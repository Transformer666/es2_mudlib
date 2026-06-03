// refine.c -- 方士「煉丹」：在丹房的丹爐前以藥材煉製丹藥（資料驅動多配方版）。
//
// 設計與來源：docs/02-遊戲系統與機制/06-煉丹與書本系統.md、
//   memory/patterns/content-alchemy.md。
//
// 由 v1 的「單一固定配方」擴充為「資料驅動配方表 + 火候/品質判定」：
//   * 一張 RECIPES 配方表，key = 丹藥（以中文名與英文 id 雙索引），
//     value = ([ "product":丹藥檔, "ingredients":([ 藥材id:份數 ]),
//                "skill":所需 alchemy-medication 等級 ])。
//   * 指令形式：
//       refine                  -- 列出方士已能起爐的全部配方（依技能門檻）。
//       refine <丹方名>         -- 煉指定丹藥（中文「小還丹」或英文「minor heal pill」）。
//   * 火候/品質：以該丹藥自身 requirement["alchemy-medication"] 為門檻
//     （見 obj/medication/alchemist/*.c），讀方士 query_skill 比對：
//       - 技能不足門檻         -> 拒絕，不起火、不耗藥（連爐都升不起來）。
//       - 技能恰好等於門檻     -> 起火耗藥，火候不穩，必煉出「錯方」(mix_recipe)。
//       - 技能高出門檻 >=50    -> 火候老到，必成。
//       - 之間                 -> 擲骰：成則出丹，敗則「燒焦」(margin 小) 或「錯方」。
//     失敗一樣消耗藥材（爐火不認人）。本判定純讀丹藥既有的 requirement 資料，
//     不需另造丹爐物件。
//
// 機制全部比照現有、已讀過原始碼確認的做法：
//   * 指令查找：檔名 == 動詞（adm/daemons/cmd_d.c 用 get_dir + verb+".c"）。
//     放在 /cmds/std/ 所有人都搜得到，故以 query_class() 鎖死成只有方士能用。
//   * 職業判定：me->query_class()（見 feature/char/score.c）。
//   * 場地判定：須在丹房（房間 set("danfang", 1)）。
//   * 技能判定：me->query_skill("alchemy-medication", 1)（feature/char/skill.c）。
//   * 兩類藥材並存：靈芝/當歸/養氣丹是 COMBINED_ITEM（有 amount，
//     add_amount(-1) 逐份消耗、歸零自毀，移入身上自動合併）；辰砂/枸杞/
//     番木鱉/鶴頂紅是 REAGENT_ITEM（按重量論價、無 amount，買一份 = 一個
//     物件、不自動合併）。本指令兩者通吃：COMBINED_ITEM 數 query_amount()、
//     REAGENT_ITEM 一個物件算一份，消耗時前者 add_amount、後者 destruct。
//   * 產出丹藥：new(product)->move(me)（COMBINED_ITEM 會與同類自動合併）。
//   * 訊息：message_vision，$N=施者（見現有指令）。
//
// 安全性：所有前置檢查（職業／丹房／技能門檻／藥材是否齊全）都在動手扣料
// **之前**完成，任一不過一律拒絕、不消耗任何東西。確認可煉後才一次扣足藥材，
// 故非無限資源，也不會半途扣了料卻沒結果。

inherit F_CLEAN_UP;

#define ALCHEMY_SKILL   "alchemy-medication"
#define PILL_MIXED      "/obj/medication/alchemist/mix_recipe"

// 前置宣告（比照 green_pill.c 的 do_cure_poison 慣例，免函式定義先後順序之累）。
private string herb_name(string id);
private string id_to_path(string id);
private int count_herb(object me, string id);
private void consume_herb(object me, string id, int n);
private int list_recipes(object me);

// 資料驅動配方表。
//   key      ：丹藥的指認字串。同一爐丹列兩條（中文名 + 英文短名），
//              讓玩家 refine 小還丹 或 refine minor heal pill 都認得。
//   product  ：成品丹藥檔。
//   ingredients：([ 藥材英文 id : 份數 ])。份數 = COMBINED_ITEM 的 amount
//              或 REAGENT_ITEM 的個數。等級越高 -> 藥材越多越稀（辰砂、番木鱉）。
//   skill    ：所需 alchemy-medication 等級（與成品 requirement 一致，作備援）。
mapping RECIPES = ([
    // 養氣丹：丹派入門療傷丹（保留原 v1 配方，門檻最低）。
    "養氣丹"            : ([ "product":"/obj/reagent/yangqi_pill",
                            "ingredients":([ "lingzhi":1, "danggui":1 ]),
                            "skill":0 ]),
    "yangqi pill"       : ([ "product":"/obj/reagent/yangqi_pill",
                            "ingredients":([ "lingzhi":1, "danggui":1 ]),
                            "skill":0 ]),

    // 烏心丹：民間恢復體力的常方，藥材尋常。
    "烏心丹"            : ([ "product":"/obj/medication/alchemist/black_pill",
                            "ingredients":([ "danggui":1, "medlar":1 ]),
                            "skill":0 ]),
    "black pill"        : ([ "product":"/obj/medication/alchemist/black_pill",
                            "ingredients":([ "danggui":1, "medlar":1 ]),
                            "skill":0 ]),

    // 清腹丹（新）：清食水、解滯脹的輕劑。
    "清腹丹"            : ([ "product":"/obj/medication/alchemist/lavage_pill",
                            "ingredients":([ "medlar":1, "danggui":1 ]),
                            "skill":10 ]),
    "lavage pill"       : ([ "product":"/obj/medication/alchemist/lavage_pill",
                            "ingredients":([ "medlar":1, "danggui":1 ]),
                            "skill":10 ]),

    // 甘靈清毒丹：清熱解毒，含微毒鶴頂紅以毒攻毒。
    "甘靈清毒丹"        : ([ "product":"/obj/medication/alchemist/green_pill",
                            "ingredients":([ "danggui":1, "medlar":2, "crane dye":1 ]),
                            "skill":15 ]),
    "green pill"        : ([ "product":"/obj/medication/alchemist/green_pill",
                            "ingredients":([ "danggui":1, "medlar":2, "crane dye":1 ]),
                            "skill":15 ]),

    // 醒神丹（新）：回神（sen）提神醒腦。
    "醒神丹"            : ([ "product":"/obj/medication/alchemist/mana_pill",
                            "ingredients":([ "lingzhi":1, "medlar":1 ]),
                            "skill":20 ]),
    "mana pill"         : ([ "product":"/obj/medication/alchemist/mana_pill",
                            "ingredients":([ "lingzhi":1, "medlar":1 ]),
                            "skill":20 ]),

    // 金液丹：常見療傷丹，需汞護爐，故添辰砂。
    "金液丹"            : ([ "product":"/obj/medication/alchemist/aquapill",
                            "ingredients":([ "lingzhi":1, "danggui":1, "cinnabar":1 ]),
                            "skill":30 ]),
    "aquapill"          : ([ "product":"/obj/medication/alchemist/aquapill",
                            "ingredients":([ "lingzhi":1, "danggui":1, "cinnabar":1 ]),
                            "skill":30 ]),

    // 養心丹（新）：回精（gin）並解疲勞（fatigue）。
    "養心丹"            : ([ "product":"/obj/medication/alchemist/relax_pill",
                            "ingredients":([ "danggui":1, "medlar":1, "cinnabar":1 ]),
                            "skill":35 ]),
    "relax pill"        : ([ "product":"/obj/medication/alchemist/relax_pill",
                            "ingredients":([ "danggui":1, "medlar":1, "cinnabar":1 ]),
                            "skill":35 ]),

    // 金鎖固精丸：澀精丹，藥材精貴。
    "金鎖固精丸"        : ([ "product":"/obj/medication/alchemist/refresh_pill",
                            "ingredients":([ "lingzhi":1, "medlar":2, "cinnabar":1 ]),
                            "skill":50 ]),
    "refresh pill"      : ([ "product":"/obj/medication/alchemist/refresh_pill",
                            "ingredients":([ "lingzhi":1, "medlar":2, "cinnabar":1 ]),
                            "skill":50 ]),

    // 小還丹：瞬癒外傷的仙丹，須大量汞護爐，藥材昂貴。
    "小還丹"            : ([ "product":"/obj/medication/alchemist/minor_heal_pill",
                            "ingredients":([ "lingzhi":2, "danggui":1, "cinnabar":2 ]),
                            "skill":60 ]),
    "minor heal pill"   : ([ "product":"/obj/medication/alchemist/minor_heal_pill",
                            "ingredients":([ "lingzhi":2, "danggui":1, "cinnabar":2 ]),
                            "skill":60 ]),

    // 大還丹：內外傷俱癒的極品仙丹，另需番木鱉等罕材，火候最難。
    "大還丹"            : ([ "product":"/obj/medication/alchemist/major_heal_pill",
                            "ingredients":([ "lingzhi":3, "danggui":2, "cinnabar":3, "strychin":1 ]),
                            "skill":150 ]),
    "major heal pill"   : ([ "product":"/obj/medication/alchemist/major_heal_pill",
                            "ingredients":([ "lingzhi":3, "danggui":2, "cinnabar":3, "strychin":1 ]),
                            "skill":150 ]),
]);

private void create() { seteuid(getuid()); }

// 取藥材的中文名（給訊息用）。先 present 身上的實物，沒有就 load 藍本問。
private string herb_name(string id)
{
    object ob = present(id, this_player());
    if( !ob ) {
        mixed err = catch(ob = load_object(id_to_path(id)));
        if( err || !ob ) return id;
    }
    return (string)ob->query("name") || id;
}

// 藥材 id -> 物件檔（僅供 herb_name fallback 載入藍本；可省略也不影響主流程）。
private string id_to_path(string id)
{
    switch(id) {
        case "lingzhi"  : return "/obj/reagent/lingzhi";
        case "danggui"  : return "/obj/reagent/danggui";
        case "cinnabar" : return "/obj/reagent/cinnabar";
        case "medlar"   : return "/obj/reagent/medlar";
        case "strychin" : return "/obj/reagent/strychin";
        case "crane dye": return "/obj/reagent/crane_dye";
    }
    return id;
}

// 數方士身上某味藥材的可用份數。
//   COMBINED_ITEM：累加各物件的 query_amount()。
//   REAGENT_ITEM ：一個物件算一份（買一份即一物件，不自動合併）。
private int count_herb(object me, string id)
{
    int total = 0;
    object ob;

    foreach(ob in all_inventory(me)) {
        if( !ob->id(id) ) continue;
        if( inherits(COMBINED_ITEM, ob) )
            total += (int)ob->query_amount();
        else
            total += 1;
    }
    return total;
}

// 從方士身上扣掉某味藥材 n 份。
//   COMBINED_ITEM：add_amount(-take)，歸零自毀。
//   REAGENT_ITEM ：逐個 destruct，每個一份。
// 呼叫前必已 count_herb 確認份數足夠。
private void consume_herb(object me, string id, int n)
{
    object ob;
    int have, take;

    foreach(ob in all_inventory(me)) {
        if( n <= 0 ) break;
        if( !ob->id(id) ) continue;

        if( inherits(COMBINED_ITEM, ob) ) {
            have = (int)ob->query_amount();
            take = (have < n) ? have : n;
            ob->add_amount(-take);
            n -= take;
        } else {
            destruct(ob);
            n -= 1;
        }
    }
}

// 列出方士當前能起爐的配方（標示技能門檻與藥材）。
// 配方表每爐丹有「中文名 + 英文短名」兩條 key﹐這裡只取中文名那條（key[0]
// 為高位元組）逐一列出﹐英文 key 自然略過﹐故每爐丹恰列一次。
private int list_recipes(object me)
{
    int skill = (int)me->query_skill(ALCHEMY_SKILL, 1);
    string list = "";
    string key, hid, herbs, cname;
    mapping r;
    int qty, req;

    foreach(key, r in RECIPES) {
        if( key[0] < 128 ) continue;        // 只列中文名那條﹐略過英文別名

        cname = (string)load_object(r["product"])->query("name");
        if( !cname ) cname = key;
        req = r["skill"];

        herbs = "";
        foreach(hid, qty in r["ingredients"])
            herbs += sprintf("%s%s×%d", herbs=="" ? "" : "、", herb_name(hid), qty);

        list += sprintf("  %-14s（技能 %3d）  藥材：%s%s\n",
            cname, req, herbs,
            skill >= req ? "" : "  ［技未及﹐火候不足］");
    }

    write("丹房丹爐前﹐你（alchemy-medication 技能 " + skill + "）盤算著手上能煉的丹方：\n");
    write("-------------------------------------------------------------\n");
    write(list);
    write("以「refine <丹方名>」起爐﹐如 refine 養氣丹 / refine minor heal pill。\n");
    return 1;
}

int main(object me, string arg)
{
    mapping recipe;
    mapping ingredients;
    string product, hid, cname;
    int qty, req, skill, margin, roll;
    object blueprint, pill;

    if( me->is_busy() )
        return notify_fail("請先用 halt 停止你正在做的事。\n");

    // 只有方士懂得煉丹。
    if( me->query_class() != "alchemist" )
        return notify_fail("你又不是方士﹐哪會煉什麼丹？\n");

    // 須在丹房（架著丹爐）才能起火煉丹。
    if( !environment(me) || !environment(me)->query("danfang") )
        return notify_fail("這裡沒有丹爐﹐你得到丹房裡才煉得了丹。\n");

    // 不帶參數 -> 列出可煉的配方。
    if( !arg || arg=="" )
        return list_recipes(me);

    // 查表（中文名或英文短名皆可）。lower_case 只動 ASCII A-Z﹐中文 key
    // 的高位元組不受影響﹐故「養氣丹」與「Minor Heal Pill」皆查得到。
    recipe = RECIPES[arg];
    if( !mapp(recipe) ) recipe = RECIPES[lower_case(arg)];
    if( !mapp(recipe) )
        return notify_fail("丹經裡查無「" + arg + "」這一爐丹方。打 refine（不帶參數）看看你能煉些什麼。\n");

    product     = recipe["product"];
    ingredients = recipe["ingredients"];
    blueprint   = load_object(product);
    cname       = (string)blueprint->query("name") || arg;

    // 火候門檻：以成品自身的 requirement 為準，配方表 skill 作備援。
    req   = (int)blueprint->query("requirement/" + ALCHEMY_SKILL);
    if( !req ) req = recipe["skill"];
    skill = (int)me->query_skill(ALCHEMY_SKILL, 1);

    // 技能連門檻都不及 -> 連爐火都升不起來，拒絕、不耗藥。
    if( skill < req )
        return notify_fail(sprintf(
            "煉製%s須通曉煉丹之術達 %d 級﹐你才 %d 級﹐連爐火也升不穩﹐莫要糟蹋了藥材。\n",
            cname, req, skill));

    // 清點藥材是否齊全（全部在動手扣料之前查完）。
    foreach(hid, qty in ingredients) {
        if( count_herb(me, hid) < qty )
            return notify_fail(sprintf("煉製%s還少了%s（需 %d 份）﹐你身上不夠。\n",
                cname, herb_name(hid), qty));
    }

    // 藥材齊全、技能達標 -> 確定要起爐了﹐一次扣足所有藥材（成敗都扣）。
    foreach(hid, qty in ingredients)
        consume_herb(me, hid, qty);

    message_vision("$N將備齊的藥材一一投入丹爐﹐添炭搧風﹐凝神運火。\n", me);

    // 火候/品質判定。margin = 技能高出門檻多少。
    //   margin >=50：火候老到 -> 必成。
    //   margin ==0 ：火候勉強 -> 必出錯方（deterministic 失敗錨點）。
    //   1..49      ：擲骰﹐成則出丹﹐敗則燒焦(margin<10)或錯方。
    margin = skill - req;
    if( margin >= 50 ) {
        roll = -1;          // 標記必成
    } else if( margin == 0 ) {
        roll = 100;         // 標記必敗（錯方）
    } else {
        roll = random(100); // 50 + margin 為成功線
    }

    if( margin >= 50 || (margin > 0 && roll < 50 + margin) ) {
        // 成功：煉出正品丹藥。
        pill = new(product);
        pill->move(me);
        message_vision(sprintf(
            "$N守爐運氣﹐良久﹐爐中藥香漸濃﹐火候恰到好處﹐凝成一粒%s。\n", cname), me);
        return 1;
    }

    // 失敗：火候沒拿穩。margin 太小（含恰好等於門檻）-> 燒焦無丹﹔否則出錯方。
    if( margin < 10 && margin != 0 ) {
        message_vision(
            "$N守爐半晌﹐一個火候沒拿穩﹐爐中藥材登時焦糊﹐冒起一股黑煙﹐這一爐算是廢了。\n", me);
        return 1;
    }

    // 錯方：藥性混雜﹐凝出一粒來路不明的混合藥丹（mix_recipe）。
    pill = new(PILL_MIXED);
    pill->move(me);
    message_vision(
        "$N火候稍欠﹐爐中諸藥未能調和﹐勉強凝成一粒色澤駁雜的混合藥丹﹐藥性難料。\n", me);
    return 1;
}

int help(object me)
{
    write(@HELP
指令格式﹕
    refine                （中文﹕煉丹）          列出你目前能起爐的丹方
    refine <丹方名>       （如 refine 小還丹 / refine minor heal pill）  起爐煉一爐丹

方士站在丹房的丹爐前﹐身上備齊藥材時﹐可用此指令煉製丹藥。每一爐丹方各
有所需藥材與「煉丹之術（alchemy-medication）」的技能門檻﹕

    養氣丹      靈芝×1 當歸×1                （技能 0）  調養精氣神、癒外傷
    烏心丹      當歸×1 枸杞×1                （技能 0）  恢復體力
    清腹丹      枸杞×1 當歸×1                （技能 10） 清食水、解滯脹
    甘靈清毒丹  當歸×1 枸杞×2 鶴頂紅×1       （技能 15） 清熱解毒
    醒神丹      靈芝×1 枸杞×1                （技能 20） 回神醒腦
    金液丹      靈芝×1 當歸×1 辰砂×1         （技能 30） 療傷
    養心丹      當歸×1 枸杞×1 辰砂×1         （技能 35） 回精、解疲勞
    金鎖固精丸  靈芝×1 枸杞×2 辰砂×1         （技能 50） 澀精
    小還丹      靈芝×2 當歸×1 辰砂×2         （技能 60） 瞬癒外傷
    大還丹      靈芝×3 當歸×2 辰砂×3 番木鱉×1（技能 150）內外傷俱癒

火候（品質）取決於你的技能高出該丹門檻多少﹕技未及門檻者連爐火也升不起來
（不耗藥）﹔技能恰好及格者火候不穩﹐每每煉成不知藥性的「混合藥丹」﹔技高一
籌方能穩穩出丹。無論成敗﹐起爐後都會消耗投入的藥材。

藥材可向百藥谷的采藥老人 buy。煉成後以英文代號服食﹐如 eat yangqi、eat minor。
HELP
    );
    return 1;
}

// vim: set ts=4 sw=4 syntax=lpc

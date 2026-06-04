// lizaiyan.c -- 京畿神社的隱士「李再延」，docs 支線 item-giver。
//
// 來源(doc)：docs/01-世界觀與劇情/05-主線任務與NPC.md「重要任務 NPC」表——
//   「李再延 @ 京畿神社 n-w-s → 給六靈玄衣」。本檔即落實李再延其人，並令其
//   贈玩家一件防具「六靈玄衣」(d/capital/npc/obj/liuling_robe)。
//
// 立意（接 d/capital 京畿神社/聖木一脈設定）：李再延者，當年守木一脈一位早已
//   隱去名姓的織衣老者。他畢生只做一件事——以神社祕傳的六色靈絲緙織護身的「六
//   靈玄衣」，緙一件，便在神社後殿的蒲團上枯坐參一回六脈之靈。他不問世事，唯
//   有後生肯虛心向他問起這門將要失傳的『玄衣』織技，他才肯把畢生緙就的一件六
//   靈玄衣，贈與有緣之人。
//
// 給法（同步交付，承本專案頭號 bug class「同步交付」之教訓 — 鏡 d/caobang/npc/
//   jiangyun.c 之 give_ghost_ring）：
//   * do_ask 之贈衣分支內，直接 give_robe(who)：new() + if(!move(who)) move(env)，
//     並於設完成旗標『之前』呼叫——絕不放進延遲的 do_chat closure(玩家中途離場會
//     soft-lock)；亦不用 `if(move)`(成功時反落地)。
//   * 防重領：以逐玩家旗標 quest/sq_lizaiyan 為閘(已領者只給氣氛、不重發)，
//     give_robe 內另以 present("liuling robe", who) 作第二道防重給保險。
//
// 閘門可測性：本支線無 docs 載明的硬性前置(不似鍾豪需 10g、凌筠語需換物)，
//   故唯一閘門即「未曾領過」(quest/sq_lizaiyan 未設) — 任何玩家(含 wizard)
//   ask 一次即可取得，便於測試。
//
// ⚠ 本 NPC 自訂 do_ask，依 lesson『有自訂 add_action 之 NPC 斷不可 replace_program』
//   — 本檔故「不」replace_program。

#include <ansi.h>
#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("李再延", ({ "li zaiyan", "lizaiyan", "zaiyan" }) );
	set("nickname", "織衣老者");
	set("title", "守木一脈");
	set_attr("int", 24);
	set_attr("wis", 26);
	set("gender", "male");
	set("age", 78);
	set_race("human");
	set_class("commoner");
	set_level(18);
	set_skill("unarmed", 30);
	set_skill("dodge", 30);
	set_skill("force", 40);
	set_skill("literate", 50);
	set_skill("weaving", 80);

	set("long",
		HIK "京畿神社後殿一隅的蒲團上﹐枯坐著一位織衣的老者。\n" NOR
		"他鬚眉皆白﹐一身洗得發灰的玄色舊袍﹐枯瘦的十指卻靈巧得\n"
		"不似這把年紀——指間一架巴掌大的小小緙絲機上﹐六色細若髮\n"
		"絲的靈絲在他手底穿梭游走﹐織出的衣面隱隱泛著流轉的微光。\n"
		"他並不抬眼看人﹐只是一梭一梭地織著﹐彷彿這神社的香火鼎\n"
		"沸、善信往來﹐皆與他無干。聽聞他是守木一脈一位早已隱去\n"
		"名姓的織衣人﹐畢生只緙一件護身的『六靈玄衣』﹐緙成一件\n"
		"﹐便枯坐參一回六脈之靈。\n"
		"（你或許可以問問他﹕ask lizaiyan about 玄衣）\n");
	setup();
	carry_object("/obj/area/obj/robe")->wear();
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

// 把一件六靈玄衣同步交到玩家手上（new + move；move 失敗才落地，鏡 jiangyun.c）。
// 第二道防重給：玩家身上已有則不再給。
private void give_robe(object who)
{
	object robe;

	if( !who || environment(who) != environment() )
		return;
	if( present("liuling robe", who) )
		return;

	robe = new(__DIR__"obj/liuling_robe");
	if( !robe->move(who) )
		robe->move(environment());
}

int do_ask(string arg)
{
	object me = this_player();

	if( !arg )
		return notify_fail("你想問這位織衣老者甚麼﹖（試試 ask lizaiyan about 玄衣）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("李再延正低頭緙著手中那件玄衣﹐沒空理你。\n");

	// 贈衣分支：六靈玄衣 / 玄衣 / 織技 / 守木
	if( arg == "lizaiyan about 玄衣"
	||  arg == "lizaiyan about 六靈玄衣"
	||  arg == "lizaiyan about 織衣"
	||  arg == "lizaiyan about 織技"
	||  arg == "lizaiyan about 守木"
	||  arg == "lizaiyan about 六靈"
	||  arg == "lizaiyan about robe"
	||  arg == "li zaiyan about 玄衣"
	||  arg == "li zaiyan about robe" ) {

		// 已領過：只給氣氛，不重發
		if( me->query("quest/sq_lizaiyan") >= 1 ) {
			do_chat(({
				(: command, "say （李再延枯瘦的手底一梭一梭地織著﹐並不抬眼）那件六靈玄衣﹐老朽既已贈與少俠﹐便是少俠的造化了。" :),
				(: command, "say 好生穿著罷——這六色靈絲護的是少俠周身六脈﹐遠勝尋常刀槍不入的硬甲。老朽這門將要失傳的織技﹐能有人接著穿﹐也算不負了。" :),
			}));
			return 1;
		}

		// 未領：同步授衣（先給物、後設旗標），再播氣氛對白
		give_robe(me);
		me->set("quest/sq_lizaiyan", 1);
		do_chat(({
			"李再延的手停了一停﹐這才緩緩抬起頭來﹐一雙渾濁的老眼在你臉上端詳了半晌。\n",
			(: command, "say 後生肯虛心問起這門織技 ... 難得﹐難得。如今的少年人﹐眼裡只有那寒光逼人的硬甲利兵﹐有幾個還記得這以六色靈絲緙就、護住周身六脈的玄衣﹖" :),
			(: command, "say 老朽守木一脈﹐這一輩子也沒做別的﹐只把這六靈玄衣緙了一件又一件。緙成一件﹐便在這蒲團上參一回六脈之靈——緙到如今﹐倒也記不清緙了多少件了。" :),
			"老者枯瘦的手在身畔一摸﹐取出一件疊得方方正正、玄色泛著微光的軟衣來﹐遞到你手中。\n",
			(: command, "say 這一件﹐老朽便贈與少俠了。穿在身上﹐六脈要害皆在護持之下﹐刀劍劈來如砍韌革——少俠他日闖蕩江湖﹐莫教這條命﹐折在不值當的地方。去罷。" :),
		}));
		return 1;
	}

	return notify_fail("李再延只顧低頭緙著手中的玄衣﹐淡淡道﹕老朽不過一個織衣的﹐世事多問無益。（試試 ask lizaiyan about 玄衣）\n");
}

int accept_fight(object ob)
{
	do_chat((: command, "say 少俠息怒﹗老朽一個織衣的糟老頭子﹐當不起少俠動怒。" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc

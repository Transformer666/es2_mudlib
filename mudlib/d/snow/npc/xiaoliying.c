// xiaoliying.c -- 雪山妖妃「肖麗穎」，docs 支線 item-giver。
//
// 來源(doc)：docs/01-世界觀與劇情/05-主線任務與NPC.md「重要任務 NPC」表——
//   「肖麗穎 (Xiao li ying) @ 雪山妖妃 → 給青絲釣竿、追風劍」。本檔落實肖麗穎
//   其人，並令其贈玩家一件釣具「青絲釣竿」(d/snow/npc/obj/qingsi_rod)。
//
// 駐地：docs 原列『雪山妖妃(雪山)』一域，然本 mudlib 至今未開出雪山一域(d/ 下
//   無雪山／妖妃之室；snow=雪亭鎮、snowmanor=雪吟莊、skysnow=卯天樹下，皆非雪
//   山)。依任務指示『雪山一域整域缺席則不憑空造鎮』，本支線暫借雪亭鎮河邊空地
//   (d/snow/riverbank.c)為肖麗穎駐足之地——湍流臨水，正宜這位妖妃臨潭垂釣、贈
//   竿予有緣後生。他日雪山一域開出，自當遷之歸位。
//
// 立意：雪山妖妃肖麗穎者，傳是雪山深處一位來歷莫測的女子。世人只當她是個禍水
//   妖妃，她卻自顧自地揀了這滾滾紅塵裡一處臨水的空地，終日把著一桿青絲釣竿臨
//   潭而坐，神色淡淡，物我兩忘。她釣的不是魚——是這紅塵裡難得的一點清靜。她不
//   問世事，唯有後生肯虛心向她問起這門臨水垂釣、忘機物外的工夫，她才肯把親手
//   以三千青絲挽就的一桿青絲釣竿，贈與有緣之人。
//
// 給法（同步交付，承本專案頭號 bug class「同步交付」之教訓 — 鏡 d/capital/npc/
//   lizaiyan.c::give_robe / d/caobang/npc/jiangyun.c::give_ghost_ring）：
//   * do_ask 之贈竿分支內，直接 give_rod(who)：new() + if(!move(who)) move(env)，
//     並於設完成旗標『之前』呼叫——絕不放進延遲的 do_chat closure(玩家中途離場
//     會 soft-lock)；亦不用 `if(move)`(成功時反落地)。
//   * 防重領：以逐玩家旗標 quest/sq_xiaoliying 為閘(已領者只給氣氛、不重發)，
//     give_rod 內另以 present("qingsi rod", who) 作第二道防重給保險。
//   * 遺失補發：已設旗標但身上已無此竿者，再 ask 一次即同步補發(give_rod 內
//     present() 查無 → 重發)，玩家不致因遺失而 soft-lock。
//
// 閘門可測性：docs 雖列肖麗穎一系或涉換物，本支線從輕、以『虛心問起垂釣工夫』
//   為唯一軟閘——quest/sq_xiaoliying 未設者，任何玩家(含 wizard)ask 一次即得，
//   便於測試；docs 之換物意味化入對白風味，不作硬閘。
//
// ⚠ 本 NPC 自訂 do_ask(有 add_action)，依 lesson『有自訂 add_action 之 NPC 斷
//   不可 replace_program』— 本檔故「不」replace_program。

#include <ansi.h>
#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name(HIM "肖麗穎" NOR, ({ "xiaoliying", "xiao liying", "liying" }) );
	set("nickname", HIM "雪山妖妃" NOR);
	set("title", "臨潭垂釣");
	set_attr("int", 25);
	set_attr("wis", 26);
	set_attr("con", 22);
	set("gender", "female");
	set("age", 27);
	set_race("human");
	set_class("commoner");
	set_level(20);
	set_skill("unarmed", 35);
	set_skill("dodge", 40);
	set_skill("force", 45);
	set_skill("staff", 50);
	set_skill("literate", 40);

	set("long",
		HIK "河邊這方臨水的空地上﹐一位女子正獨自把著釣竿﹐臨潭而坐。\n" NOR
		"她生得明艷照人﹐一身月白衣裙在湍流的水汽裡微微浮動﹐烏髮\n"
		"只用一支青玉簪鬆鬆挽住﹐幾縷垂在頰邊﹐說不出的慵懶風流。\n"
		"她手裡那桿釣竿竿梢繫著一縷青中泛碧的細絲﹐垂在風裡卻不見\n"
		"它隨風亂擺﹐反似有靈﹐自顧自地舒捲游走。她並不抬眼看人﹐\n"
		"只是望著平靜的潭面﹐神色淡淡﹐似已物我兩忘。聽聞這位便是\n"
		"雪山深處那位來歷莫測的『雪山妖妃』肖麗穎了——世人只當她是\n"
		"個禍水﹐她卻自顧自地揀了這臨水的空地﹐終日垂釣﹐釣的不是\n"
		"魚﹐是這滾滾紅塵裡難得的一點清靜。\n"
		"（你或許可以問問她﹕ask xiaoliying about 垂釣）\n");
	setup();
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

// 把一根青絲釣竿同步交到玩家手上（new + move；move 失敗才落地，鏡 lizaiyan.c）。
// 第二道防重給：玩家身上已有則不再給。
private void give_rod(object who)
{
	object rod;

	if( !who || environment(who) != environment() )
		return;
	if( present("qingsi rod", who) )
		return;

	rod = new(__DIR__"obj/qingsi_rod");
	if( !rod->move(who) )
		rod->move(environment());
}

int do_ask(string arg)
{
	object me = this_player();

	if( !arg )
		return notify_fail("你想問這位臨潭垂釣的女子甚麼﹖（試試 ask xiaoliying about 垂釣）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("肖麗穎正凝神望著潭面那縷青絲﹐沒空理你。\n");

	// 贈竿分支：垂釣 / 釣竿 / 青絲釣竿 / 青絲 / 妖妃 / rod
	if( arg == "xiaoliying about 垂釣"
	||  arg == "xiaoliying about 釣竿"
	||  arg == "xiaoliying about 青絲釣竿"
	||  arg == "xiaoliying about 青絲"
	||  arg == "xiaoliying about 妖妃"
	||  arg == "xiaoliying about 雪山"
	||  arg == "xiaoliying about rod"
	||  arg == "xiaoliying about fishing"
	||  arg == "xiao liying about 垂釣"
	||  arg == "xiao liying about rod" ) {

		// 已領過：身上仍在 → 只給氣氛；身上已無 → 同步補發(遺失補發)
		if( me->query("quest/sq_xiaoliying") >= 1 ) {
			if( present("qingsi rod", me) ) {
				do_chat(({
					(: command, "say （肖麗穎望著潭面﹐並不抬眼）那桿青絲釣竿﹐我既已贈與少俠﹐便是少俠的緣法了。" :),
					(: command, "say 得空時﹐尋一處清靜水邊﹐垂它一竿罷——釣得著釣不著魚﹐都不打緊﹐要緊的是那一點忘機的心境。" :),
				}));
				return 1;
			}
			// 旗標已設、竿卻不在身上：判為遺失，同步補發
			give_rod(me);
			do_chat(({
				(: command, "say （肖麗穎眉梢微微一動）少俠那桿青絲釣竿﹐怎的不在身上了﹖" :),
				"她信手在身畔一摸﹐又取出一桿一模一樣的青絲釣竿來﹐遞到你手中。\n",
				(: command, "say 罷了﹐這紅塵裡的東西﹐丟了便丟了。再贈少俠一桿便是——這一回﹐莫教它再離了身。" :),
			}));
			return 1;
		}

		// 未領：同步授竿（先給物、後設旗標），再播氣氛對白
		give_rod(me);
		me->set("quest/sq_xiaoliying", 1);
		do_chat(({
			"肖麗穎握竿的手停了一停﹐這才緩緩側過臉來﹐一雙水盈盈的妙目在你臉上掃了一掃。\n",
			(: command, "say 後生肯虛心問起這臨水垂釣的工夫 ... 倒也難得。世人見了我﹐不是怕﹐便是貪﹐有幾個還靜得下心來﹐看一看這潭面上的一點清光﹖" :),
			(: command, "say 我這桿釣竿﹐竿梢這縷青絲﹐是我一寸一寸、以三千青絲親手挽就的。垂之於潭﹐釣的不是魚——是這滾滾紅塵裡﹐難得的一點清靜罷了。" :),
			"她信手在身畔一摸﹐取出一桿丈餘長、竿梢繫著一縷幽碧青絲的釣竿來﹐遞到你手中。\n",
			(: command, "say 這一桿﹐我便贈與少俠了。少俠他日闖蕩江湖﹐殺得倦了、爭得累了﹐便尋一處清靜水邊﹐垂它一竿——記著這潭面上的一點清光﹐莫教那紅塵裡的刀光劍影﹐迷了少俠的眼。去罷。" :),
		}));
		return 1;
	}

	return notify_fail("肖麗穎只顧凝望著潭面那縷青絲﹐淡淡道﹕我不過一個臨水垂釣的閒人﹐世事多問無益。（試試 ask xiaoliying about 垂釣）\n");
}

int accept_fight(object ob)
{
	do_chat((: command, "say 少俠且慢動手——我一個臨水垂釣的女子﹐當不起少俠這般大動干戈。" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc

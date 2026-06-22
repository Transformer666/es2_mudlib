// hermit.c -- 採藥隱士，隱居六甲山雲松坪的避世採藥老者。
//
// 純氣氛 NPC：不開任務、不給物、不戰鬥。只負責 ask hermit about <關鍵字>
// 講述六甲山的由來掌故（六甲、石陣、散仙、草藥）。結構沿用已驗證的
// /d/wutang/npc/washerwoman.c（add_action("do_ask","ask") + interactive 護衛
// 招呼 + do_chat）。遵 INDEX #11：本 NPC 有自訂 init()/do_ask method，不可
// replace_program；遵 #14：init() 招呼加 interactive(this_player()) 護衛，只招
// 呼真人，免 NPC 互觸洗版。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("採藥隱士", ({ "herb hermit", "hermit", "old man" }) );
	set("nickname", "六甲山人");
	set_race("human");
	set_class("commoner");
	set_level(8);

	set("age", 71);
	set("gender", "male");
	set("long",
		"一位鬚髮皓然的採藥老者﹐布衣芒鞋﹐背著一只半舊的竹簍﹐簍\n"
		"裡盛著剛採來的草藥。他在這六甲山雲松坪結廬已數十載﹐日日\n"
		"倚松吐納、入谷採藥﹐早把這滿山的草木掌故、由來舊聞﹐都摸\n"
		"得透熟。他面色和藹﹐眼神清矍﹐見了入山的後生﹐倒也樂得攀\n"
		"談幾句。（你可以 ask hermit about 六甲／石陣／散仙／草藥）\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"採藥隱士捻著一株剛採的黃精﹐就著日光端詳藥性。\n",
		"採藥隱士望著峰頂的方向﹐悠悠地嘆道﹕這六甲山﹐養人哪。\n",
		"採藥隱士盤膝坐在青石上﹐闔目吐納﹐胸口微微起伏。\n",
	}));
	setup();
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	// 遵 INDEX #14：只對真人招呼，免 NPC 互觸成洗版。
	if( this_player() && interactive(this_player()) && !is_fighting() )
		do_chat((: command,
			"say 後生入山了﹖這六甲山的掌故﹐老朽倒還知道些﹐儘管問來。" :));
}

int do_ask(string arg)
{
	if( is_fighting() || is_chatting() )
		return notify_fail("採藥隱士正忙著﹐沒空理你。\n");

	if( arg == "hermit about 六甲" || arg == "hermit about liujia" ) {
		do_chat(({
			(: command, "say 這六甲山的名字﹐緣於峰頂一處古拙的石陣。" :),
			(: command, "say 那石陣以六塊巨石按著甲子六甲之數布成﹐相傳乃上古高人手筆﹐暗合奇門遁甲之妙﹐故喚作六甲山。" :),
			(: command, "say 山雖不算極高﹐草木地氣卻最是養人﹐故避世修煉的散人﹐都愛來此潛修。" :),
		}));
		return 1;
	}
	if( arg == "hermit about 石陣" || arg == "hermit about stone" ) {
		do_chat(({
			(: command, "say 峰頂那座六甲石陣麼﹖老朽年輕時也曾上去瞧過。" :),
			(: command, "say 六塊烏石歷盡風雨雷火﹐不知幾千百年了。據說每逢月圓子時﹐陣中隱隱有異象﹐然老朽福薄﹐倒不曾親見。" :),
			(: command, "say 山頂那位散仙﹐便日日在那陣中踏罡步斗﹐借石陣的玄機與峰頂的罡風養氣。" :),
		}));
		return 1;
	}
	if( arg == "hermit about 散仙" || arg == "hermit about sanren" ) {
		do_chat(({
			(: command, "say 你說的是峰頂那位六甲散仙罷﹖那是位內功有成的高人﹐潛修這六甲山頂已數十載了。" :),
			(: command, "say 他不問世事﹐卻最重一個武字。後生若自負藝高﹐上得峰頂去與他印證武學﹐他向來奉陪到底、絕不藏私——只是他手底下了得﹐你可掂量著來。" :),
		}));
		return 1;
	}
	if( arg == "hermit about 草藥" || arg == "hermit about herb" ) {
		do_chat(({
			(: command, "say 這六甲山的深谷崖罅﹐喜陰的好藥材著實不少——黃精、白朮、首烏、靈芝之屬﹐俯拾皆是。" :),
			(: command, "say 老朽採了藥﹐曬乾了便下山換些米鹽。後生若也識得藥性﹐這滿山倒是一座取之不盡的寶庫呢。" :),
		}));
		return 1;
	}

	return notify_fail("你想問採藥隱士甚麼﹖（試試 ask hermit about 六甲／石陣／散仙／草藥）\n");
}

// 與世無爭、不與人動武。
int accept_fight()
{
	do_chat("採藥隱士連連擺手﹐呵呵笑道﹕老朽一個採藥的山野之人﹐與後生無冤無仇﹐動甚麼手呢﹖\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc

// teller.c -- 喬陰縣前廣場的算命先生，替人占算「技能天賦(潛能)」的隱藏資訊
//
// 設計來源：docs/02-遊戲系統與機制/03-升級與天賦.md「算命仙天賦對照表」。
//   * 縣前廣場(square.c)的房間描述本就有「算命的瞎子」，本 NPC 即坐鎮於此。
//   * 玩家以 inquire <技能英文代號>（中文別名 占算）請先生占算某技能的天賦上限，
//     每次收卦金五兩黃金；先生依天賦數值(140~200)說出對應的吉凶斷語。
//   * 真正的占算/收費/查詢天賦邏輯全在 /cmds/std/inquire.c，本 NPC 只負責：
//       - 以 set("fortune_teller", 1) 標記，供 inquire 指令尋人。
//       - do_ask 解說「算命」這門生意（要玩家去 inquire <技能>）。
//
// 注意：玩家指令以英文 id 比對(feature/name.c::id())，故 ask 的對象、inquire 的
//   技能參數都用英文；先生口中說出的技能名則轉成中文(to_chinese)以利閱讀。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("算命先生", ({ "teller", "fortune teller", "xiansheng" }) );
	set("nickname", "賽神仙");
	set_race("human");
	set_class("scholar");
	set_level(10);

	set("age", 61);
	set("gender", "male");
	set("long",
		"一位坐在縣前廣場角落的算命先生﹐一身洗得發白的灰布道袍﹐\n"
		"頭戴方巾﹐一雙眼睛半睜半閉﹐似瞎非瞎。他面前的小桌上鋪著\n"
		"一方寫著「鐵口直斷」的舊布幡﹐擺著籤筒、銅錢與一本翻得起\n"
		"了毛邊的相書。聽聞他這「賽神仙」的名號不是白叫的﹐尤擅看\n"
		"人骨相、占人習武的天賦根骨﹐只是這卦金﹐可不便宜。\n"
		"你或許可以問問他﹕ask teller about 算命。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"算命先生半睜著眼﹐枯瘦的手指捻著三枚銅錢﹐口中念念有詞。\n",
		"算命先生捋鬚道﹕骨相天定﹐根骨深淺﹐冥冥中自有定數﹐強求不來哪。\n",
		"算命先生壓低嗓子道﹕客官這眉宇間﹐隱隱透著一股不凡之氣 ... 可惜﹐天機不可白洩。\n",
	}));

	// 供 /cmds/std/inquire.c 尋找在場的算命先生（比照 enchant.c 的 enchant_master 標記）。
	set("fortune_teller", 1);

	setup();
	carry_money("coin", 50);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	if( this_player() && interactive(this_player()) ) {
		if( !is_fighting() )
			do_chat((: command,
				"say 這位客官面生﹐可是要算上一卦﹖" :));
	}
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這位算命先生甚麼﹖（試試 ask teller about 算命）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("算命先生正凝神替人卜算﹐沒空理你。\n");

	// 算命 / 天賦 / 占算：說明這門生意，引導玩家去 inquire <技能英文代號>
	if( arg == "teller about 算命"
	||  arg == "teller about 天賦"
	||  arg == "teller about 占算"
	||  arg == "fortune teller about 算命"
	||  arg == "teller about fortune"
	||  arg == "teller about talent" ) {
		do_chat(({
			(: command, "say 老朽這套相人之術﹐別的不敢誇口﹐單論看人習武的天賦根骨﹐喬陰縣裡再無第二人。" :),
			(: command, "say 人這一身根骨﹐天生便定了能在哪門技藝上走多遠——尋常人練到頭也不過爾爾﹐有根骨的卻能一日千里、登峰造極。" :),
			(: command, "say 客官若想知道自個兒在某門技藝上的天賦深淺﹐便對老朽說『inquire 技藝的英文代號』﹐比如想算劍法﹐便是 inquire sword﹐想算拳腳﹐便是 inquire unarmed。" :),
			(: command, "say 只是天機難測﹐起一卦得耗老朽不少心血﹐每卦須奉上卦金五兩黃金。客官須得先學過那門技藝﹐老朽方占得出名堂——半點根骨都沒沾過的﹐神仙也算不出。" :),
		}));
		return 1;
	}

	return notify_fail("算命先生半睜著眼﹐並不答話。（試試 ask teller about 算命）\n");
}

int accept_fight(object ob)
{
	do_chat((: command, "say 哎喲﹗客官息怒﹗老朽一個算命的瞎子﹐與你無冤無仇哪﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc

// chaos_seal.c -- 正史主線第七章「渾沌獸」任務的招喚信物：渾沌印記。
//
// 來歷（承接 canon 主線樹 docs 05 L54「5 個 broken seal + 神之心 → 渾沌印記」、L57「渾
//   沌獸（七彩石招喚）」、L180「進入七彩石 insert chaos seal 招喚」）：
//   少俠降盡天龍島火、天龍、雷、風四神、將四印嵌齊星光環之後，漕幫耆宿江隕將那枚自
//   蜈蚣之患所留的『破碎的印記』、合以一枚散落人間的『神之心』，於漕幫禮堂中以秘法
//   熔煉，凝成這一方七彩流轉、混沌未分的『渾沌印記』。持此印往天龍島島心神域旁的『七
//   彩石』處，於身上『insert chaos seal』(亦容『用 渾沌印記』)，便能將那印中所封、隨地
//   流竄的渾沌獸自七彩石中招出——降了渾沌獸，必得一片完整印記。
//
// 用法（第七章招喚機制——本檔 init()+do_insert()/do_use() 落實，承 lesson #11「自訂函
//   式之物不可 replace_program」、lesson #10「destruct/招喚-LAST」）：
//   * 本印在玩家背包中，其 init() 必隨印入背包(get)而觸發——故於 init() 註冊招喚動作
//     (add_action "do_insert","insert"；add_action "do_use","用"/"use")。動作掛在【背
//     包內的渾沌印記物件】上(reliable，承 starlight_ring 之 do_insert 範式)，非掛在房。
//   * 玩家須立於七彩石(/d/longdao/colorstone)、身負第七章旗標(quest/main_canon7==1)，
//     於身上『insert chaos seal』(亦容 insert chaos seal into stone / into 七彩石；或
//     『用 渾沌印記』)。合格時：自七彩石房招出渾沌獸(/d/longdao/npc/chaosbeast)、本印
//     即沒入七彩石(destruct)。⚠ destruct(渾沌印記) 與招喚 new(...)->move() 務必置於所
//     有旗標/訊息邏輯「之後」(destruct/招喚-LAST，承 lesson #10)。
//   設 no_sell：招喚信物干係主線，玩家須帶在身邊，斷不可變賣。
//
// 注意：本印為江隕逐玩家 clone 交付的任務信物，不 inherit F_UNIQUE(鏡 ghost_ring/
//   starlight_ring 之做法：僅以 set("unique",1) 作風味標記)。⚠ 既定義自訂 init()/
//   do_insert()/do_use()，依 lesson #11 斷「不」replace_program。

#include <ansi.h>

inherit ITEM;

// 七彩石房路徑——招喚渾沌獸之地。玩家須立於此方能招喚。
#define COLORSTONE_ROOM "/d/longdao/colorstone"
// 渾沌獸 NPC 路徑。
#define CHAOSBEAST      "/d/longdao/npc/chaosbeast"

int do_insert(string arg);
int do_use(string arg);
private int summon_chaosbeast(object me);

void create()
{
	set_name(HIW "渾沌印記" NOR,
		({ "chaos seal", "chaos mark", "渾沌印記" }) );
	set_weight(500);

	if( !clonep() ) {
		set("unit", "枚");
		set("value", 1);
		set("unique", 1);
		set("no_sell", 1);
		set("long",
			"一方七彩流轉、混沌未分的奇異印記。印身既非金石、亦非玉\n"
			"璧，而似一團將凝未凝、將散未散的混沌元氣所鑄——通體表面赤、\n"
			"橙、黃、綠、青、藍、紫七色光華緩緩交織迴盪，明滅不定，彷彿\n"
			"一整方天地初開、清濁未判的鴻濛之氣，盡被收攏進了這方寸之\n"
			"間。這是漕幫耆宿江隕將那枚蜈蚣之患所留的『破碎的印記』、合\n"
			"以一枚散落人間的『神之心』，以秘法熔煉而成的『渾沌印記』。\n"
			"凝神細看，那七色光華深處隱隱蟠著一頭混沌巨獸的模糊輪廓，正\n"
			"在那方寸鴻濛之中無聲地翻騰、嘶吼、伺機而動——傳聞持此印往天\n"
			"龍島島心神域旁的『七彩石』處，於身上『insert chaos seal』，\n"
			"便能將那印中所封、隨地流竄的渾沌獸自七彩石中招出。握之在\n"
			"手，但覺一股混沌而磅礡的元氣自掌心緩緩漫開，周身百骸俱為之\n"
			"一震。\n");
	}
	setup();
}

// 本印在玩家背包中，其 init() 必隨印入背包(get)而觸發——於此註冊第七章招喚動作。
void init()
{
	add_action("do_insert", "insert");
	add_action("do_use", ({ "用", "use" }) );
}

// 招喚：insert <chaos seal>（亦容 insert chaos seal into stone / into 七彩石）。
//   解析 arg（剝去尾綴 "into ..."），須指本印；合格則招喚渾沌獸。
int do_insert(string arg)
{
	object me = this_player();
	object seal;

	if( !me ) return 0;
	if( !arg || arg == "" )
		return notify_fail("你要將甚麼嵌入七彩石？（試試：insert chaos seal）\n");

	// 容 "insert chaos seal into stone" / "into 七彩石"：剝去 " into ..." 尾綴。
	sscanf(arg, "%s into %*s", arg);
	if( arg == "" )
		return notify_fail("你要將甚麼嵌入七彩石？（試試：insert chaos seal）\n");

	// arg 須指本渾沌印記（在玩家身上）。
	seal = present(arg, me);
	if( !objectp(seal) || seal != this_object() )
		return notify_fail("你身上並無這樣一方可嵌的印記。\n");

	return summon_chaosbeast(me);
}

// 招喚：用 渾沌印記 / use chaos seal。動詞「用」/「use」後接本印之名。
int do_use(string arg)
{
	object me = this_player();
	object seal;

	if( !me ) return 0;
	if( !arg || arg == "" )
		return notify_fail("你要用甚麼？（試試：insert chaos seal）\n");

	// arg 須指本渾沌印記（在玩家身上）。
	seal = present(arg, me);
	if( !objectp(seal) || seal != this_object() )
		return notify_fail("你身上並無這樣一方印記。\n");

	return summon_chaosbeast(me);
}

// 招喚渾沌獸。me=this_player()。守則：須立於七彩石、身負第七章旗標(main_canon7==1)。
//   合格時——先做完所有把關/訊息，最末才招喚 + destruct 本印（招喚/destruct-LAST，承
//   lesson #10）。
private int summon_chaosbeast(object me)
{
	object stone, beast;

	if( !me ) return 0;

	// 須已接第七章渾沌獸之約（main_canon7>=1）方能招喚。
	if( me->query("quest/main_canon7") < 1 )
		return notify_fail(
			"你凝望著印中七色光華深處那頭翻騰的混沌巨獸，可這招喚的門道，"
			"怕還得先去尋那漕幫的江隕老前輩問個明白。\n");

	// 渾沌獸已招出（main_canon7 已推進至 2 以上，或印該已沒入）——不重複招喚。
	if( me->query("quest/main_canon7") >= 2 )
		return notify_fail(
			"那渾沌印記中的混沌巨獸早已被你自七彩石中招出，此印七色光華已"
			"斂、混沌之氣已散，再無可招之物了。\n");

	// 須立於七彩石之地方能招喚。
	stone = environment(me);
	if( !objectp(stone) || base_name(stone) != COLORSTONE_ROOM )
		return notify_fail(
			"你催動手中的渾沌印記，那七色光華卻只在掌心微微一盪便又斂去——"
			"此地並無可承這混沌之力的法器。這渾沌印記，須往天龍島島心神域旁"
			"的『七彩石』處方能催發。\n");

	// 七彩石房內若渾沌獸已在場（防同房重招）——不重複招喚。
	if( present("chaosbeast", stone) )
		return notify_fail(
			"那七彩石上七色神光正自瘋狂炸響，渾沌獸已然自石中招出、正在四下"
			"暴起肆虐，無須再招！\n");

	// —— 合格招喚：先出高潮 message，最末才招喚渾沌獸 + destruct 本印（招喚/destruct
	// 殿後，承 lesson #10：destruct/招喚自身後其後碼不保證續行）——
	message_vision(
		HIW "$N將那方七彩流轉的渾沌印記凝神按上七彩石——只聽『轟』地一聲撼天動"
		"地的巨響，那印中所封的混沌元氣霎時自七色光華中傾瀉而出、盡數沒入石中！"
		"七彩石上赤橙黃綠青藍紫七色神光驟然瘋狂大綻、絞成一片亙古的混沌風暴，自"
		"那風暴最深處，一頭通體流轉著七彩混沌之力、隨地流竄的渾沌巨獸應聲破石而"
		"出，仰天發出一聲撕裂天地的咆哮——渾沌獸，現身了！\n" NOR,
		me);

	// 招喚渾沌獸入七彩石房。
	beast = new(CHAOSBEAST);
	if( objectp(beast) )
		beast->move(stone);

	// 渾沌印記既已沒入七彩石，destruct（必置於上方把關/訊息/招喚「之後」——destruct-
	// LAST，承 lesson #10）。
	destruct(this_object());

	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc

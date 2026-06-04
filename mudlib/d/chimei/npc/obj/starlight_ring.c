// starlight_ring.c -- 正史主線第五章「四鬼任務」的終局聖物兼交差信物：星光環。
//
// 來歷（承接 canon 主線樹 docs 05 L50「消滅後得星光 ring」、L189「insert seal of
//   fire/storm/water/thunder 把四片 seal 插入星光 ring」）：
//   山林川原四鬼——赤魈、青蛛、濁魚、旱魃——盡數誅於卯天樹下之際，那座鎮鬼三百年
//   的封印徹底崩解，自封印最深處、四鬼元神湮滅所凝的一點清光中，誕出這一枚通體
//   流轉著星河微芒的奇環。它是四鬼之患終獲了結的鐵證，更是日後了結十三靈、再戰
//   侮天鬼的終局之鑰——環上天然生著四道空槽，正待四神(火/天龍/雷/風)之 seal 嵌
//   入；湊全四片完整 seal、插入此環，方能行那技能重置(reset)、開啟十三靈最終任務。
//
// 用法（第五章交差 + 第六章四神嵌印）：
//   * 持此環回漕幫禮堂(/d/caobang/hall.c)交與江隕，ask jiangyun about 四鬼，繳交
//     領賞、為四鬼任務作結（亦可 wear ring 戴在指上；交差走 ask-path 為主）。
//   * 此即 docs 主線樹終局所載、四神/十三靈 arc 將需的「星光 ring」——故 ids 兼收
//     英文 "starlight ring"/"ring" 與中文「星光」。
//   設 no_sell：終局聖物干係十三靈最終任務，玩家須一路帶在身邊，斷不可變賣。
//
// 【第六章「四神任務」嵌印機制（本檔 init()+do_insert() 落實）】（承接 docs 05 L52-
//   54 四神任務、L68 reset 流程「insert 4 seal on ring」；江隕 jiangyun.c L108 所言：
//   集得火、天龍、雷、風四神的完整封印，以四片神印嵌入這星光環，另有一番驚天動地的
//   造化）：
//   * 本環在玩家背包中，其 init() 必隨環入背包(get)而觸發——故於 init() 註冊 insert
//     動作(add_action "do_insert","insert")。玩家於身上『insert <seal>』(亦容
//     『insert <seal> into ring』/『into 星光環』)，將四神之印逐一嵌入環上空槽。
//   * 每嵌一片合格神印(身上有該印、main_canon6>=1、該印尚未嵌)：quest/main_canon6_
//     seals +1、記該印已嵌(quest/main_canon6_seal_<fire|dragon|thunder|wind>=1)、該
//     印 destruct(沒入環中)、message。⚠ destruct(seal) 務必置於計數/旗標更新「之後」
//     (destruct-LAST，承 lesson #10)。
//   * 第四片相異神印嵌入(main_canon6_seals 達 4)且 main_canon6==1 時：推進 main_
//     canon6 1->2（務必置於該印 destruct「之前」）+ 高潮 message（星光環四道空槽四
//     色神光齊綻）。持四印齊嵌的星光環回漕幫禮堂交江隕交差(main_canon6==2)。
//   * 防越界：main_canon6<1 者嵌印不計、不推進；已嵌之印不重複計；不 re-advance(僅
//     main_canon6==1 方推進至 2)。
//
// 注意：本環為逐玩家掉落/clone 交付的終局聖物，不 inherit F_UNIQUE(鏡 chuanling/
//   ghost_ring 之做法：僅以 set("unique",1) 作風味標記，免多人持環時的任何意外自
//   毀)。可戴在指上(F_FINGER_EQ)。⚠ 本環既定義自訂 init()/do_insert()，依 lesson #11
//   斷「不」replace_program。

#include <ansi.h>
#include <armor.h>

inherit F_FINGER_EQ;

int do_insert(string arg);

void create()
{
	set_name(HIW "星光環" NOR, ({ "starlight ring", "starlight", "ring", "星光" }) );
	set_weight(200);
	setup_finger_eq();

	if( !clonep() ) {
		set("wear_as", "finger_eq");
		set("unit", "枚");
		set("value", 1);
		set("unique", 1);
		set("no_sell", 1);
		set("long",
			"一枚輕靈剔透、彷彿不染半分塵滓的奇環。環身既非金石、亦非\n"
			"玉璧，而似一縷凝而不散的清光所鑄——通體流轉著一片細碎的星\n"
			"河微芒，明滅閃爍，宛若將一整片夜空的繁星收攏進了這方寸之\n"
			"間。這是山林川原四鬼盡數湮滅於卯天樹下封印之際，自那崩解的\n"
			"亙古封印最深處、四鬼元神所化的一點至清之光中誕出的聖物。凝\n"
			"神細看，環身之上天然生著四道淺淺的空槽，槽中清芒流轉不定，\n"
			"似在無聲地等待著甚麼——傳聞日後當集齊火、天龍、雷、風四方神\n"
			"祇之 seal，一一嵌入此環，方能成就那了結十三靈、再戰侮天鬼的\n"
			"終局大願。握之在手，但覺一股溫煦澄澈的星輝自掌心緩緩漫開，\n"
			"周身百骸俱為之一清。\n");
		set("wear_msg",
			"$N將那枚流轉著星河微芒的奇環套上手指，環上星輝霎時一盛，灑下一片清光。\n");
		set("remove_msg",
			"$N將那枚星光環自指上褪下，環上那一片流轉的星河微芒方才稍斂。\n");
	}
	setup();
}

// 本環在玩家背包中，其 init() 必隨環入背包(get)而觸發——於此註冊第六章嵌印動作。
void init()
{
	add_action("do_insert", "insert");
}

// 嵌印：insert <seal>（亦容 insert <seal> into ring / into 星光環）。把四神之印逐一
// 嵌入星光環。who=this_player()。
//   * 解析 arg（剝去尾綴 "into ..."），於玩家身上 present() 尋四神之印之一。
//   * 合格(身上有該印、main_canon6>=1、該印尚未嵌)：計數 +1、記該印已嵌、(第四片相
//     異印嵌入且 main_canon6==1 時)推進 main_canon6 1->2 + 高潮 message，末了 destruct
//     該印(沒入環中)。⚠ destruct(seal) 殿後（destruct-LAST，承 lesson #10）。
int do_insert(string arg)
{
	object me = this_player();
	object seal;
	string sid, fkey;
	int n;

	if( !me ) return 0;
	if( !arg || arg == "" )
		return notify_fail("你要嵌甚麼進這星光環？（試試：insert seal of fire）\n");

	// 容 "insert <seal> into ring" / "into 星光環"：剝去 " into ..." 尾綴，arg 取
	// "into" 之前的神印名（add_action 已剝去前導動詞與空白，無 "into" 者 arg 原樣）。
	sscanf(arg, "%s into %*s", arg);
	if( arg == "" )
		return notify_fail("你要嵌甚麼進這星光環？（試試：insert seal of fire）\n");

	// 須已接第六章四神之約（main_canon6>=1）方能嵌印。
	if( me->query("quest/main_canon6") < 1 )
		return notify_fail(
			"你凝神望著環上那四道淺淺的空槽，槽中清芒流轉不定，似在等待"
			"著甚麼——可你手上並無甚麼可嵌之物，這嵌印的門道，怕還得先去尋"
			"那漕幫的江隕老前輩問個明白。\n");

	// 於玩家身上尋 arg 所指之物，須正是四神之印之一。
	seal = present(arg, me);
	if( !objectp(seal) || environment(seal) != me )
		return notify_fail("你身上並沒有這樣一枚神印可嵌。\n");

	// 比對四神之印 id，定出其對應的嵌印旗標 key 與顯名（fkey）。
	if( seal->id("fire seal") ) {
		sid  = "quest/main_canon6_seal_fire";
		fkey = HIR "火神之印" NOR;
	} else if( seal->id("dragon seal") ) {
		sid  = "quest/main_canon6_seal_dragon";
		fkey = HIC "天龍之印" NOR;
	} else if( seal->id("thunder seal") ) {
		sid  = "quest/main_canon6_seal_thunder";
		fkey = HIM "雷神之印" NOR;
	} else if( seal->id("wind seal") ) {
		sid  = "quest/main_canon6_seal_wind";
		fkey = HIW "風神之印" NOR;
	} else {
		return notify_fail("這並非四神之印，嵌不進這星光環的空槽。\n");
	}

	// 該印若已嵌過（旗標已立），不重複計（防越界/重覆嵌）。
	if( me->query(sid) == 1 )
		return notify_fail("這一枚神印早已嵌入了星光環的空槽，無須再嵌。\n");

	// —— 合格嵌印：先做完所有計數/旗標更新與推進、message，最後才 destruct 該印 ——
	// 計數 +1（封頂於 4）。
	n = me->query("quest/main_canon6_seals");
	if( n < 4 ) n++;
	me->set("quest/main_canon6_seals", n);
	me->set(sid, 1);   // 記該印已嵌。

	message_vision(
		HIW "$N將那枚" + fkey + HIW "凝神嵌入星光環上一道淺淺的空槽——只聽"
		"『鏘』地一聲清越的鳴響，那神印霎時化作一縷流光沒入環中，環上那一道"
		"空槽便亮起了一團相應的元素神光，與環身流轉的星河微芒交映生輝！\n" NOR,
		me);

	// 第四片相異神印嵌入（計數達 4）且 main_canon6==1：推進 1->2（務必置於 destruct
	// 之前——承 lesson #10/#11）+ 高潮 message。防 re-advance：唯 main_canon6==1 方推進。
	if( n >= 4 && me->query("quest/main_canon6") == 1 ) {
		me->set("quest/main_canon6", 2);
		tell_object(me,
			HIY "四片完整神印盡數嵌入星光環的空槽之際，環上那四道空槽的火"
			"赤、龍青、雷紫、風白四色元素神光驟然齊齊大綻、轟然合而為一——整"
			"枚星光環霎時化作一輪流轉著火、天龍、雷、風四神之力的璀璨光環，那"
			"四方神祇湮滅所凝的滔天神威自環中浩浩漫開，灼得你睜不開眼！這了結"
			"四神的鐵證，至此功成——是時候帶著這枚四神之力齊備的星光環，回漕幫"
			"禮堂去尋江隕老前輩覆命了。\n" NOR);
	}

	// 該印既嵌入環中，destruct（必置於上方計數/旗標/推進邏輯「之後」——destruct-LAST，
	// 承 lesson #10：destruct 後其後要緊邏輯不保證續行）。
	destruct(seal);

	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc

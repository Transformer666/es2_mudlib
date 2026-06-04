// huang_jade_pei.c -- 京畿渡口戒言大師相贈的護身信物：黃玉佩。
//
// 來歷（承接 canon：docs 01/05「戒言大師 @ 京畿渡口 → 給黃玉佩」）：
//   京畿城內漕運渡口邊，那座飄著青布招子的板棚旁，常有一位掛單於此的方外
//   高僧——人稱戒言大師。大師早年遍歷江湖，看盡世間紛擾，晚來只在這渡口邊
//   結一草庵，望著南來北往的漕船，替過客誦一段平安經。大師隨身有一枚溫養
//   多年的黃玉佩，玉中蘊著他半生戒貪戒嗔、清靜守一的定力。他見有心向道、
//   肯為這天下蒼生奔走的少俠，便將這枚玉佩相贈，盼它能護持少俠的心神，於
//   江湖風波中多一分安定。
//
// 用法：束(wear pei / wear jade)於腰間即可——護身信物，略增護甲，又因其溫養
//   人心、固本培元之效，佩之膂力稍長(str+2)。
//   設 no_sell：大師一片清靜心意，玩家留著護身，不宜變賣。
//
// 設計：玉佩乃懸於腰間的佩飾，故取 F_WAIST_EQ(腰部裝備)為基。其 str 加成走
//   apply_armor/waist_eq/str，穿戴時由 armor 一脈將之套入 query_temp("apply/str")
//   (見 feature/attribute.c::query_attr 讀 "apply/"+what)，與 hunter_necklace 之
//   apply_armor/neck_eq/spi 同式。量級從輕(str+2、armor+3)，定位為護身信物而非神兵。

#include <ansi.h>
#include <armor.h>

inherit F_WAIST_EQ;

void create()
{
	set_name(HIY "黃玉佩" NOR, ({ "huang jade pei", "jade pei", "pei", "黃玉佩", "玉佩" }) );
	set_weight(300);
	setup_waist_eq();

	if( !clonep() ) {
		set("wear_as", "waist_eq");
		set("unit", "枚");
		set("value", 1);
		set("no_sell", 1);
		set("long",
			"一枚溫潤厚實的黃玉佩，色作熟栗般的暖黃，玉質瑩潤無瑕，入手\n"
			"沉沉，貼掌竟微微生溫。佩身雕作一輪渾圓的璧形，當中鏤著一個\n"
			"古樸的『戒』字，邊緣陰刻著一圈細密如髮的雲水紋路，盤旋不\n"
			"絕，宛若那渡口邊終年不歇的河水。系著玉佩的是一條揉得極韌的\n"
			"明黃絲絛，絛尾綴著兩枚小小的玉珠。京畿渡口那位戒言大師說，\n"
			"這玉是他結庵渡口、誦經守一足足數十載，以一身戒貪戒嗔的清靜\n"
			"定力日日溫養而成；佩之在身，但覺一縷溫煦而安定的氣息自玉中\n"
			"緩緩沁入心脾，連那縈繞不去的躁念都彷彿被熨平了幾分。大師\n"
			"言：心定則身固，這玉佩護的，是少俠那一點不教江湖風波撼動的\n"
			"本心。\n");
		set("wear_msg",
			"$N將那枚黃玉佩束上腰間，玉色暖黃，一縷溫煦安定的氣息隱隱沁入心脾。\n");
		set("remove_msg",
			"$N將那枚黃玉佩自腰間解下，那縷溫養人心的暖意方才稍斂。\n");
		set("apply_armor/waist_eq", ([
			"armor" : 3,
			"str"   : 2,
		]) );
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc

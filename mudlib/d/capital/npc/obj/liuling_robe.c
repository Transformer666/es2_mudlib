// liuling_robe.c -- 京畿神社李再延所贈之防具「六靈玄衣」(body armor)。
//
// 來源(doc)：docs/01-世界觀與劇情/05-主線任務與NPC.md「重要任務 NPC」表——
//   「李再延 @ 京畿神社 n-w-s → 給六靈玄衣」。本檔即落實那件六靈玄衣為一件
//   可穿的軀幹防具(F_ARMOR、wear_as "armor")。
//
// 立意：六靈者，傳人身六脈之靈也。此衣以玄色靈蠶之絲、雜六色靈絲緙織，貼身
//   而穿，能護周身六脈之要害，卸去刀劍之力，且隱隱固護心神——故曰「六靈玄衣」。
//
// apply 鍵之取捨(僅用 driver 確實會讀的 combat 鍵，鏡 obj/topgear/firescale_armor.c)：
//   "armor"   : 受擊時真正抵減傷害的護甲值(combat.c:277 query_temp("apply/armor"))
//   "defense" : 守勢/閃避之助(combat.c:81 query_temp("apply/defense"))
//   "attack"  : 攻擊能力之助(combat.c:72 query_temp("apply/attack"))
//   數值取中庸量級(armor 12 / defense 10 / attack 6)——較頂裝火鱗胸鎧(18/15/18)
//   為輕，合一件「任務贈防」之身價，不喧奪頂裝之鋒。
//
//   armor.c 之 setup_armor() 為空殼；護具之效全憑 apply_armor/<part> 一個 mapping；
//   穿戴時由 equip.c::do_equip 套用(apply())。
//
// 設 no_sell：任務贈物，不可變賣。ids 兼收中文(六靈玄衣/玄衣)與英文
//   (liuling robe / robe / armor)。

#include <ansi.h>
#include <armor.h>

inherit F_ARMOR;

void create()
{
	set_name(HIM "六靈玄衣" NOR, ({ "liuling robe", "liuling", "robe", "armor", "六靈玄衣", "玄衣" }) );
	set_weight(4000);
	setup_armor();

	if( !clonep() ) {
		set("unit", "件");
		set("value", 1);
		set("wear_as", "armor");
		set("no_sell", 1);
		set("long",
			"這是一件貼身而穿的玄色軟甲『六靈玄衣』。通體以玄色靈蠶之\n"
			"絲為地、雜入赤、青、黃、白、玄、紫六色細若髮絲的靈絲緙織而\n"
			"成﹐衣面看似柔軟無骨﹐入手卻沉沉地墜著一股韌勁﹐刀劍劈來竟\n"
			"如砍在牛皮韌革之上﹐難傷分毫。最奇的是那六色靈絲在衣上隱隱\n"
			"游走流轉﹐合著人身六脈的氣息明滅生輝﹐穿在身上﹐周身六脈要\n"
			"害俱在這一層靈衣護持之下﹐既卸得刀兵之力﹐又隱隱固護著一縷\n"
			"心神之清——傳聞乃京畿神社守木一脈祕傳的護身之物。\n");
		set("wear_msg",
			"$N將那件玄色的六靈玄衣貼身束上﹐衣上六色靈絲霎時順著六脈幽幽游走﹐隱隱泛起一線微光。\n");
		set("unequip_msg",
			"$N卸下身上的六靈玄衣﹐那六色靈絲的微光也隨之斂去。\n");
		set("apply_armor/armor", ([
			"armor"   : 12,
			"defense" : 10,
			"attack"  : 6,
		]) );
	}

	setup();
}

// vim: set ts=4 sw=4 syntax=lpc

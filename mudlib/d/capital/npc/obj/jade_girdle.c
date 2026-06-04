// jade_girdle.c -- 玄天教法王所贈的腰帶聖物：金絲翡翠帶 (jade girdle)。
//
// 來歷（承接 docs/01-世界觀與劇情/05-主線任務與NPC.md L116：
//   「玄天教法王 @ 京畿小酒館 → 給金絲翡翠帶」）：
//   玄天教（教主東方孤冥，見 docs 05 L88）一脈廣布帝都，這位法王每每微服
//   匿跡於朱雀大街的小樓客店裡，以閒談論武為樂，暗察天下英雄。少俠若得他
//   青眼，他便自腰間解下這條傳承教中的「金絲翡翠帶」相贈——帶以崑崙翠玉為
//   扣、千縷赤金細絲為帶身，束在腰間護住命門氣海，行功運氣時周身真氣為之
//   一束、收發由心，是玄天教中外門弟子夢寐難求的護身佳物。
//
// 機制（waist_eq 護腰，apply 鍵皆取 driver 確實會讀者）：
//   doc 之效果         本檔 apply 鍵           取用處
//   ──────────        ──────────────         ──────────
//   束氣護命（體魄）     "con"    : 2           feature/attribute.c:29 apply/con
//   崑崙翠玉壯力        "str"    : 2           feature/attribute.c:29 apply/str
//   護腰當身（護甲）     "armor"  : 4           feature/char/combat.c:277 apply/armor
//   收發由心（守勢）     "defense": 6           feature/char/combat.c:81  apply/defense
//   （元素/內功類 apply 鍵本 mudlib 版本未實作，從略以免無效鍵；量級取「贈與」
//     佳物之譜，遜於闇之魔戒 str+5 一類須以物易物的頂物——見 docs 05 L126。）
//   waist_eq 之 setup_waist_eq() 為空殼(feature/armor/waist_eq.c)，效力全憑
//   apply_armor/waist_eq 一個 mapping，束戴時由 equip.c::wear 套用。
//
// 設 no_sell：法王相贈的教中信物，玩家當隨身佩束，不可變賣（鏡 ghost_ring.c）。

#include <ansi.h>
#include <armor.h>

inherit F_WAIST_EQ;

void create()
{
	set_name(HIG "金絲翡翠帶" NOR,
		({ "jade girdle", "gold girdle", "girdle", "金絲翡翠帶", "翡翠帶", "腰帶" }) );
	set_weight(800);
	setup_waist_eq();

	if( !clonep() ) {
		set("wear_as", "waist_eq");
		set("unit", "條");
		set("value", 1);
		set("no_sell", 1);
		set("long",
			"這便是玄天教世代相傳的護身佳物『金絲翡翠帶』了。帶身以千\n"
			"縷赤金細絲密密織就﹐入手沉沉﹐隨光流轉泛著一層融融的暖金\n"
			"之色﹔正中嵌著一方溫潤剔透的崑崙翠玉作扣﹐玉色青翠欲滴﹐\n"
			"內裡幽幽似有一縷碧芒在流轉。束在腰間﹐恰恰護住命門氣海一\n"
			"線﹐行功運氣之際﹐周身真氣為這條金帶一束﹐登時收束如意、\n"
			"收發由心。相傳玄天教外門弟子要熬上十年苦功﹐方得教中法王\n"
			"青眼﹐解下這麼一條金絲翡翠帶相贈。\n");
		set("wear_msg",
			"$N將那條金絲翡翠帶束上腰間﹐帶扣上的崑崙翠玉幽幽泛起一線碧芒﹐"
			"周身真氣登時為之一束。\n");
		set("unequip_msg",
			"$N將金絲翡翠帶自腰間解下﹐那縷束氣護命的碧芒方才稍稍斂去。\n");
		set("apply_armor/waist_eq", ([
			"con"     : 2,
			"str"     : 2,
			"armor"   : 4,
			"defense" : 6,
		]) );
	}

	setup();
}

// vim: set ts=4 sw=4 syntax=lpc

// qingsi_rod.c -- 雪山妖妃肖麗穎所贈的釣具聖物：青絲釣竿。
//
// 來源(doc)：docs/01-世界觀與劇情/05-主線任務與NPC.md「重要任務 NPC」表——
//   「肖麗穎 (Xiao li ying) @ 雪山妖妃 → 給青絲釣竿、追風劍」。本檔即落實其
//   所贈之釣具「青絲釣竿」。docs 原列雪山一域未在本 mudlib 開出，本支線暫借
//   雪亭鎮河邊空地(d/snow/riverbank.c)為肖麗穎駐足之地（湍流臨水，正宜垂釣）。
//
// 基底（釣具 → F_STAFF）：青絲釣竿乃一桿丈餘長的釣竿，質地細長、可雙手持揮，
//   以兵器論最近『杖／桿』一類，故 inherit F_STAFF、setup_staff(...)。docs 雖
//   歸其於「釣具」，乃風味分類；於 LPC 兵器體系中以 F_STAFF 呈現最為貼切，
//   亦鏡同域 d/snow/npc/obj/cane.c(拐杖，F_STAFF) 之做法。
//
// 立意：竿身通體墨竹所製，纏著一縷不知何物所結的青絲為線——那青絲入水不沉、
//   遇風自動，傳是雪山妖妃以三千青絲挽就，垂之於潭，釣的不只是魚，更是這紅塵
//   裡的一點清靜。竿力雖不及名劍利刃，揮將起來卻自有一股柔韌綿長之勁。
//
// 給法：本竿由 d/snow/npc/xiaoliying.c::give_rod 逐玩家 new()+move 同步交付。
//   設 no_sell：此乃雪山妖妃親贈之物，玩家須帶在身邊，不可變賣。
//   不 inherit F_UNIQUE：逐玩家 clone+move，鏡 chuanling.c/ghost_ring.c 之做法，
//   僅以 set("unique",1) 作風味標記，免多人持竿時的任何意外自毀。

#include <ansi.h>
#include <weapon.h>

inherit F_STAFF;

void create()
{
	set_name(HIC "青絲釣竿" NOR, ({ "qingsi rod", "fishing rod", "rod", "青絲釣竿", "釣竿" }) );
	set_weight(2200);
	// 柔韌綿長之釣竿：勝尋常拐杖(1,19,130,0)些許，然非利兵之屬，皆在範圍之內。
	setup_staff(1, 20, 140, 2);

	if( !clonep() ) {
		set("wield_as", ({ "staff", "twohanded staff" }) );
		set("unit", "根");
		set("value", 1);
		set("rigidity", 14);
		set("unique", 1);
		set("no_sell", 1);
		set("long",
			"一根丈餘長、入手卻輕的釣竿。竿身以一截通體墨黑的老竹所製，\n"
			"竹節勻細，拂之溫潤如玉，叩之卻錚錚有金石之韻。竿梢繫著一縷\n"
			"說不出是何物所結的青絲為線——那青絲細若髮、青中泛碧，垂在風\n"
			"裡卻不見它隨風亂擺，反似有靈，自顧自地舒捲游走。傳是雪山妖\n"
			"妃肖麗穎以三千青絲一寸一寸挽就，垂之於寒潭，釣的不只是潭裡\n"
			"的魚，更是這滾滾紅塵裡難得的一點清靜。竿力雖遠不及名劍利刃，\n"
			"然這一桿柔韌綿長之勁揮將起來，倒也自有一番說不出的纏綿意味。\n");
		set("wield_msg",
			"$N將那根青絲釣竿輕輕一抖，竿梢那縷青絲便在風裡自顧自地舒捲開來，泛起一線幽碧的微光。\n");
		set("unwield_msg",
			"$N將青絲釣竿緩緩收起，那縷青絲方才乖乖地纏回竿梢，斂了那線幽碧的光。\n");
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc

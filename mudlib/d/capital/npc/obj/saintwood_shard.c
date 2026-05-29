// saintwood_shard.c -- 主線任務三「聖木探封」的信物：
//                      京畿神社守木老者自聖木舊址取下的一片殘木﹐其上猶
//                      鎮著三百年前那道將潰的封印之力﹐須帶回封山派交還
//                      陸抱朴師叔參詳

inherit ITEM;

void create()
{
	set_name("聖木殘片", ({ "saintwood shard", "shard" }) );
	set_weight(120);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "片");
		set("value", 1);
		set("long",
			"一片自皇城聖木舊址取下的殘木﹐約莫巴掌大小﹐木色黝黑如\n"
			"鐵﹐斷口處卻泛著一層幽幽的青芒﹐隱隱有暖意自掌心透來。相\n"
			"傳這聖木原是三百年前鎮著天地、封著侮天鬼之物的神木﹐後遭\n"
			"人攔腰斷去﹐這殘片乃是當年封印僅存的一鱗半爪。如今那青芒\n"
			"忽明忽暗﹐似明似滅——守木老者說﹐這便是封印將潰之兆。這等\n"
			"關乎舊案的物事﹐合該趕緊帶回封山派﹐交給追查此事多年的陸\n"
			"師叔。\n");
		set("no_sell", 1);
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc

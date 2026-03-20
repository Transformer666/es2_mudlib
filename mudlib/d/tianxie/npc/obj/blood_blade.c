// blood_blade.c - 血魔刀

inherit WEAPON;

void create()
{
	set_name("血魔刀", ({"blood blade", "blood_blade", "blade"}));
	set("long",
		"一柄通體血紅色的長刀﹐刀身上隱隱浮現著詭異的紋路﹐散發\n"
		"著令人不寒而慄的邪氣。刀柄處鑲嵌著一顆暗紅色的寶石﹐彷\n"
		"彿隨時會滴下鮮血。\n");
	set("weapon_type", "blade");
	set("damage", 85);
	set("weight", 3000);
	set("value", 5000);
	setup();
}

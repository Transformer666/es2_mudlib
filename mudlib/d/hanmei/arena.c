// Room: /d/hanmei/arena.c

inherit ROOM;

void create()
{
	set("short", "冷梅莊演武場");
	set("long", @LONG
這是冷梅莊的演武場﹐一片寬闊的平地以黃土夯實﹐四周立著一排
木人樁與兵器架。場上時時有弟子對拆劍招﹐劍光霍霍﹐喝聲不絕。場
邊一塊青石碑上刻著冷梅劍法的總訣﹐供弟子揣摩。往南可回到前院。
LONG
	);
	set("detail", ([
		"兵器架" : "兵器架上整齊地插著一柄柄練習用的木劍與鐵劍。
",
		"石碑" : "青石碑上刻著冷梅劍法的總訣﹐字句精簡﹐須得細細參詳方能領會。
",
		"木人樁" : "一排木人樁供弟子練習劈刺﹐樁身被劍痕劃得密密麻麻。
",
	]));
	set("outdoors", "snow");
	set("exits", ([
		"south" : __DIR__"yard",
	]));

	setup();
}
// vim: set ts=4 sw=4 syntax=lpc

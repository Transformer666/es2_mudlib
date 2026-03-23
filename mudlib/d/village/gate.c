// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "村口柵門");
	set("long", @LONG
村子的入口處立著一道簡陋的柵門﹐用幾根粗木樁和橫木釘成﹐雖然不算堅固﹐但也能擋住野獸的侵擾。柵門旁邊有一個小小的崗亭﹐是守衛值班的地方。柵門上方釘著一塊木板﹐上面歪歪扭扭地寫著「天寒村」三個字。
LONG
	);
	set("outdoors", "wilderness");
	set("objects", ([
		__DIR__"npc/guard" : 1,
	]));
	set("exits", ([
		"north" : "/d/road/wild_path2",
		"south" : __DIR__"entrance",
	]));

	setup();
	replace_program(ROOM);
}

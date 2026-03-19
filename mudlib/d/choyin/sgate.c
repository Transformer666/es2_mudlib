// Room: /d/choyin/sgate.c

inherit ROOM;

void create()
{
	set("short", "喬陰南門");
	set("long", @LONG
喬陰縣城的南門﹐比北門氣派得多。門樓上懸著一塊匾額﹐題著
「南薰門」三字。城門外是一條寬闊的官道﹐往南可通往五堂鎮。來來
往往的商旅和行人大多由此門進出﹐因此南門一帶比較繁忙。
LONG
	);
	set("objects", ([
		__DIR__"npc/cityguard" : 1,
	]));
	set("exits", ([
		"north" : __DIR__"sstreet",
		"south" : __DIR__"choyin_road",
	]));

	setup();
	replace_program(ROOM);
}

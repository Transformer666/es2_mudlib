// Room: /d/fengcheng/street2.c

inherit ROOM;

void create()
{
    set("short", "風城東巷");
    set("long", @LONG
這是一條狹窄的小巷﹐兩旁是灰色的石牆﹐牆頭上長著些枯黃
的野草。小巷雖然不寬﹐但來往的人卻不少﹐因為南邊通向風城的
集市﹐是城中最熱鬧的地方之一。地面上鋪著不太平整的石板﹐石
板的縫隙中積著薄薄的一層冰霜。
LONG
    );
    set("outdoors", "town");
    set("exits", ([
        "north" : __DIR__"store",
        "south" : __DIR__"market",
    ]));

    setup();
    replace_program(ROOM);
}

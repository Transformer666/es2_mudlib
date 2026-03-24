// Room: /d/fengcheng/yamen.c

inherit ROOM;

void create()
{
    set("short", "風城衙門");
    set("long", @LONG
風城衙門坐落在城隍廟東側﹐門口立著兩根高大的石柱﹐上面刻
著「公正廉明」四個大字。衙門的大門平時緊閉﹐門前的石階上蹲
著兩隻石獅。因為風城地處邊陲﹐衙門的規模並不大﹐但門口站崗
的衙役個個彪悍﹐手持水火棍﹐目光如炬。
LONG
    );
    set("no_fight", 1);
    set("objects", ([
        __DIR__"npc/patrol" : 1,
    ]));
    set("detail", ([
        "石柱" : "兩根高大的石柱﹐上面的字跡經過風雪侵蝕已略有模糊。\n",
        "石獅" : "兩隻石獅子﹐雖然不大﹐但雕工頗為精細﹐蹲在門前頗有幾分威嚴。\n",
    ]));
    set("exits", ([
        "west" : __DIR__"temple",
    ]));

    setup();
    replace_program(ROOM);
}

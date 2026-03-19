inherit ROOM;

void create()
{
    set("short", "暗牢");
    set("long", @LONG
一間陰暗潮濕的地牢﹐四壁嵌著鐵環和鐵鏈。地上散落著幾根枯骨
﹐不知是何年何月的囚犯留下的。空氣中瀰漫著一股腐臭的氣味。
LONG
    );
    set("exits", ([
        "east" : __DIR__"hall",
    ]));

    setup();
    replace_program(ROOM);
}

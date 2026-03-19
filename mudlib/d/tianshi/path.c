inherit ROOM;

void create()
{
    set("short", "山間石階");
    set("long", @LONG
一條蜿蜒的石階從真天神殿延伸而出﹐沿著山壁向上攀升。石階兩
旁種著翠竹﹐竹葉在風中沙沙作響。遠處隱約可見一座道觀的飛簷。
LONG
    );
    set("outdoors", "mountain");
    set("exits", ([
        "west" : "/d/wutang/temple",
        "east" : __DIR__"gate",
    ]));

    setup();
    replace_program(ROOM);
}

inherit ROOM;

void create()
{
    set("short", "玄天小徑");
    set("long", @LONG
從真天神殿北面延伸出一條幽靜的小徑﹐兩旁種著高大的松柏﹐遮
天蔽日。小徑上鋪著青石板﹐石板上長滿了青苔﹐看起來已有些年月。
LONG
    );
    set("outdoors", "mountain");
    set("exits", ([
        "south" : "/d/wutang/temple",
        "north" : __DIR__"gate",
    ]));

    setup();
    replace_program(ROOM);
}

inherit ROOM;

void create()
{
    set("short", "冷梅莊大門");
    set("long", @LONG
冷梅莊的大門古樸典雅﹐門楣上掛著一塊白玉匾額﹐上書「冷梅莊」
三個銀鉤鐵劃的大字。門前種著兩株老梅﹐枝幹蒼勁如鐵。
LONG
    );
    set("exits", ([
        "west"  : __DIR__"road",
        "north" : __DIR__"yard",
    ]));

    setup();
    replace_program(ROOM);
}

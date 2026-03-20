// Room: /d/baiyao/valley_path.c

inherit ROOM;

void create()
{
    set("short", "谷中小徑");
    set("long", @LONG
峽谷中的小徑蜿蜒曲折，兩旁的岩壁高聳入雲，只留下一線天光。
地上鋪滿了落葉和枯枝，踩上去發出咯吱的聲響。路邊長著各種珍稀
的藥材，有些還開著五顏六色的小花。空氣中瀰漫著濃郁的草藥香氣，
令人精神一振。
LONG
    );
    set("outdoors", "mountain");
    set("exits", ([
        "north" : __DIR__"entrance",
        "east" : __DIR__"herb_garden",
        "south" : __DIR__"waterfall",
    ]));

    setup();
    replace_program(ROOM);
}

// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "幻霧觀");
    set("long", @LONG
幻霧觀終年籠罩在一片神秘的迷霧之中，視野所及不過數步之遙。
霧氣中不時閃爍著奇異的光芒，眼角餘光處隱約可見各種虛幻的影像。
這裡是茅山修煉幻術的所在，據說長年在此修行可以洞悉虛實之道。
LONG
    );
    set("exits", ([
        "east" : __DIR__"gate",
    ]));

    setup();
    replace_program(ROOM);
}

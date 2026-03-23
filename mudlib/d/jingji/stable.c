// Room: /d/jingji/stable.c

inherit ROOM;

void create()
{
    set("short", "馬房");
    set("long", @LONG
衙門後方的一間寬敞馬房﹐幾匹膘肥體壯的駿馬站在各自的馬廄裡﹐
不時打著響鼻。一名馬伕正拿著刷子細心地為一匹棗紅馬梳理鬃毛﹐
地上鋪著厚厚的乾草﹐空氣中混雜著馬匹和青草的氣味。
LONG
    );
    set("exits", ([
        "west" : __DIR__"garden",
    ]));

    setup();
    replace_program(ROOM);
}

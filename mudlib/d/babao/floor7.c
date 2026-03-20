// Room: /d/babao/floor7.c

inherit ROOM;

void create()
{
    set("short", "八寶樓七樓 - 毒窟");
    set("long", @LONG
第七層的空氣中瀰漫著一股令人頭暈目眩的甜膩氣味。地上擺放著
三十個骷髏頭，每個骷髏頭裡都盛著白色的粉末。四周燃著無數蠟燭，
燭光搖曳，映照著滿室的詭異光影。「鬼見愁」施鈺就藏身此處，此人
武功不算高強，卻精通各種毒術，令人防不勝防。
LONG
    );
    set("objects", ([
        "/d/wutang/npc/shi_yu" : 1,
    ]));
    set("detail", ([
        "骷髏頭" : "三十個骷髏頭整齊排列，裡面盛著不知名的白色粉末。\n",
        "蠟燭" : "無數蠟燭燃著昏黃的火焰，蠟油流得到處都是。\n",
    ]));
    set("exits", ([
        "down" : __DIR__"floor6",
        "up" : __DIR__"floor8",
    ]));

    setup();
    replace_program(ROOM);
}

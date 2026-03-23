// Room: /d/road/fengbai_road.c

inherit ROOM;

void create()
{
    set("short", "楓柏村外的小路");
    set("long", @LONG
一條蜿蜒的鄉間小路穿過一片楓樹和柏樹交錯的樹林﹐秋天時
節﹐紅黃相間的落葉鋪滿了整條路。空氣中帶著一股清新的草木香
氣﹐偶爾可以聽到遠處傳來雞犬相聞的聲音。往北是楓柏村的南口﹐
往南可以接上通往五堂鎮方向的官道。
LONG
    );
    set("outdoors", "road");
    set("exits", ([
        "north" : "/d/fengbai/sgate",
        "south" : __DIR__"road3",
    ]));

    setup();
    replace_program(ROOM);
}

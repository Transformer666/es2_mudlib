inherit ROOM;

void create()
{
    set("short", "三清殿");
    set("long", @LONG
三清殿是天師道觀的正殿﹐殿中供奉著三清道祖的神像﹐香煙繚繞
﹐莊嚴肅穆。殿內兩側的壁畫描繪著道家傳說中的仙境﹐栩栩如生。
一位道士正在殿前靜坐調息。
LONG
    );
    set("objects", ([
        __DIR__"npc/master" : 1,
    ]));
    set("exits", ([
        "south" : __DIR__"courtyard",
        "west"  : __DIR__"quarters",
        "north" : __DIR__"altar",
    ]));

    setup();
    replace_program(ROOM);
}

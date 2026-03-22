// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "三清殿");
    set("long", @LONG
三清殿是茅山派的主殿，殿內供奉著三清祖師的神像，香煙繚繞，
莊嚴肅穆。大殿正中擺放著一座青銅香爐，爐中檀香嫋嫋升起。殿
柱上懸掛著道家經文的楹聯，地面以青石板鋪就，光潔如鏡。殿後有
一道月門通往掌門靜室。
LONG
    );
    set("exits", ([
        "south" : __DIR__"gate",
        "north" : __DIR__"lingyun",
        "east"  : __DIR__"quarters",
    ]));

    setup();
    replace_program(ROOM);
}

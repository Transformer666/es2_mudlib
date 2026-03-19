// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "內堂");
    set("long", @LONG
虎刀門的內堂，牆上掛著歷代掌門的畫像，每一位都是虎目圓睜，
神態威嚴。正面供桌上擺放著歷代祖師的牌位，香煙裊裊。一旁的兵器
架上陳列著門派的幾把鎮派寶刀，刀身上隱隱可見虎紋暗花。
LONG
    );
    set("exits", ([
        "south" : __DIR__"hall",
    ]));
    set("no_fight", 1);

    setup();
    replace_program(ROOM);
}

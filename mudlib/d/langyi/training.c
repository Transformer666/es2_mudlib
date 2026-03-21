inherit ROOM;

void create()
{
    set("short", "暗器房");
    set("long", @LONG
暗器房中陳列著各式各樣的暗器﹐有飛刀、暗鏢、毒針、袖箭等﹐
琳瑯滿目。牆上掛著幾個人形靶﹐上面插滿了暗器。一名弟子正在練習
拋擲飛刀﹐手法迅捷而準確。
LONG
    );
    set("exits", ([
        "west" : __DIR__"hall",
    ]));

    set("objects", ([
        __DIR__"npc/disciple" : 2,
    ]));

    setup();
    replace_program(ROOM);
}

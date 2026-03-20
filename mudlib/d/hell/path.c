// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "黃泉路");
    set("long", @LONG
一條陰森的石路在迷霧中向前延伸﹐路的兩旁立著一排排慘白色
的石柱﹐柱上雕刻著各種鬼怪的面孔﹐在昏暗的光線下顯得猙獰可怖
。路面上不時冒出幾縷青色的磷火﹐忽明忽暗地飄蕩著。偶爾有幾道
模糊的身影從霧中飄過﹐分不清是活人還是幽魂。前方隱約可見一座
高聳的塔樓。
LONG
    );
    set("detail", ([
        "石柱" : "慘白色的石柱上雕刻著各種鬼怪的面孔﹐有的呲牙咧嘴﹐有的怒目圓睜﹐栩栩如生。\n",
        "磷火" : "青色的磷火在地面上飄蕩﹐靠近時會感到一陣刺骨的寒意。\n",
    ]));
    set("objects", ([
        __DIR__"npc/wandering_ghost" : 2,
    ]));
    set("exits", ([
        "south" : __DIR__"entrance",
        "north" : __DIR__"tower_base",
    ]));

    setup();
    replace_program(ROOM);
}

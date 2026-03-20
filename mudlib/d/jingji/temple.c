// vim: syntax=lpc

#include <room.h>

inherit TEMPLE;

void create()
{
    set("short", "皇家寺院");
    set("long", @LONG
一座規模宏大的皇家寺院，琉璃瓦在陽光下閃爍著金色的光芒。
寺院大殿內供奉著三尊鎏金佛像，佛前的供桌上擺滿了鮮花瓜果和名
貴的線香。殿內的柱子上纏繞著金龍紋飾，地面鋪著漢白玉石板，盡
顯皇家氣派。幾名身著錦袈裟的高僧正在殿中誦經，梵音低沉悠遠。
LONG
    );
    set("exits", ([
        "east" : __DIR__"square",
    ]));
    set("no_fight", 1);
    set("objects", ([
        __DIR__"npc/temple_monk" : 1,
    ]));

    setup();
    replace_program(TEMPLE);
}

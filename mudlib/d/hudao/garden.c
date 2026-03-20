// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "後院");
    set("long", @LONG
內堂後方的一片小院落，院中種著幾棵枝幹粗壯的老榕樹，樹蔭
下擺著石桌石凳。院牆邊整齊地插著一排練功用的木刀，刀柄上磨出了
光亮的手印。角落裡有一口古井，井水清冽甘甜。這裡是虎刀門長輩們
閒暇時品茶論刀的所在。
LONG
    );
    set("exits", ([
        "south" : __DIR__"inner_hall",
    ]));

    set("objects", ([ __DIR__"npc/elder" : 1 ]));
    setup();
}

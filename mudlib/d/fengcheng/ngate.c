// Room: /d/fengcheng/ngate.c

inherit ROOM;

void create()
{
    set("short", "風城北門");
    set("long", @LONG
這裡是風城的北門﹐城門外就是通往天山的山路﹐凜冽的北風從
門洞中灌進來﹐吹得人幾乎站不穩。城門上方的城樓飽經風霜﹐牆
壁上的磚石被寒風侵蝕出一道道裂痕。北門是進出天山的要道﹐來
往的多是江湖中人﹐偶爾也能看到幾個裹著厚厚皮裘的獵戶。
LONG
    );
    set("outdoors", "town");
    set("objects", ([
        __DIR__"npc/guard" : 2,
    ]));
    set("detail", ([
        "城樓" : "城樓上插著幾面旗幟﹐在北風中獵獵作響﹐旗面已經被吹得破爛不堪。\n",
        "山路" : "城門外的山路蜿蜒向北﹐消失在茫茫天山之中。\n",
    ]));
    set("exits", ([
        "south" : __DIR__"temple",
    ]));

    setup();
    replace_program(ROOM);
}

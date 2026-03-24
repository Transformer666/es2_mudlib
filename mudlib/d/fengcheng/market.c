// Room: /d/fengcheng/market.c

inherit ROOM;

void create()
{
    set("short", "風城集市");
    set("long", @LONG
風城的集市規模不大﹐但因為靠近天山﹐這裡能買到不少中原罕
見的北地貨物。攤位上擺著各種皮毛、藥材和山珍野味﹐還有獵戶們
從山中帶回的獸骨獸牙。集市上的人大多穿得厚實﹐操著北方口音互
相寒暄。寒風中飄來陣陣烤肉的香氣﹐讓人忍不住多吸幾口。
LONG
    );
    set("outdoors", "town");
    set("objects", ([
        __DIR__"npc/hunter" : 1,
        __DIR__"npc/merchant" : 1,
    ]));
    set("detail", ([
        "皮毛" : "攤位上掛著各種獸皮﹐有狐皮、狼皮、鹿皮﹐還有幾張少見的白熊皮。\n",
        "攤位" : "攤位上擺著各種北地特產﹐從藥材到獸骨﹐琳瑯滿目。\n",
    ]));
    set("exits", ([
        "north" : __DIR__"street2",
        "east"  : __DIR__"forge",
        "south" : __DIR__"back_alley",
    ]));

    setup();
    replace_program(ROOM);
}

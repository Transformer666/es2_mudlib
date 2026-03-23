// Room: /d/luocheng/teahouse.c

inherit ROOM;

void create()
{
    set("short", "聚賢茶樓");
    set("long", @LONG
聚賢茶樓是羅城最有名的茶樓﹐二層木樓﹐飛簷翹角﹐頗有氣
派。樓下的大廳擺著十幾張八仙桌﹐茶客們三五成群地喝茶閒聊。
角落裡一個說書人正講得唾沫橫飛﹐引得滿堂喝彩。空氣中飄著龍
井茶的清香﹐夾雜著瓜子花生的香味。
LONG
    );
    set("no_fight", 1);
    set("objects", ([
        __DIR__"npc/storyteller" : 1,
        __DIR__"npc/tea_vendor" : 1,
    ]));
    set("detail", ([
        "八仙桌" : "紅漆八仙桌擦得鋥亮﹐桌上放著茶壺和茶杯。\n",
        "飛簷" : "茶樓的飛簷上掛著幾個紅燈籠﹐即使在白天也頗為醒目。\n",
    ]));
    set("exits", ([
        "north" : __DIR__"market",
    ]));

    setup();
    replace_program(ROOM);
}

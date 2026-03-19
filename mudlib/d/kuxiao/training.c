inherit ROOM;

void create()
{
    set("short", "演武場");
    set("long", @LONG
演武場中擺放著幾個木製的假人﹐每個假人的臉上都畫著不同的哭笑
表情。幾名弟子正在對著假人練習各種招式﹐口中時而大笑時而痛哭。
LONG
    );
    set("exits", ([
        "west" : __DIR__"yard",
    ]));

    setup();
    replace_program(ROOM);
}

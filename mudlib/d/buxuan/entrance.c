inherit ROOM;

void create()
{
    set("short", "沐華居門口");
    set("long", @LONG
從御史別院東面的小門出來﹐便是沐華居的入口。門楣上掛著一塊樸
素的木匾﹐上書「沐華居」三個飄逸的草書大字。門前種著幾株蘭花﹐
幽香陣陣。
LONG
    );
    set("exits", ([
        "west" : "/d/wutang/residence",
        "east" : __DIR__"garden",
    ]));

    setup();
    replace_program(ROOM);
}

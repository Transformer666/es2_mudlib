// Room: /d/wutang/inn_3f.c

inherit ROOM;

void create()
{
    set("short", "醇雨樓三樓");
    set("long", @LONG
三樓是客房區﹐走廊兩側排列著幾間簡單的客房﹐盡頭處有一扇
窗戶﹐透過窗戶可以看到遠處的武山﹐山腰處雲霧繚繞﹐隱約可以
看到一座古寺的輪廓。
LONG
    );
    set("no_fight", 1);
    set("exits", ([
	"down" : __DIR__"inn_2f",
    ]));

    setup();
    replace_program(ROOM);
}

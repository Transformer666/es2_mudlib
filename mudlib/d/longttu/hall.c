inherit ROOM;

void create()
{
    set("short", "龍圖閣大廳");
    set("long", @LONG
龍圖閣的大廳寬敞明亮﹐空氣中瀰漫著淡淡的草藥清香。廳中央擺
放著一張寬大的紫檀木桌﹐上面擺著一尊銅製丹爐的擺件。兩側牆上
掛著歷代閣主的畫像﹐個個儀態端莊。廳柱上雕刻著蟠龍圖案﹐寓意
龍圖閣的傳承源遠流長。
LONG
    );
    set("exits", ([
        "west"  : __DIR__"entrance",
        "east"  : __DIR__"garden",
    ]));

    setup();
    replace_program(ROOM);
}

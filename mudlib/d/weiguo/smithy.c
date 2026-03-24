// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "鐵匠鋪");
    set("long", @LONG
一間熱氣蒸騰的鐵匠鋪，爐火正旺，橘紅色的火焰映照著整間屋
子。一座大鐵砧擺在屋子正中央，砧面上佈滿了錘擊的痕跡。牆上掛著
各種鉗子、錘子和模具，地上散落著一些鐵屑。這裡主要為駐軍打造和
修補兵器盔甲，偶爾也接待過路的江湖客。鍛打聲叮叮噹噹，不絕於耳。
LONG
    );
    set("exits", ([
        "west" : __DIR__"street",
        "east" : __DIR__"east_street",
    ]));

    set("objects", ([ __DIR__"npc/smith" : 1 ]));

    setup();
    replace_program(ROOM);
}

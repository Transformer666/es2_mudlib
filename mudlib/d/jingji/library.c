// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "書院");
    set("long", @LONG
一座古色古香的書院，門楣上懸掛著「明德書院」的匾額。院內幾
間教室圍著一片小庭院，庭中種著幾棵桂花樹。書架上擺滿了四書五經
和各類典籍，桌案上還散落著學生們的習作。幾名身著儒衫的書生正搖
頭晃腦地誦讀經文，朗朗的讀書聲在院中迴盪。
LONG
    );
    set("exits", ([
        "east" : __DIR__"street",
    ]));
    set("no_fight", 1);
    set("objects", ([
        __DIR__"npc/scholar" : 2,
    ]));

    setup();
}

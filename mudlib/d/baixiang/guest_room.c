// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "客房");
    set("long", @LONG
一間簡素雅致的客房，專供遠道而來的信徒和旅人借宿。房中只有
一張木床、一張書桌和一個蒲團，桌上擺著一卷佛經和一盞油燈。窗外
可以看到庭院中菩提樹的枝葉，偶爾傳來悠遠的晚鐘聲，令人心生安寧。
LONG
    );
    set("exits", ([
        "south" : __DIR__"meditation",
    ]));
    set("no_fight", 1);

    setup();
    replace_program(ROOM);
}

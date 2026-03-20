// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "藏書閣");
    set("long", @LONG
大殿後方一座小巧的藏書閣，閣內整齊地排列著數排木製書架，上
面擺放著歷代封山派前輩留下的劍譜、心法手札和武學典籍。一些年代
久遠的竹簡已經泛黃，但字跡依然清晰可辨。書桌上攤開著一卷劍法圖
解，墨跡猶新，似乎有人剛剛在此研讀。
LONG
    );
    set("exits", ([
        "south" : __DIR__"main_hall",
    ]));
    set("no_fight", 1);
    set("objects", ([ __DIR__"npc/librarian" : 1 ]));

    setup();
}

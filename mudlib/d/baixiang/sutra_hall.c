// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "藏經閣");
    set("long", @LONG
一座三層高的藏經閣，樓內整齊地排列著一排排檀木書架，上面擺
滿了各類佛經典籍。從最古老的貝葉經到歷代高僧的手抄本，卷帙浩繁。
閣中瀰漫著陳年墨香和檀木的氣息，幾名年長的僧人正靜靜地翻閱著經
書，偶爾低聲交談幾句。窗外的菩提樹枝葉婆娑，灑下斑駁的光影。
LONG
    );
    set("exits", ([
        "west" : __DIR__"main_hall",
    ]));
    set("no_fight", 1);

    set("objects", ([
        __DIR__"npc/sutra_monk" : 1,
    ]));

    setup();
}

// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "膳堂");
    set("long", @LONG
弟子房北面的膳堂，面積不大但收拾得十分整潔。幾張長條桌椅排
列有序，牆角的灶台上擱著幾口鐵鍋。封山派弟子飲食簡樸，以山中野
菜、菌菇和米糧為主，但量大管飽。灶台上方的木架上晾著幾串風乾的
山菌，散發出淡淡的泥土芳香。
LONG
    );
    set("exits", ([
        "south" : __DIR__"quarters",
    ]));
    set("objects", ([ __DIR__"npc/cook" : 1 ]));

    setup();
}

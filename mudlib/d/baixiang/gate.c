// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "白象寺山門");
    set("long", @LONG
一座古樸的寺院山門前，豎立著一尊潔白如玉的石象，神態安詳莊
嚴。寺門內傳來陣陣誦經之聲，裊裊檀香隨風飄散而來。山門上方的
匾額寫著「白象寺」三個金色大字，在陽光下熠熠生輝。
LONG
    );
    set("exits", ([
        "south" : "/d/road/mountain_road2",
        "north" : __DIR__"courtyard",
    ]));

    setup();
    replace_program(ROOM);
}

inherit ROOM;

void create()
{
    set("short", "天師道觀山門");
    set("long", @LONG
道觀山門巍峨壯觀﹐門楣上懸掛著一塊金字匾額﹐上書「天師道
觀」四個大字。門兩側各立著一尊石獅﹐張牙舞爪﹐氣勢不凡。門前
的石階上﹐幾片落葉隨風飄舞。
LONG
    );
    set("exits", ([
        "west"  : __DIR__"path",
        "north" : __DIR__"courtyard",
    ]));

    setup();
    replace_program(ROOM);
}

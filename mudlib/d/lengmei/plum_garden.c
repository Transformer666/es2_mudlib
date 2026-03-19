inherit ROOM;

void create()
{
    set("short", "梅園");
    set("long", @LONG
梅園中種滿了各種品種的梅花﹐紅梅、白梅、綠梅交相輝映。園中
有一塊平整的空地﹐看痕跡是莊中弟子常常在此對練劍法的場所。
LONG
    );
    set("exits", ([
        "west" : __DIR__"yard",
    ]));

    setup();
    replace_program(ROOM);
}

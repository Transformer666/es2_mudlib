// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "馬廄");
    set("long", @LONG
帥帳東面的馬廄，養著十來匹軍中的戰馬。這些馬匹都是精挑細選
的良駒，毛色油亮，體格健壯。馬廄裡乾草的氣味混合著馬匹的體味，
一名馬夫正忙著給馬兒添加草料和清水。牆上掛著一排馬鞍和韁繩，
每一副都標記著對應馬匹的名字，管理得井井有條。
LONG
    );
    set("exits", ([
        "west" : __DIR__"command",
    ]));
    set("objects", ([
        __DIR__"npc/stablehand" : 1,
    ]));

    setup();
}

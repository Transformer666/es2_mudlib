// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "龍安寺");
    set("long", @LONG
一座香火鼎盛的城中寺廟，紅牆黃瓦在陽光下格外醒目。寺門前
的石階被往來的信眾踩踏得光滑如鏡，門內正殿供奉著一尊金身菩薩，
神態慈悲。殿前的大香爐中插滿了燃燒的香火，青煙裊裊升騰。幾位
善男信女正虔誠地跪在蒲團上祈福禱告。
LONG
    );
    set("exits", ([
        "east" : __DIR__"square",
    ]));
    set("no_fight", 1);

    set("objects", ([ __DIR__"npc/temple_monk" : 1 ]));

    setup();
}

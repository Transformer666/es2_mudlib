// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "兵器鋪");
    set("long", @LONG
一間前店後鋪的兵器鋪，門口掛著幾把嶄新的刀劍作為招牌。店
內牆壁上掛滿了各式兵器，從長槍大戟到短劍匕首，琳瑯滿目。後面
的作坊裡不時傳來叮叮噹噹的打鐵聲，混雜著淬火時發出的嘶嘶聲。
一股熾熱的鐵水味和煤煙味撲面而來，讓人感受到兵器鑄造的熱烈氣
氛。
LONG
    );
    set("exits", ([
        "west" : __DIR__"street",
    ]));

    set("objects", ([ __DIR__"npc/weaponsmith" : 1 ]));

    setup();
}

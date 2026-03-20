// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "兵器庫");
    set("long", @LONG
一排排的刀架整齊地排列著，從簡單的練習用木刀到精心鍛造的虎
紋寶刀，應有盡有。兵器庫的牆壁上掛滿了各種形制的刀具，有的刀身
寬厚，有的刀刃細長，每一把都保養得光可鑑人。空氣中瀰漫著淡淡的
磨刀油香味。
LONG
    );
    set("exits", ([
        "west"  : __DIR__"inner_hall",
        "north" : __DIR__"treasury",
    ]));
    set("no_fight", 1);

    setup();
    replace_program(ROOM);
}

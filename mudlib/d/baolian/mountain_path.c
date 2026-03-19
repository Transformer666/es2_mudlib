inherit ROOM;

void create()
{
    set("short", "蓮花山路");
    set("long", @LONG
一條石板路沿著山勢蜿蜒而上﹐兩旁種著一排排的蓮花﹐雖然此時
並非花開時節﹐但碧綠的荷葉鋪滿了路旁的水池﹐清風徐來﹐送來陣
陣清香。遠處隱約可見一座寺院的金頂。
LONG
    );
    set("outdoors", "mountain");
    set("exits", ([
        "south" : "/d/choyin/temple",
        "north" : __DIR__"gate",
    ]));

    setup();
    replace_program(ROOM);
}

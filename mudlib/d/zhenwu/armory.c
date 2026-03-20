// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "軍械庫");
    set("long", @LONG
營房北面的軍械庫，鐵門厚重，上著幾道鐵鎖。庫房內兵器排列
得整整齊齊，長矛插在木架上，弓箭掛在牆壁上，刀劍按照大小依序
擺放。幾面沾著血跡的戰旗被摺疊收好，放在角落的木箱裡。一名管
庫的老兵正在逐一清點武器的數量，嘴裡念念有詞。
LONG
    );
    set("exits", ([
        "south" : __DIR__"barracks",
    ]));
    set("no_fight", 1);
    set("objects", ([
        __DIR__"npc/armorer" : 1,
    ]));

    setup();
}

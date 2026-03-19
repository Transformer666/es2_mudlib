inherit ROOM;

void create()
{
    set("short", "經卷閣");
    set("long", @LONG
經卷閣中擺放著大量的道教經典和武學秘笈﹐書架從地面直達屋頂
。幾名教眾正在安靜地抄寫經文﹐偶爾翻動書頁的聲音在寂靜中格外
清晰。
LONG
    );
    set("no_fight", 1);
    set("objects", ([
        __DIR__"npc/attendant" : 1,
    ]));
    set("exits", ([
        "east" : __DIR__"hall",
    ]));

    setup();
    replace_program(ROOM);
}

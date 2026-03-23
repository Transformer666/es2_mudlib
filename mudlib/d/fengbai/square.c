// Room: /d/fengbai/square.c

inherit ROOM;

void create()
{
    set("short", "楓柏村口");
    set("long", @LONG
這裡是楓柏村的村口﹐因為村子四周種滿了楓樹和柏樹﹐因而得
名。秋天的時候﹐漫山遍野的楓葉火紅一片﹐煞是好看。村子雖小﹐
但因為位於五堂鎮通往黑風山的必經之路上﹐偶爾也會有旅人在此
歇腳。村口一棵巨大的柏樹下﹐立著一塊刻有「楓柏村」的石碑。
LONG
    );
    set("objects", ([
        __DIR__"npc/villager" : 1,
    ]));
    set("detail", ([
        "柏樹" : "一棵蒼勁的老柏樹﹐樹幹粗得要兩個人才能環抱﹐枝葉繁茂﹐遮出了一大片綠蔭。\n",
        "石碑" : "一塊半人多高的青石碑﹐上面刻著「楓柏村」三個字﹐字跡已經有些模糊了。\n",
    ]));
    set("exits", ([
        "north" : __DIR__"ngate",
        "south" : __DIR__"street1",
        "east"  : __DIR__"inn_hall",
        "west"  : __DIR__"temple",
    ]));

    setup();
    replace_program(ROOM);
}

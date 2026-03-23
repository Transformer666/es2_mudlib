// Room: /d/fengcheng/store.c

inherit ROOM;

void create()
{
    set("short", "雜貨鋪");
    set("long", @LONG
這裡是一間雜貨鋪﹐貨架上擺滿了各種日用品和北地特產。因為
風城靠近天山﹐所以這裡能買到不少中原罕見的山貨﹐像是各種藥材
、皮毛和乾糧。掌櫃是個精明的中年漢子﹐滿臉笑容地招呼客人。
LONG
    );
    set("objects", ([
        __DIR__"npc/vendor" : 1,
    ]));
    set("no_fight", 1);
    set("exits", ([
        "west" : __DIR__"square",
    ]));

    setup();
    replace_program(ROOM);
}

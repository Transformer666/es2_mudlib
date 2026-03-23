// Room: /d/luocheng/store.c

inherit ROOM;

void create()
{
    set("short", "百貨行");
    set("long", @LONG
這裡是羅城有名的百貨行﹐因為地處交通要道﹐各地的貨物都匯
聚於此。貨架上琳瑯滿目﹐從兵器護甲到日常用品﹐應有盡有。掌
櫃是個見多識廣的老商人﹐據說跟江湖上不少門派都有生意往來。
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

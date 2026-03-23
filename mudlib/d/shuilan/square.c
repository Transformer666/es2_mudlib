// Room: /d/shuilan/square.c

inherit ROOM;

void create()
{
    set("short", "水嵐縣廣場");
    set("long", @LONG
這裡是水嵐縣的中央廣場﹐水嵐縣因為靠近羿水南岸﹐水氣充沛﹐
常年瀰漫著一層薄薄的霧氣﹐因而得名。廣場不算太大﹐但四周的
建築錯落有致﹐白牆黑瓦﹐頗有江南水鄉的風韻。廣場中央有一座
八角涼亭﹐亭中立著一塊石碑﹐記載著水嵐縣的歷史。
LONG
    );
    set("objects", ([
        __DIR__"npc/villager" : 2,
    ]));
    set("detail", ([
        "涼亭" : "一座八角涼亭﹐飛簷翹角﹐頗為精緻。亭中有石桌石凳﹐供人歇息。\n",
        "石碑" : "石碑上記載著水嵐縣的歷史﹐據說這裡在百年前只是一個小漁村﹐後來因為渡口的興盛才逐漸發展成為縣城。\n",
    ]));
    set("exits", ([
        "north" : __DIR__"street1",
        "south" : __DIR__"street2",
        "east"  : __DIR__"store",
        "west"  : __DIR__"inn_hall",
    ]));

    setup();
    replace_program(ROOM);
}

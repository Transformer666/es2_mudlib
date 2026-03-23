// Room: /d/shuilan/store.c

inherit ROOM;

void create()
{
    set("short", "南貨鋪");
    set("long", @LONG
這裡是一間南貨鋪﹐賣的都是南方的特產。因為水嵐縣地處羿水
南岸﹐南北貨物都在此地交匯﹐所以這間鋪子裡的貨品還算齊全。
掌櫃是個瘦小的老頭﹐說話慢條斯理的﹐但算起賬來一點也不含糊。
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

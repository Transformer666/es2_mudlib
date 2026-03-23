// Room: /d/shuilan/teahouse.c

inherit ROOM;

void create()
{
    set("short", "臨水茶寮");
    set("long", @LONG
這是一間簡陋的茶寮﹐幾張竹桌竹椅隨意擺放著﹐頂上搭著一
片蘆葦編的涼棚﹐勉強遮住日頭。茶寮雖然簡陋﹐但位置極好﹐
坐在這裡可以遙望北邊的羿水﹐偶爾還能看到渡船往來。茶寮的老
闆是個話多的老頭﹐一邊沏茶一邊跟客人閒扯﹐天南地北的消息他
都知道一些。
LONG
    );
    set("no_fight", 1);
    set("objects", ([
        __DIR__"npc/tea_vendor" : 1,
    ]));
    set("detail", ([
        "竹桌" : "竹桌上擺著幾個粗瓷茶碗﹐茶碗邊沿已經磕了幾個小缺口。\n",
        "涼棚" : "蘆葦編的涼棚已有些年頭了﹐陽光從縫隙中灑落下來。\n",
    ]));
    set("exits", ([
        "west" : __DIR__"market",
    ]));

    setup();
    replace_program(ROOM);
}

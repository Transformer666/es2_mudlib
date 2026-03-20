// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "圓通寶殿");
    set("long", @LONG
圓通寶殿是天月庵的正殿﹐殿中供奉著一尊白玉觀世音菩薩坐像
﹐菩薩端坐蓮台之上﹐面容慈悲安詳﹐手持淨瓶﹐似要普度眾生。佛
像前的供桌上擺放著鮮花素果﹐兩側銅燈長明不滅。殿堂兩壁繪有觀
音菩薩三十二應化身的壁畫﹐色彩雖經歲月而略顯斑駁﹐但人物神態
依然栩栩如生。
LONG
    );
    set("detail", ([
        "觀音像" : "白玉雕成的觀世音菩薩坐像﹐高約一丈﹐端坐在蓮花座上﹐雕工精湛絕倫。\n",
        "壁畫" : "壁畫描繪了觀音菩薩的三十二種應化身﹐有救苦救難的﹐有降妖除魔的﹐每一幅都十分生動。\n",
        "銅燈" : "兩盞古銅油燈﹐燈火搖曳﹐將整座大殿映照得莊嚴肅穆。\n",
    ]));
    set("objects", ([
        __DIR__"npc/master" : 1,
    ]));
    set("exits", ([
        "south" : __DIR__"courtyard",
        "east"  : __DIR__"meditation",
        "west"  : __DIR__"quarters",
    ]));

    setup();
    replace_program(ROOM);
}

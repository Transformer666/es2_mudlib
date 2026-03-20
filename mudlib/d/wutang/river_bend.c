// Room: /d/wutang/river_bend.c
// Quest: 飲血丟在了哪裡？ (quest/yinxue_found_done)

inherit ROOM;

void create()
{
    set("short", "河灣");
    set("long", @LONG
沿著碼頭往南走﹐河流在這裡拐了一個大彎﹐水流變得平緩了許
多。河灣處形成了一個小小的淺灘﹐灘上堆積著不少被水流沖來的
枯枝和碎石。河岸邊長滿了蘆葦﹐在風中沙沙作響。淺灘的泥沙中
隱約可以看到一些被沖刷出來的東西﹐偶爾會有閃閃發光的物件夾
雜其中。這裡十分僻靜﹐很少有人來。
LONG
    );
    set("detail", ([
	"蘆葦" : "一叢叢蘆葦長得有一人多高﹐在風中搖曳﹐發出沙沙的聲響﹐如果有人躲在裡面恐怕很難發現。\n",
	"淺灘" : "河灣處的淺灘上堆積著枯枝和碎石﹐仔細翻找的話﹐說不定能找到些什麼。\n",
	"河水" : "河水在這裡變得平緩﹐清澈了不少﹐可以看到水底的鵝卵石和水草。\n",
    ]));
    set("objects", ([
	__DIR__"npc/boy" : 1,
    ]));
    set("outdoors", "wutang");
    set("exits", ([
	"north" : __DIR__"dock",
    ]));

    setup();
}

void init()
{
    ::init();
    add_action("do_search", "search");
    add_action("do_search", "dig");
}

int do_search(string arg)
{
    object me = this_player();

    if( !arg || strsrch(arg, "淺灘") < 0 && strsrch(arg, "泥沙") < 0
    &&  strsrch(arg, "沙") < 0 )
        return notify_fail("你要搜索什麼﹖試試 search 淺灘。\n");

    if( me->query("quest/yinxue_found_done") ) {
        write("你在淺灘的泥沙中仔細翻找﹐但除了碎石和枯枝之外什麼也沒發現。\n");
        return 1;
    }

    if( !me->query_temp("pending/yinxue_search") ) {
        write(
            "你蹲下身子﹐在淺灘的泥沙中仔細翻找。翻開幾層碎石和\n"
            "枯枝之後﹐你的手指觸碰到一個堅硬冰涼的東西﹐似乎是\n"
            "金屬。泥沙中隱約露出一抹暗紅色的光澤。\n"
            "也許再仔細挖一挖就能把它弄出來。\n");
        me->set_temp("pending/yinxue_search", 1);
        return 1;
    }

    write(
        "你用力將那東西從泥沙中拔了出來﹐竟然是一把通體血紅的\n"
        "長劍﹗劍身上的泥沙被河水沖去後﹐露出隱約流動的血絲紋\n"
        "路。握住劍柄的瞬間﹐你能感受到一股嗜血的渴望從劍身傳\n"
        "來。這把就是傳說中被丟棄在河中的名劍——「飲血」。\n");
    say(me->query("name") + "從淺灘的泥沙中挖出了一把血紅色的長劍。\n");

    me->set("quest/yinxue_found_done", 1);
    me->delete_temp("pending/yinxue_search");
    me->gain_score("quest", 120);
    clone_object("/obj/weapon/yinxue")->move(me);
    return 1;
}

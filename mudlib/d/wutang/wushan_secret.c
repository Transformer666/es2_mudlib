// Room: /d/wutang/wushan_secret.c
// Quest: 巫山之中神秘雕像有何秘密？
// Flow: player discovers secret room → opens stone chest → gets ancient scroll → reward

inherit ROOM;

void create()
{
    set("short", "巫山密室");
    set("long", @LONG
石像底下的石台竟然可以移動﹗推開石台﹐露出一個剛好容一人
通過的洞口﹐沿著狹窄的石階往下走﹐你來到了一個隱藏在洞窟深
處的密室。密室的牆壁上鑲嵌著幾顆夜明珠﹐發出幽幽的冷光﹐勉
強照亮了整個空間。地面上刻著一個巨大的八卦圖案﹐八卦的每個
方位都放著一塊刻有銘文的石碑。密室的一角放著一個古老的石匣﹐
上面佈滿了封印的痕跡。
LONG
    );
    set("detail", ([
	"夜明珠" : "幾顆鴿蛋大小的夜明珠鑲嵌在石壁中﹐散發著幽幽的青白色光芒﹐不知在這裡照耀了多少年。\n",
	"八卦" : "地面上刻著的八卦圖案線條流暢﹐每個卦位都放著一塊小石碑﹐碑上刻著對應的卦名和一段晦澀難懂的銘文。\n",
	"石匣" : "一個用整塊青石雕成的匣子﹐上面佈滿了複雜的封印符文﹐似乎可以試著打開(open)看看。\n",
	"石碑" : "八塊小石碑分別對應八卦的八個方位﹐碑上的銘文似乎記載著某種修煉法門或武學秘籍。\n",
    ]));
    set("exits", ([
	"up" : __DIR__"wushan_cave",
    ]));

    setup();
}

private void give_rewards(object player)
{
    object ob;

    if( !player || environment(player) != environment() ) return;

    ob = new(__DIR__"npc/obj/ancient_scroll");
    if( !ob->move(player) )
	ob->move(environment());

    player->set("quest/wushan_statue_done", 1);
    player->gain_score("quest", 200);
}

int do_open(string arg)
{
    object player = this_player();

    if( !arg || (strsrch(arg, "石匣") < 0 && strsrch(arg, "chest") < 0) )
	return notify_fail("打開什麼﹖\n");

    if( player->query("quest/wushan_statue_done") ) {
	write("石匣已經被打開過了﹐裡面空空如也。\n");
	return 1;
    }

    if( player->query_temp("pending/wushan_statue") ) {
	write("你已經取走了石匣中的東西。\n");
	return 1;
    }

    message_vision("$N小心翼翼地推開石匣的蓋子。\n", player);
    write("\n封印符文閃爍了幾下便黯淡了﹐石匣的蓋子緩緩滑開。\n");
    write("石匣裡面放著一卷泛黃的古卷﹐散發著一股淡淡的檀香。\n");
    write("你小心地將古卷取出。卷上記載著真天教的秘史和一段\n");
    write("關於巫山封印的詳細記錄。這份古卷或許對了解巫山的\n");
    write("秘密很有價值。\n\n");

    player->set_temp("pending/wushan_statue", 1);
    give_rewards(player);
    return 1;
}

void init()
{
    ::init();
    add_action("do_open", "open");
    add_action("do_open", "打開");
}

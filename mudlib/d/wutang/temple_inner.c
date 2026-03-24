// Room: /d/wutang/temple_inner.c
// Quest: 鎮天神廟藏著誰？
// Flow: examine 蒲團 → lift 蒲團 → find hidden journal → learn temple master's true identity

inherit ROOM;

void create()
{
    set("short", "神殿密室");
    set("long", @LONG
繞過神像﹐你發現在神殿的後方有一道隱蔽的小門。推門而入﹐
裡面是一間不大的密室﹐四面牆壁上掛滿了古老的經文和符咒。密
室中央擺著一張石桌﹐桌上放著一盞長明燈﹐燈火搖曳不定。石桌
旁邊有一個蒲團﹐似乎有人經常在此打坐修煉。密室的角落裡堆放
著一些竹簡和書卷﹐看起來年代十分久遠。
LONG
    );
    set("detail", ([
	"經文" : "牆壁上的經文用金色的墨水書寫﹐字體古樸蒼勁﹐似乎是某種失傳已久的經典。\n",
	"長明燈" : "一盞青銅長明燈﹐燈火微弱卻從不熄滅﹐不知是什麼原理。\n",
	"竹簡" : "角落裡的竹簡已經十分古舊﹐上面刻著密密麻麻的小字﹐記載著一些關於真天神殿歷史的內容。\n",
	"蒲團" : "一個已經磨得光滑的蒲團﹐看得出有人長年在此靜坐。仔細一看﹐蒲團下方的地面似乎有些不太對勁﹐好像可以翻開(lift)看看。\n",
    ]));
    set("no_fight", 1);
    set("exits", ([
	"north" : __DIR__"temple",
    ]));

    setup();
}

int do_lift(string arg)
{
    object player = this_player();

    if( !arg || (strsrch(arg, "蒲團") < 0 && strsrch(arg, "mat") < 0
    &&  strsrch(arg, "cushion") < 0) )
	return notify_fail("翻開什麼﹖\n");

    if( player->query("quest/temple_secret_done") ) {
	write("蒲團下的暗格已經被你打開過了﹐裡面空空如也。\n");
	return 1;
    }

    message_vision("$N翻開蒲團﹐露出了下方地面上的一個暗格。\n", player);
    write("\n蒲團下方的石板上有一個精巧的暗格﹗你小心翼翼地打開暗格﹐\n");
    write("裡面放著一本泛黃的手札。\n\n");
    write("手札上以蠅頭小楷寫道﹕\n");
    write("「吾乃真天教第十七代掌教﹐法號淨空。昔日真天教弟子數千﹐\n");
    write("遍佈天下﹐何其鼎盛。怎奈天道無常﹐教中遭逢大劫﹐門人離散﹐\n");
    write("道場盡毀。吾隱姓埋名﹐以住持之身守此最後一方淨土﹐只為看\n");
    write("護巫山封印﹐不令邪祟再禍人間。若有緣人見此手札﹐望知——\n");
    write("這神殿住持並非尋常老僧﹐而是真天教最後的掌教。吾之所學﹐\n");
    write("盡在此殿經文之中﹐有心人自可參悟。」\n\n");
    write("原來那位看似普通的神殿住持﹐竟是真天教最後一任掌教淨空﹗\n");
    write("你將手札小心放回暗格﹐心中對這位獨守道場的老人多了幾分敬意。\n\n");

    player->set("quest/temple_secret_done", 1);
    player->gain_score("quest", 150);
    return 1;
}

void init()
{
    ::init();
    add_action("do_lift", "lift");
    add_action("do_lift", "翻開");
    add_action("do_lift", "翻");
}

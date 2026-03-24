// Room: /d/wutang/wushan_cave.c
// Quest: 巫山之中神秘雕像有何秘密？
// Flow: examine 石台 → push 石台 → discover hidden passage down to wushan_secret

inherit ROOM;

void create()
{
    set("short", "武山洞窟");
    set("long", @LONG
這是一個幽深的山洞﹐洞壁上刻著一些奇異的符號﹐看起來十分
古老。洞窟的最深處矗立著一座石像﹐石像雕刻得栩栩如生﹐但面
目模糊﹐看不清是何方神聖。石像前面擺著一個石台﹐上面放著一
只殘破的香爐﹐似乎很久沒有人來祭拜了。
LONG
    );
    set("detail", ([
	"神像" : "一座高約八尺的石像﹐雕工精湛﹐但面目已經被歲月侵蝕得模糊不清﹐只能隱約看出是一個持劍的人形。\n",
	"石壁" : "石壁上刻著密密麻麻的符號﹐似乎是某種古老的文字﹐但你完全看不懂。\n",
	"石台" : "仔細觀察石台﹐你發現石台的底部似乎有一些磨損的痕跡﹐好像這個石台曾經被人推動(push)過。\n",
	"香爐" : "一只殘破的香爐﹐積滿了塵土﹐已經很久沒有人來祭拜了。\n",
    ]));
    set("exits", ([
	"south" : __DIR__"wushan_path3",
	"north" : "/d/yinjiao/secret_passage",
    ]));

    setup();
}

int do_push(string arg)
{
    object player = this_player();

    if( !arg || (strsrch(arg, "石台") < 0 && strsrch(arg, "stone") < 0
    &&  strsrch(arg, "台") < 0) )
	return notify_fail("推什麼﹖\n");

    if( query_temp("passage_revealed") ) {
	write("石台已經被推開了﹐露出了往下的通道。\n");
	return 1;
    }

    message_vision("$N用力推動石台﹐石台緩緩移開﹐發出沉悶的摩擦聲。\n", player);
    write("\n石台下方露出了一個剛好容一人通過的洞口﹗隱約可以看到\n");
    write("一條狹窄的石階通往下方的黑暗之中。\n\n");

    set_temp("passage_revealed", 1);
    set("exits", ([
	"south" : __DIR__"wushan_path3",
	"north" : "/d/yinjiao/secret_passage",
	"down"  : __DIR__"wushan_secret",
    ]));
    return 1;
}

void init()
{
    ::init();
    add_action("do_push", "push");
    add_action("do_push", "推");
}

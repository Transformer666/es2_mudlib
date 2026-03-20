// temple_master.c
// Quest: 鎮天神廟內藏著誰？
// Flow: ask who he is → listen to story → learn his identity → reward

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("神殿住持", ({"temple_master", "master"}));
    set_attr("int", 20);
    set_attr("wis", 25);
    set_attr("spi", 22);
    set_race("human");
    set_class("commoner");
    set_level(45);

    set("age", 70);
    set("attitude", "peaceful");
    set("long",
	"一個鬚髮皆白的老者﹐身穿一件素白的道袍﹐盤坐在神像前的蒲\n"
	"團上﹐雙目微閉﹐似乎正在入定。\n");
    set("chat_chance", 1);
    set("chat_msg", ({
	"住持微微睜開雙目﹐淡淡地說道﹕萬物有靈﹐善惡有報。\n",
    }));
    setup();
}

private void give_rewards(object player)
{
    object ob;

    if( !player || environment(player) != environment() ) return;

    ob = new(__DIR__"obj/jade_token");
    if( !ob->move(player) )
	ob->move(environment());

    player->set("quest/temple_master_done", 1);
    player->gain_score("quest", 150);
}

void init()
{
    ::init();
    if( !userp(this_player()) ) return;
    if( is_fighting() || is_chatting() ) return;

    if( this_player()->query("quest/temple_master_done") ) {
	do_chat("住持微微頷首﹐淡淡地說道﹕施主又來了﹐請坐。\n");
	return;
    }

    if( this_player()->query_temp("pending/temple_master") )
	do_chat("住持緩緩睜開雙目﹐似乎在等你開口。\n");
}

void relay_say(object ob, string msg)
{
    int stage;

    if( !userp(ob) ) return;
    if( is_fighting() || is_chatting() ) return;
    if( ob->query("quest/temple_master_done") ) return;

    stage = ob->query_temp("pending/temple_master");

    // Stage 0: initial contact
    if( !stage || stage == 0 ) {
	if( strsrch(msg, "誰") >= 0 || strsrch(msg, "住持") >= 0
	||  strsrch(msg, "身份") >= 0 || strsrch(msg, "來歷") >= 0
	||  strsrch(msg, "你是") >= 0 || strsrch(msg, "什麼人") >= 0 ) {
	    do_chat(({
		"住持緩緩睜開雙目﹐嘴角微微上揚。\n",
		"住持說道﹕老衲只是一個守廟的老人罷了﹐施主不必多問。\n",
		"住持說道﹕不過 ... 施主若是有緣﹐不妨在此坐坐﹐聽老衲說個故事。\n",
	    }));
	    ob->set_temp("pending/temple_master", 1);
	    return;
	}
    }

    // Stage 1: player shows interest in the story
    if( stage == 1 ) {
	if( strsrch(msg, "故事") >= 0 || strsrch(msg, "聽") >= 0
	||  strsrch(msg, "說") >= 0 || strsrch(msg, "有緣") >= 0
	||  strsrch(msg, "願意") >= 0 || strsrch(msg, "好") >= 0 ) {
	    do_chat(({
		"住持點了點頭﹐緩緩說道﹕這座神殿已有數百年的歷史。\n",
		"住持說道﹕當年天朝初建﹐此地曾是一處鎮守要地﹐負責監視巫山之中的封印。\n",
		"住持說道﹕老衲的師父﹐以及師父的師父﹐世代守護這裡﹐為的就是不讓山中的東西出來。\n",
		"住持沉聲道﹕那巫山洞窟之中﹐有一座古老的石像和一間密室 ...\n",
		"住持說道﹕密室之中封著的是什麼﹐老衲也不敢妄言﹐但若封印一旦被破 ...\n",
		"住持搖搖頭﹐不再說下去。\n",
	    }));
	    ob->set_temp("pending/temple_master", 2);
	    return;
	}
    }

    // Stage 2: player asks about the seal/secret
    if( stage == 2 ) {
	if( strsrch(msg, "封印") >= 0 || strsrch(msg, "密室") >= 0
	||  strsrch(msg, "什麼") >= 0 || strsrch(msg, "秘密") >= 0
	||  strsrch(msg, "後來") >= 0 || strsrch(msg, "然後") >= 0 ) {
	    do_chat(({
		"住持長嘆一聲﹐說道﹕罷了﹐能來到此處﹐便是有緣。\n",
		"住持說道﹕老衲俗姓白﹐師承真天教﹐法號「淨空」。\n",
		"住持說道﹕真天教早已式微﹐如今只剩老衲一人守著這最後的道場。\n",
		"住持說道﹕施主既然有心﹐老衲便將此事託付於你 — 若日後巫山有異動﹐切記告知官府。\n",
		"住持站起身﹐從蒲團下取出一塊玉牌﹐遞給你。\n",
		"住持說道﹕這是真天教的信物﹐拿著它﹐以後或許用得上。\n",
		(: give_rewards, ob :),
	    }));
	    return;
	}
    }
}

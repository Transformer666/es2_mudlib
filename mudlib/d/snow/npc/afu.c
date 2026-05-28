// afu.c -- 阿福，張婆婆的孫兒，雪亭鎮新手任務 1 的收件人
//
// 玩家從張婆婆處接下任務 (quest/snow_newbie==1) 後，把「油紙包」
// 帶到廣場中央交 (give) 給阿福；阿福收下後把玩家旗標設為 2，
// 玩家再回客棧向張婆婆領賞。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("阿福", ({ "afu" }) );
	set_race("human");
	set_class("commoner");
	set_level(1);

	set("gender", "male");
	set("age", 8);
	set("long",
		"一個八九歲的小男孩﹐光著腳丫子在大榕樹下跑來跑去﹐臉蛋紅撲\n"
		"撲的﹐看見生人也不怕﹐只是一個勁兒地咧著嘴笑。他便是客棧張\n"
		"婆婆的孫兒阿福了。\n");
	setup();
	carry_object("/obj/area/obj/cloth")->wear();
}

void init()
{
	::init();
	if( this_player() && interactive(this_player()) ) {
		int q = this_player()->query("quest/snow_newbie");
		if( q == 1 )
			do_chat((: command,
				"say 大哥哥﹐你是不是奶奶叫來的呀﹖奶奶有給我帶吃的麼﹖" :));
		else if( !is_fighting() && !is_chatting() )
			do_chat((: command, "say 嘻嘻﹐你也來爬樹麼﹖" :));
	}
}

// 收下油紙包：確認是任務信物且玩家任務進行中，推進旗標 1 -> 2
int accept_object(object who, object ob)
{
	if( !ob->id("pastry parcel") ) {
		do_chat((: command, "say 這個我不要啦﹗" :));
		return 0;
	}

	// 不是正在進行任務的玩家送來的（或已送過），就不再推進旗標
	if( who->query("quest/snow_newbie") != 1 ) {
		do_chat((: command, "say 嘻嘻﹐謝謝大哥哥﹗" :));
		return 1;	// 仍收下，避免油紙包卡在玩家身上
	}

	who->set("quest/snow_newbie", 2);
	do_chat(({
		"阿福迫不及待地拆開油紙包﹐裡頭果然是他最愛吃的點心。\n",
		(: command, "say 是奶奶做的點心﹗謝謝大哥哥﹗" :),
		(: command, "say 大哥哥快回去跟奶奶說一聲呀﹗" :),
	}));
	return 1;
}

int accept_fight()
{
	do_chat((: command, "say 哇﹗你好兇喔﹐我要去告訴奶奶﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc

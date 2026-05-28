// smith.c

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("鐵匠", ({ "smith", "tiejiang" }) );
	set_race("human");
	set_level(13);
	set_stat_maximum("kee", 80);
	set_attr("str", 19);
	set_attr("cor", 17);
	set_attr("cps", 15);
	set_attr("dex", 18);

	set("age", 45);
	set("gender", "male");
	set("long",
		"一個身材粗壯的鐵匠﹐袒著被爐火燻得黝黑的胸膛﹐手臂上的\n"
		"肌肉虬結﹐正掄起大鐵鎚﹐一下一下地敲打著鐵砧上的兵器。牆\n"
		"上掛著他打造的各式刀劍槍棍。你可以用 list 看他賣些什麼﹐\n"
		"用 buy 向鐵匠購買。\n");

	// 雪亭鎮鐵匠鋪﹐販售各門派入門弟子防身用的基本兵器。
	// 注意﹕F_VENDOR 以兵器物件本身的 "value" 為售價﹐
	//      此處 mapping 的數值僅代表庫存數量。
	// 所有兵器物件路徑均已確認存在 (詳見 /obj/area/obj/)。
	set("merchandise", ([
		"/obj/area/obj/woodsword"  : 20,  // 木劍   value  400
		"/obj/area/obj/knife"      : 20,  // 小刀   value   70
		"/obj/area/obj/dagger"     : 10,  // 匕首   value  500
		"/obj/area/obj/shortsword" : 10,  // 短劍   value  900
		"/obj/area/obj/longsword"  : 5,   // 長劍   value 4000
		"/obj/area/obj/blade"      : 5,   // 單刀   value 3500
		"/obj/area/obj/pike"       : 5,   // 長槍   value 6000
		"/obj/area/obj/rod"        : 5,   // 鐵鞭   value 5200
		__DIR__"obj/hoe"           : 3,
		__DIR__"obj/shovel"        : 5,
	]));

	set("chat_chance", 5);
	set("chat_msg", ({
		"鐵匠將一塊燒紅的鐵塊「嗤」地一聲浸入一旁的水箱中。\n",
		"鐵匠用手中的鐵鎚在鐵砧上用力敲打。\n",
		"鐵匠抹了把汗﹐說道﹕剛拜了師的後生﹐先挑把趁手的兵器再上路罷。\n",
		"鐵匠說道﹕站開點﹐小心別燙著了。\n",
		"鐵匠說道﹕唉 ... 真把我給忙壞了。\n",
	}));
	setup();
	carry_object(__DIR__"obj/smock")->wear();
	carry_money("coin", 200);
}

int accept_fight()
{
	do_chat("鐵匠瞪了瞪眼﹐掂了掂手中的大鐵鎚﹐說道﹕走開﹐我正忙著。\n");
	return 0;
}

void init()
{
	::init();
	add_action("do_vendor_list", "list");
}

int accept_object(object who, object ob)
{
	object thing;
	if ( !ob->id("lo iron") ) return 0;
	call_out((:command("say 喔！要製成箭嗎, 那簡單, 馬上就可以做好.\n"):),1);
	thing=new(__DIR__"obj/arrow");
	thing->move(who);
	call_out((:message_vision("鐵匠把剛做好的箭交給了$N。\n",this_player(),) :),2);
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc

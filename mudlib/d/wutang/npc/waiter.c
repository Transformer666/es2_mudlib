// waiter.c

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

int on_service = 0;

void create()
{
    set_name("店伴", ({"waiter", "wutang_waiter"}));
    set_race("human");
    set_class("commoner");
    set_level(3);

    set("age", 19);
    set("long",
	"一個年輕的店伴﹐忙碌地穿梭在客人之間﹐你可以用 list 看看\n"
	"菜單﹐用 buy 跟他點菜。\n");
    set("chat_chance", 1);
    set("chat_msg", ({
	"店伴吆喝道﹕客倌﹐要來點什麼﹖本店的水煮牛肉可是一絕﹗\n",
	"店伴忙碌地擦拭著桌子。\n",
	"店伴說道﹕客倌慢用﹐有什麼需要儘管吩咐。\n",
    }));
    set("merchandise", ([
	__DIR__"obj/beef" : 30,
	__DIR__"obj/white_wine" : 30,
	__DIR__"obj/beef_dumpling" : 50,
	__DIR__"obj/manto" : 50,
	__DIR__"obj/waterskin" : 50,
    ]));

    setup();
}

void init()
{
    ::init();
    add_action("do_vendor_list", "list");
}

int accept_fight(object ob)
{
    do_chat("店伴連忙擺手道﹕客倌﹐小店是做生意的﹐可不興打架﹗\n");
    return 0;
}

mixed affirm_merchandise(object customer, string item_name)
{
    if( on_service )
	return notify_fail("店伴正忙著招呼其他客人﹐請你等一會兒。\n");
    return ::affirm_merchandise(customer, item_name);
}

private void handover(object customer, mixed item)
{
    on_service = 0;
    if( !customer || environment(customer)!=environment() ) {
	command("say 咦﹖剛剛那位客倌人呢﹖");
	say("店伴把端出來的" + item->name() + "又端了回去。\n");
	return;
    }
    command("say 客倌﹐您的" + item->name() + "來啦﹗");
    message_vision("$N把剛端出來的" + item->name()
	+ "送到$n面前。\n", this_object(), customer);
    ::deliver_merchandise(customer, item);
}

void deliver_merchandise(object customer, mixed item)
{
    command("say " + item->name() + "是吧﹖馬上來﹗");
    on_service = 1;
    do_chat((: handover, customer, item :));
}

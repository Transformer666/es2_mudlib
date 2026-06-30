// d/baolian/npc/keeper.c -- 寶蓮寺藏經閣知客僧：照看經卷流通處(F_VENDOR)。
//
// docs 02-遊戲系統與機制/06-煉丹與書本系統.md L128 寶蓮寺書單：
//   迷羅香 15兩、法華經/大悲咒/往生經/佛名經 各 5兩。
// 經卷皆為共用悟性書 object(/obj/book/*)，跨店共用同物件；迷羅香為共用薰香道具。
// merchandise 的 mapping value 是「庫存數量」(feature/npc/vendor.c)，價格取自各物件 set("value")。
//
// 【runtime】本 NPC 純結緣流通、無自訂指令；init 補 add_action("do_vendor_list","list")(F_VENDOR 標準)。
//   不 replace_program(NPC 本就不該)。物件以英文裸 token id 認(鐵則 #6)：list/buy fahua/dabei…。

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("知客僧", ({ "keeper", "monk", "vendor",
		"知客僧", "知客" }) );
	set("nickname", "知客僧");
	set_race("human");
	set_class("bonze");
	set_level(12);

	set("age", 48);
	set("gender", "male");
	set("long",
		"這位是藏經閣的知客僧﹐一襲灰布僧袍洗得發白﹐面相和善﹐\n"
		"眉宇間透著久經禪修的安詳。他照看著閣角的經卷流通處﹐凡\n"
		"有香客求經問法﹐他總是不厭其煩地一一指點。你可以用 list\n"
		"看他結緣些什麼經卷香品﹐用 buy 向他請一卷回去。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"知客僧雙手合十﹐和聲道﹕阿彌陀佛﹐施主是來請經的麼﹖\n",
		"知客僧捻著念珠道﹕經卷請回去﹐尋個清靜處 study 細細參讀﹐於悟性大有助益。\n",
		"知客僧道﹕本寺刻印的法華、往生諸經皆隨喜結緣﹐施主量力添些香火便是。\n",
		"知客僧拈起一束迷羅香端詳道﹕這迷羅香乃番邦異草所製﹐尋常香客倒少有人問津。\n",
	}));
	// 寶蓮寺書單(docs 06 L128)。價格自各物件 set("value") 讀取；此處數字為庫存。
	set("merchandise", ([
		"/obj/book/milu_incense" : 5,		// 迷羅香 15兩(薰香道具)
		"/obj/book/fahua_sutra" : 10,		// 法華經 5兩
		"/obj/book/dabei_mantra" : 10,		// 大悲咒 5兩(上一批已建，複用)
		"/obj/book/rebirth_sutra" : 10,		// 往生經 5兩(上一批已建，複用)
		"/obj/book/foming_sutra" : 10,		// 佛名經 5兩
	]));

	setup();
	carry_money("coin", 300);
}

void init()
{
	::init();
	add_action("do_vendor_list", "list");
}

int accept_fight(object ob)
{
	do_chat("知客僧合十垂目﹐和聲道﹕出家人四大皆空﹐施主何苦動氣﹖罪過罪過。\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc

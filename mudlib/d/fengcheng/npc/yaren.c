// yaren.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("相馬牙人", ({ "yaren", "horse broker", "broker" }) );
	set_race("human");
	set_class("commoner");
	set_level(4);

	set("age", 52);
	set("gender", "male");
	set("long",
		"一個專做馬市生意的牙人﹐瘦得像根麻桿﹐一雙眼睛卻賊亮\n"
		"賊亮的﹐據說只消繞著一匹馬轉上一圈﹐便能把那馬的年口、\n"
		"腳力、脾性說得分毫不差﹐是風城馬市裡頂有名的人物。\n");
	set("chat_chance", 4);
	set("chat_msg", ({
		"相馬牙人瞇著眼﹐口中嘖嘖有聲﹐像是又相中了哪匹好馬。\n",
		"相馬牙人湊上前來﹐熱絡地問道﹕客官可是要尋匹好腳力的馬﹖這風城馬市的行情﹐沒人比小老兒更門兒清。\n",
		"相馬牙人豎起拇指誇道﹕塞外的良駒﹐日行千里不在話下﹐走鏢闖關東﹐有匹好馬便是半條命哪﹗\n",
		"相馬牙人壓低聲音道﹕買馬的學問大著哩﹐光看牙口就有十來樣門道﹐外鄉人不懂行﹐最容易吃虧上當。\n",
	}));
	setup();
	carry_money("coin", 150);
}

int accept_fight(object ob)
{
	do_chat("相馬牙人連連擺手道﹕有話好說有話好說﹗小老兒一張嘴吃飯﹐手底下可沒這本事﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc

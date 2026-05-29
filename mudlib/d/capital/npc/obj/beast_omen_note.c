// beast_omen_note.c -- 主線任務四「獸亂之兆」的信物：
//                      京畿神社守木老者驗過異獸殘牙、認出那股戾氣源自將
//                      潰的聖木封印後﹐親筆寫就的一紙識獸帖﹐須帶回老松
//                      林交還那位老獵戶﹐告知獸亂的根由。

inherit ITEM;

void create()
{
	set_name("識獸帖", ({ "omen note", "note", "beast omen" }) );
	set_weight(60);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "紙");
		set("value", 1);
		set("long",
			"一紙京畿神社守木老者親筆寫就的識獸帖﹐素箋為底﹐字跡蒼\n"
			"勁而急促﹐顯是寫得倉皇。帖上言明﹕那異獸殘牙所染的青黑\n"
			"戾氣﹐與三百年前皇城聖木封印之力同出一源——封印一日弱似\n"
			"一日﹐那將復出之物的邪念便順著地脈漫入深山﹐蠱得走獸發\n"
			"狂﹐成群朝天靈山的方向湧去。帖末叮囑持帖之人﹕獸亂只是\n"
			"前兆﹐真正的禍根在天靈山那頭悔天鬼身上﹐萬望早作提防。\n");
		set("no_sell", 1);
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc

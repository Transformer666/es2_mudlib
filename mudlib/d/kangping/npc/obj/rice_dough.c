// rice_dough.c -- 康平村非戰鬥支線「康平新米飯糰」的回報信物（蒸好的新米飯糰）：
//                 一隻荷葉包著的新米飯糰。灶上嬸子把田裡老農交與玩家的新米陶缽接過﹐
//                 將新米上籠蒸熟、捏成一個熱乎乎的飯糰﹐拿荷葉包好交還玩家﹐囑其
//                 速速持回康平小店交與店家﹐好教店家拿這新米喜飯張羅村裡的秋收謝場。
//
// 用途：純為支線回報信物（quest/kangping_rice），不堪戰、不能賣、不能偷。
//       由 d/kangping/npc/cook.c 在玩家持新米陶缽來蒸飯後交付（同時銷除空缽）﹐
//       交還 d/kangping/npc/keeper.c 領賞。送件進度記在玩家身上的旗標﹐
//       本物件只作憑證﹐自身不記狀態。

inherit ITEM;

void create()
{
	set_name("新米飯糰", ({ "rice dough", "dough", "xinmifantuan" }) );
	set_weight(450);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "個");
		set("value", 1);
		set("long",
			"一個拿乾荷葉嚴嚴包著的飯糰﹐還溫溫的﹐荷葉的清香裡透\n"
			"著新米蒸熟的暖香。揭開荷葉﹐裡頭是雪白晶瑩、捏得結實的新\n"
			"米飯﹐正是灶上嬸子拿田裡老農新碾的新米上籠蒸熟、捏成的「康\n"
			"平新米飯糰」﹐香軟頂飢﹐是康平村秋收謝場待客的喜飯。\n"
			"該把它持回康平小店交與店家﹕ask keeper about 新米﹐或 give rice dough to keeper。\n");
		set("no_sell", 1);
		set("no_steal", 1);
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc

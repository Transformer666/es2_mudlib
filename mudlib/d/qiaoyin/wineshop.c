// Room: /d/qiaoyin/wineshop.c

inherit ROOM;

void create()
{
	set("short", "聚仙酒樓");
	set("long", @LONG
這是廣場西側的「聚仙酒樓」﹐一座兩層的飛簷木樓﹐是喬陰城裡
數一數二的去處。樓下大堂寬敞明亮﹐十來張紅木方桌座無虛席﹐跑堂
的夥計端著菜盤在桌間穿梭如飛﹔靠牆一道朱漆樓梯通往樓上的雅座﹐
不時傳來划拳行令與絲竹之聲。堂中酒香菜香交織﹐叫人未飲先醉。出
口在東邊﹐通往縣前廣場。
LONG
	);
	set("detail", ([
		"方桌" : "十來張擦得發亮的紅木方桌幾乎座無虛席﹐桌上杯盤交錯﹐坐的多是些南來北往的商旅與本地的鄉紳。\n",
		"樓梯" : "靠牆一道朱漆樓梯通往二樓的雅座﹐樓上臨窗的位子最是搶手﹐須得早早來訂。\n",
		"夥計" : "跑堂的夥計肩搭抹布﹐手托菜盤﹐在桌間穿梭如飛﹐口中還不住地報著菜名。\n",
		"酒旗" : "樓外一面杏黃酒旗上「聚仙」二字迎風招展﹐底下還綴著一行小字﹕「太白遺風」。\n",
	]));
	set("objects", ([
		__DIR__"npc/citizen" : 1,
		__DIR__"npc/laocangtou" : 1,
	]));
	set("outdoors", "qiaoyin");
	set("no_fight", 1);
	set("exits", ([ /* sizeof() == 1 */
		"east" : __DIR__"square",
	]));

	setup();
	replace_program(ROOM);
}

// vim: set ts=4 sw=4 syntax=lpc

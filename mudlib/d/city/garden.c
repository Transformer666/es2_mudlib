// Room: /d/city/garden.c

inherit ROOM;

void create()
{
	set("short", "城中花園");
	set("long", @LONG
一座精心打理的花園，假山流水、亭台樓閣錯落有致。園中遍植
四季花卉，此時正值盛開，奼紫嫣紅，芳香四溢。一條鵝卵石小路蜿
蜒穿過花叢，通向中央的涼亭。幾隻蝴蝶在花間翩翩起舞，好一處
鬧中取靜的所在。
LONG
	);
	set("detail", ([
		"涼亭" : "涼亭飛簷翹角，四面通風，亭中擺著一張石桌和幾個石墩，是品茗賞花的好地方。\n",
		"假山" : "假山堆疊得頗為巧妙，山間還有一道小小的瀑布，水聲潺潺。\n",
	]));
	set("exits", ([
		"southwest" : __DIR__"square",
	]));

	setup();
	replace_program(ROOM);
}

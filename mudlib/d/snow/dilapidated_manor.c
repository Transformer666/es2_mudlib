// Room: /d/snow/dilapidated_manor.c

inherit ROOM;

void create()
{
	set("short", "破舊莊園");
	set("long", @LONG
這裡是一座荒廢已久的莊園﹐斑駁的圍牆上爬滿了枯萎的藤蔓﹐
大門早已歪斜脫落﹐只剩一扇殘破的門板搖搖欲墜。院子裡雜草
叢生﹐一口枯井靜靜地立在角落﹐井沿上積滿了落葉。透過破碎
的窗欞﹐隱約可以看到屋內空蕩蕩的﹐偶爾有幾隻烏鴉從屋頂上
飛過﹐發出淒厲的叫聲。這地方給人一種說不出的陰森感覺。
LONG
	);
	set("detail", ([
		"圍牆" : "圍牆用青磚砌成﹐不少地方已經坍塌﹐露出裡面的泥土。\n",
		"枯井" : "一口乾枯的水井﹐往下望去黑漆漆的﹐看不到底。井沿上刻著一些模糊的字跡﹐已經辨認不出。\n",
		"門板" : "只剩下一扇殘破的門板﹐上面的漆已經全部脫落﹐露出灰白的木頭。\n",
	]));
	set("objects", ([
		__DIR__"npc/darkrobe" : 1,
	]));
	set("exits", ([
		"north" : __DIR__"square_sw",
		"south" : __DIR__"manor_hall",
	]));

	setup();
	replace_program(ROOM);
}

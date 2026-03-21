// Room: /d/lijun/square.c

inherit ROOM;

void create()
{
	set("short", "鯉君渡廣場");
	set("long", @LONG
渡口小鎮的中心是一片不大的廣場﹐地面鋪著青石板﹐被無數行
人的腳步磨得光滑。廣場中央立著一座石碑﹐上面刻著鯉君渡的由來
傳說。幾棵老柳樹環繞四周﹐垂柳拂地﹐為過路的旅人提供一片蔭涼
。往南是繁忙的渡口大街﹐往北可以回到渡口入口﹐往西是一條僻靜的
小巷。
LONG
	);
	set("outdoors", "town");
	set("detail", ([
		"石碑" : "石碑上刻著：「相傳古時有鯉魚精在此處渡河﹐化為人形﹐故名鯉君渡。」\n",
		"柳樹" : "幾棵老柳樹枝繁葉茂﹐垂柳輕拂地面﹐透著一股悠閒的氣息。\n",
	]));
	set("exits", ([
		"north" : __DIR__"entrance",
		"south" : __DIR__"street",
		"west" : __DIR__"back_street",
	]));

	setup();
	replace_program(ROOM);
}

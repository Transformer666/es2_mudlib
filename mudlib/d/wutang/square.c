// Room: /d/wutang/square.c

inherit ROOM;

void create()
{
	set("short", "五堂鎮廣場");
	set("long", @LONG
這裡是五堂鎮的中央廣場﹐一座刻滿文字的古老石碑矗立在廣場正
中央﹐碑前插著一根高高的旗杆﹐旗幟在風中獵獵作響。四周商鋪林立
﹐東邊傳來小販的吆喝聲﹐西邊隱約可見城牆的輪廓﹐往北似乎通往衙
門方向﹐南邊則是進出鎮子的主要通道。廣場上人來人往﹐十分熱鬧。
LONG
	);
	set("objects", ([
		__DIR__"npc/villager" : 2,
	]));
	set("detail", ([
		"石碑" : "石碑上刻著五堂鎮的由來﹕相傳百餘年前﹐五位武林高手於此地結義建鎮﹐分設仁義禮智信五堂﹐教化鎮民﹐故名五堂鎮。碑文雖經風霜侵蝕﹐字跡依然清晰可辨。\n",
		"旗杆" : "一根筆直的木製旗杆﹐頂端懸掛著一面繡有「五堂」二字的杏黃旗﹐在風中飄揚。\n",
	]));
	set("exits", ([
		"east" : __DIR__"square_e",
		"west" : __DIR__"square_w",
		"north" : __DIR__"square_n",
		"south" : __DIR__"square_s",
	]));

	setup();
}

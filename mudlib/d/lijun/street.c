// Room: /d/lijun/street.c

inherit ROOM;

void create()
{
	set("short", "渡口大街");
	set("long", @LONG
這條不長的大街是鯉君渡最熱鬧的地方。街道兩旁零星地開著幾
家店鋪﹐門板上掛著褪色的招牌。地面鋪著青石板﹐被來往的行人踩
得光滑發亮。往南走是碼頭﹐可以隱約聞到河水的腥氣；東邊有個小
市集﹐不時傳來吆喝叫賣聲；西邊是一棟二層的茶樓﹐門口掛著「清
月樓」的招牌。往北可以回到渡口入口。
LONG
	);
	set("outdoors", "town");
	set("exits", ([
		"north" : __DIR__"entrance",
		"south" : __DIR__"dock",
		"east" : __DIR__"market",
		"west" : __DIR__"teahouse",
	]));

	setup();
	replace_program(ROOM);
}

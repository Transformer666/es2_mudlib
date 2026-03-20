// Room: /d/longan/street.c

inherit ROOM;

void create()
{
	set("short", "龍安大街");
	set("long", @LONG
寬闊的青石板街道兩旁商舖林立，酒樓茶肆鱗次櫛比。街上行人
如織，叫賣聲此起彼伏。幾匹高頭大馬載著身著錦袍的商人從街上走
過，馬蹄踏在石板上發出清脆的響聲。空氣中瀰漫著各種食物的香氣，
混雜著遠處傳來的說書人的聲音。
LONG
	);
	set("exits", ([
		"south" : __DIR__"entrance",
		"north" : __DIR__"square",
	]));

	setup();
	replace_program(ROOM);
}

// Room: /d/wutang/square_s.c

inherit ROOM;

void create()
{
	set("short", "廣場南邊");
	set("long", @LONG
這裡是五堂鎮廣場的南邊﹐也是鎮上最繁忙的地段之一﹐從南門進
鎮的旅人和商隊都要經過這裡。往北回到廣場中央﹐南邊的大路直通南
門﹐西邊有一條街道通往碼頭方向。地面上留著深深的車轍痕跡﹐顯然
常有載貨的馬車經過。
LONG
	);
	set("exits", ([
		"north" : __DIR__"square",
		"south" : __DIR__"sgate",
		"west" : __DIR__"street3",
	]));

	setup();
	replace_program(ROOM);
}

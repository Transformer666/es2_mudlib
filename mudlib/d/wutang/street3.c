// Room: /d/wutang/street3.c

inherit ROOM;

void create()
{
	set("short", "南街");
	set("long", @LONG
這裡是五堂鎮的南街﹐空氣中瀰漫著一股魚腥味﹐夾雜著河水潮
濕的氣息。往東回到廣場南邊﹐往西的路通往碼頭方向﹐隱約可以聽到
船工號子的聲音和水浪拍岸的聲響。街道兩旁開著幾家賣乾貨和漁具的
小店﹐門前晾曬著漁網。
LONG
	);
	set("exits", ([
		"east" : __DIR__"square_s",
		"west" : __DIR__"dock",
	]));

	setup();
	replace_program(ROOM);
}

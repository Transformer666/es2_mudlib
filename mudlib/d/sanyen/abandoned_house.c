// Room: /d/sanyen/abandoned_house.c

inherit ROOM;

void create()
{
	set("short", "廢棄民房");
	set("long", @LONG
村西一間早已無人居住的土坯房﹐屋頂塌了一半﹐幾根發黑的房梁
斜斜地架在殘牆上。屋內滿是灰塵與蛛網﹐角落裡散落著一些破碎的
陶罐和朽爛的木頭。透過坍塌的屋頂可以看到天空﹐幾隻麻雀在斷壁
殘垣間築了巢﹐嘰嘰喳喳地叫個不停。
LONG
	);
	set("exits", ([
		"east" : __DIR__"west_street",
	]));

	setup();
	replace_program(ROOM);
}

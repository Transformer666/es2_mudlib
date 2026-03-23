// Room: /d/qianchang/temple.c

#include <room.h>

inherit TEMPLE;

void create()
{
	set("short", "前場土地廟");
	set("long", @LONG
一座小小的土地廟，紅磚砌成的矮牆圍出一方清淨之地。廟門不
大，門楣上掛著一塊寫著「福德正神」的木匾。廟內供奉著一尊土
地公的泥塑像，雖然手藝粗糙，卻被擦拭得很乾淨。香爐裡插著幾
炷燃燒的線香，青煙嫋嫋升起。幾位鎮民正跪在蒲團上虔誠地祈禱，
求個風調雨順、出入平安。
LONG
	);
	set("no_fight", 1);
	set("objects", ([
		__DIR__"npc/temple_keeper" : 1,
	]));
	set("exits", ([
		"north" : __DIR__"square",
	]));

	setup();
	replace_program(TEMPLE);
}

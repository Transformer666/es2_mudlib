// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "石洞");
	set("long", @LONG
藥圃後方的山壁上有一個隱蔽的石洞，洞口被藤蔓遮掩，若非刻意
尋找很難發現。洞內空間不小，地面散落著一些碎骨和焦痕，空氣中
瀰漫著一股濃重的腥臭味。洞壁上留有巨大的爪痕，顯然有什麼可
怕的生物棲息在這裡。
LONG
	);
	set("objects", ([
		__DIR__"npc/red_dragon" : 1,
	]));
	set("exits", ([
		"south" : __DIR__"herb_garden",
	]));

	setup();
	replace_program(ROOM);
}

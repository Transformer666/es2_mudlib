// Room: /d/sanyen/inner_temple.c

#include <room.h>

inherit TEMPLE;

void create()
{
	set("short", "內殿");
	set("long", @LONG
廟宇的內殿﹐比外殿更加莊嚴肅穆。殿中供奉著一尊更大的佛像﹐
佛像用銅鑄成﹐表面鍍了一層金﹐在燭光下熠熠生輝。佛像前擺著蒲團
和木魚﹐一名僧人正閉目打坐﹐嘴中唸唸有詞。殿中瀰漫著一股淡淡
的檀香。
LONG
	);
	set("objects", ([
		__DIR__"npc/temple_monk" : 1,
	]));
	set("no_fight", 1);
	set("exits", ([
		"south" : __DIR__"temple",
	]));

	setup();
	replace_program(TEMPLE);
}

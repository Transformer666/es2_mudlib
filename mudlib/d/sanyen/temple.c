// Room: /d/sanyen/temple.c

#include <room.h>

inherit TEMPLE;

void create()
{
	set("short", "廟宇");
	set("long", @LONG
一座不大的廟宇﹐雖然年代久遠﹐但香火還算旺盛。廟門上方掛著
一塊匾額﹐上書「伏魔寺」三字。大殿中供奉著一尊金身佛像﹐佛像
前的香爐裡青煙裊裊。廟中十分安靜﹐只有木魚聲和低沉的誦經聲迴
盪在殿堂之中。
LONG
	);
	set("no_fight", 1);
	set("exits", ([
		"west" : __DIR__"street",
		"north" : __DIR__"inner_temple",
	]));

	setup();
	replace_program(TEMPLE);
}

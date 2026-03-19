// Room: /d/jingji/inn.c

#include <room.h>

inherit INN;

void create()
{
	set("short", "京畿驛館");
	set("long", @LONG
這是一間靠近京城的官方驛館，裝潢極為考究。大廳裡鋪著厚厚
的織錦地毯，窗上掛著絲綢帷幔，紅木傢俱上了好幾層漆，在燭光下
泛著溫潤的光澤。一座屏風上繡著百鳥朝鳳的圖案，將大廳隔成雅座
和散座。這裡接待的多是進京辦事的各地官員和富商巨賈。
LONG
	);
	set("valid_startroom", 1);
	set("no_fight", 1);
	set("exits", ([
		"south" : __DIR__"entrance",
	]));

	setup();
}

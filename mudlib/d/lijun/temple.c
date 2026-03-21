// Room: /d/lijun/temple.c

#include <room.h>

inherit TEMPLE;

void create()
{
	set("short", "城隍廟");
	set("long", @LONG
這座城隍廟雖然不大﹐卻打理得十分乾淨。廟門上方掛著一塊寫
著「城隍廟」的匾額﹐字跡端正有力。廟內正中供奉著一尊城隍爺的
神像﹐威嚴而慈祥。神案上擺著供品和幾柱清香﹐香煙嫋嫋。渡口的
百姓常來此處燒香祈福﹐保佑出入平安。往北可以回到小巷。
LONG
	);
	set("detail", ([
		"匾額" : "匾額上寫著「城隍廟」三個金色大字﹐兩側有一副對聯。\n",
		"神像" : "城隍爺的神像約莫三尺來高﹐面容威嚴而不失慈祥﹐身披官袍﹐頭戴官帽。\n",
		"香爐" : "一個銅製香爐﹐爐中插著幾柱清香﹐輕煙嫋嫋上升。\n",
	]));
	set("exits", ([
		"north" : __DIR__"back_street",
	]));

	setup();
	replace_program(TEMPLE);
}

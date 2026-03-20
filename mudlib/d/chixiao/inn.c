// Room: /d/chixiao/inn.c

#include <room.h>

inherit INN;

private void create()
{
	set("short", "赤魈村客棧");
	set("long", @LONG
這間簡陋的客棧是赤魈村唯一能夠落腳休息的地方﹐幾張搖搖晃
晃的桌椅散落在狹小的廳堂裡﹐牆上掛著一盞昏暗的油燈﹐搖曳的
燈光在牆壁上投射出忽明忽暗的影子。雖然條件簡陋﹐但總比露宿
荒野要強得多。
LONG
	);
	set("valid_startroom", 1);
	set("no_fight", 1);
	set("detail", ([
		"油燈" : "一盞簡陋的油燈﹐燈芯已經快燃盡了﹐發出微弱的光芒。\n",
		"桌椅" : "幾張粗糙的木桌和凳子﹐表面坑坑窪窪的﹐看起來用了很久了。\n",
	]));
	set("exits", ([
		"north" : __DIR__"village_square",
	]));

	setup();
}

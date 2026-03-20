// Room: /d/chixiao/wishing_pool.c

inherit ROOM;

void create()
{
	set("short", "許願池");
	set("long", @LONG
一座古老的石池出現在你的面前﹐池水清澈見底﹐微微泛著碧綠
色的光芒﹐與這個破敗的村莊格格不入。池邊的石欄上雕刻著奇異
的花紋﹐隱隱散發著一股神秘的力量。池底可以看到一些閃閃發光
的銅錢﹐大概是過往的旅人投下許願的。據傳說﹐將特定的物品投
入池中﹐會召喚出強大的靈體。
LONG
	);
	set("detail", ([
		"石池" : "池子不大﹐直徑約莫一丈﹐但池水深不見底﹐碧綠色的水面偶爾泛起一圈圈漣漪﹐彷彿水底有什麼東西在活動。\n",
		"花紋" : "石欄上雕刻的花紋十分古老﹐看起來像是某種遠古的符文﹐你完全看不懂。\n",
		"銅錢" : "池底散落著不少銅錢﹐在碧綠的池水映照下閃閃發亮。\n",
	]));
	set("objects", ([
		__DIR__"npc/tianling" : 1,
	]));
	set("exits", ([
		"south" : __DIR__"village_square",
	]));

	setup();
	replace_program(ROOM);
}

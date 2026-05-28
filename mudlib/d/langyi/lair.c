// Room: /d/langyi/lair.c

inherit ROOM;

void create()
{
	set("short", "破舊地窖");
	set("long", @LONG
這是僻靜小巷盡頭一座破屋下的地窖﹐四壁濕漉漉的滲著水珠﹐空
氣裡瀰漫著霉味與酒氣。地上胡亂堆著些破甕爛筐﹐看似尋常人家堆雜
物的所在﹐然而牆角一塊鬆動的石板下﹐隱隱透出一線幽光。膽大心細
之人若搬開石板﹐順著石階往下﹐便能潛入瑯夷派的密道。往上可攀回
小巷。
LONG
	);
	set("detail", ([
		"石板" : "牆角這塊青石板看似與地面無異﹐其實底下另有玄機﹐搬開
便是一道通往地底的石階。
",
		"破甕" : "幾口破甕東倒西歪地堆在牆邊﹐甕中空空如也﹐顯是故布疑
陣的障眼之物。
",
	]));
	set("exits", ([
		"up" : "/d/snow/epath",
		"down" : __DIR__"passage",
	]));

	setup();
}
// vim: set ts=4 sw=4 syntax=lpc

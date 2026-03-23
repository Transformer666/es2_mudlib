// Room: /d/chixiao/training_ground.c

inherit ROOM;

void create()
{
	set("short", "村中空地");
	set("long", @LONG
村子裡一塊被踩踏得十分平整的空地﹐地面上隱約可見幾個木樁
的殘跡﹐看起來以前曾是練武用的場地。空地邊上靠著一個破舊的
稻草人﹐身上插滿了箭矢和短刀﹐已經被風吹雨淋得不成樣子。一
旁的石台上擺著幾塊練功用的石鎖﹐表面被磨得光滑發亮。
LONG
	);
	set("detail", ([
		"木樁" : "幾根朽爛的木樁殘留在地面上﹐看得出這裡曾經是村民們練武的地方。\n",
		"稻草人" : "一個用稻草紮成的人形靶子﹐身上千瘡百孔﹐搖搖欲墜。\n",
		"石鎖" : "幾塊大小不一的石鎖﹐最大的一塊少說也有五十斤重。\n",
	]));
	set("exits", ([
		"south" : __DIR__"street",
	]));

	setup();
	replace_program(ROOM);
}

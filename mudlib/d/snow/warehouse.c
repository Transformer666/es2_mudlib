// Room: /d/snow/warehouse.c

inherit ROOM;

void create()
{
	set("short", "倉庫");
	set("long", @LONG
這裡是雪亭鎮的倉庫﹐裡面堆滿了各式各樣的木箱和麻袋﹐空氣
中瀰漫著一股潮溼的霉味。幾個工人正忙碌地搬運著貨物﹐不時傳
來沉重的腳步聲和木箱碰撞的聲響。牆角堆放著幾把掃帚和一些繩
索﹐看起來這裡的管理還算有條不紊。
LONG
	);
	set("detail", ([
		"木箱" : "大大小小的木箱堆疊在一起﹐上面用墨水寫著不同的標記﹐有些箱子上還貼著封條。\n",
		"麻袋" : "幾個鼓鼓囊囊的麻袋靠在牆邊﹐看起來裡面裝的是糧食之類的東西。\n",
	]));
	set("objects", ([
		__DIR__"npc/worker" : 2,
	]));
	set("exits", ([
		"west" : __DIR__"bazar",
	]));

	setup();
	replace_program(ROOM);
}

// Room: /d/wutang/teastall.c

inherit ROOM;

void create()
{
	set("short", "茶攤");
	set("long", @LONG
這是路口邊一個簡陋的茶攤﹐一棵老槐樹底下支起一片葦席遮陽﹐
席下擺著幾張矮桌矮凳。攤上一只半人高的大瓦壺正咕嚕咕嚕冒著熱氣
﹐攤主隨時替過往的行人斟上一碗解渴的粗茶。樹蔭下坐著幾個歇腳閒
談的鎮民﹐天南地北地說著些聽來的奇聞。往北可以回到鎮中的十字路
口。
LONG
	);
	set("detail", ([
		"老槐樹" : "一棵枝葉繁茂的老槐樹﹐濃蔭蔽日﹐替樹下的茶攤擋去了大半的烈日。\n",
		"瓦壺" : "攤上那只大瓦壺裡煮的是最便宜的粗茶﹐茶味雖澀﹐解渴卻是頂好的。\n",
		"矮凳" : "幾張被坐得發亮的矮凳隨意地擺在樹蔭下﹐累了盡管坐下歇歇。\n",
	]));
	set("outdoors", "wutang");
	set("no_fight", 1);
	set("exits", ([ /* sizeof() == 1 */
		"north" : __DIR__"cross",
	]));

	setup();
	replace_program(ROOM);
}

// vim: set ts=4 sw=4 syntax=lpc

// Room: /d/wenguo/square.c

inherit ROOM;

void create()
{
	set("short", "文國縣廣場");
	set("long", @LONG
文國縣城的中心廣場寬敞整潔﹐地面鋪著打磨光滑的大塊青石板
。廣場中央矗立著一座石碑﹐上面鐫刻著文國縣的建置沿革。廣場四
周栽著修剪整齊的冬青﹐東西兩側分別通往東大街和西大街﹐北面是
一家客棧﹐南面則是城隍廟。不時有身穿官服的吏員匆匆走過﹐廣場
旁邊的告示欄上貼著幾張公告。
LONG
	);
	set("outdoors", "city");
	set("objects", ([
		__DIR__"npc/villager" : 2,
	]));
	set("detail", ([
		"石碑" : "石碑上刻著：「文國縣﹐建於前朝永安年間﹐歷經數百年﹐文風鼎盛﹐人才輩出。」\n",
		"告示" : "告示上寫著近期的縣令公告﹐大意是提醒居民注意治安。\n",
		"冬青" : "修剪得整整齊齊的冬青樹叢﹐顯示出縣城管理的井然有序。\n",
	]));
	set("exits", ([
		"north" : __DIR__"inn",
		"south" : __DIR__"temple",
		"east" : __DIR__"street1",
		"west" : __DIR__"street2",
	]));

	setup();
	replace_program(ROOM);
}

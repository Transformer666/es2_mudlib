// Room: /d/qiaoyin/street.c

inherit ROOM;

void create()
{
	set("short", "喬陰大街");
	set("long", @LONG
這是喬陰縣城的大街﹐寬可容四馬並行﹐青石板鋪就的路面被往來
的車馬行人磨得光可鑑人。街道兩旁酒樓、茶肆、綢緞莊、藥鋪鱗次櫛
比﹐高高的幌子與招牌迎風招展﹐沿街叫賣的小販與荷擔的腳夫絡繹不
絕﹐好一派縣城的繁華景象。街東一座門面闊綽的客棧高懸著酒旗﹐街
西一間清雅的書局飄出陣陣墨香。往北通往縣前廣場﹐往南則回到西城
門。
LONG
	);
	set("detail", ([
		"幌子" : "店鋪簷下的幌子五花八門﹐酒旗、藥幌、布招、書幡﹐隨風翻飛﹐看得人眼花撩亂。\n",
		"招牌" : "一塊塊塗金描朱的招牌高掛簷下﹐字號或大或小﹐多是城裡有些年頭的老字號。\n",
		"客棧" : "街東那座客棧門面闊綽﹐簷下一面酒旗上「悅來」二字格外醒目﹐進出的多是過往的商旅。\n",
		"書局" : "街西一間書局門面清雅﹐匾上「喬陰書局」四字寫得清逸脫俗﹐門裡隱隱飄出墨香書氣。\n",
		"小販" : "沿街的小販挑著擔子、推著小車﹐賣的是些針線雜貨、時鮮果子﹐吆喝聲此起彼落。\n",
	]));
	set("objects", ([
		__DIR__"npc/citizen" : 1,
		__DIR__"npc/mailman" : 1,
	]));
	set("outdoors", "qiaoyin");
	set("exits", ([ /* sizeof() == 4 */
		"south" : __DIR__"gate",
		"north" : __DIR__"square",
		"east" : __DIR__"inn",
		"west" : __DIR__"bookshop",
	]));

	setup();
	replace_program(ROOM);
}

// vim: set ts=4 sw=4 syntax=lpc

// Room: /d/lijun/riverside_w.c

inherit ROOM;

void create()
{
	set("short", "河畔西段");
	set("long", @LONG
沿著河岸往西的一條小路﹐路旁種著幾棵垂柳﹐柳條隨風搖曳﹐
拂過水面。河邊散落著幾塊大石頭﹐是歇腳的好地方。遠處可以看到
清月樓的飛簷翹角從柳樹後面探出頭來。這裡比東邊清靜得多﹐偶爾
有釣魚的老翁在此垂釣。往北走可以到清月樓﹐往東回到碼頭。
LONG
	);
	set("outdoors", "water");
	set("exits", ([
		"east" : __DIR__"dock",
		"north" : __DIR__"teahouse",
	]));

	setup();
	replace_program(ROOM);
}

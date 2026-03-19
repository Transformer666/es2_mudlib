// Room: /d/lee/ancestral_hall.c

inherit ROOM;

void create()
{
	set("short", "李家祠堂");
	set("long", @LONG
李家村的祠堂﹐是村裡最大最氣派的建築。門楣上掛著一塊金字匾
額﹐上書「李氏宗祠」四字。祠堂中供奉著歷代先祖的牌位﹐牆上掛
著幾幅先人的畫像﹐最上方的一幅畫的是一位身穿儒袍、手持書卷的老
者﹐據說是李家的開村始祖。
LONG
	);
	set("no_fight", 1);
	set("exits", ([
		"west" : __DIR__"street",
	]));

	setup();
	replace_program(ROOM);
}

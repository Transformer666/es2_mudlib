// Room: /d/choyin/bookshop.c

inherit ROOM;

void create()
{
	set("short", "名山書肆");
	set("long", @LONG
一間不大的書店﹐門楣上掛著一塊木匾﹐寫著「名山書肆」四個蒼
勁有力的大字。店裡靠牆擺著幾排書架﹐上面整齊地碼放著各種書冊。
一張紅木書桌後面坐著掌櫃﹐正捧著一卷書讀得入神。空氣中瀰漫著
墨香和紙張特有的味道﹐令人心曠神怡。
LONG
	);
	set("objects", ([
		__DIR__"npc/bookshop_owner" : 1,
	]));
	set("no_fight", 1);
	set("exits", ([
		"west" : __DIR__"nstreet",
	]));

	setup();
	replace_program(ROOM);
}

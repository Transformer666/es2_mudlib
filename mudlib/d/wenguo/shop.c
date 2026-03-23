// Room: /d/wenguo/shop.c

inherit ROOM;

void create()
{
	set("short", "書鋪");
	set("long", @LONG
這是一間古色古香的書鋪﹐空氣中瀰漫著淡淡的墨香和紙張的氣
味。靠牆的書架上整齊地擺放著各種書籍典冊﹐從四書五經到詩詞歌
賦應有盡有。櫃臺上擺著筆墨紙硯等文房四寶﹐供客人挑選。書鋪的
掌櫃是個飽讀詩書的老者﹐常有學子慕名前來請教學問。
LONG
	);
	set("objects", ([
		__DIR__"npc/shopkeeper" : 1,
	]));
	set("detail", ([
		"書架" : "書架上分門別類地擺放著各種書籍﹐有經史子集﹐也有科舉時文。\n",
		"文房四寶" : "櫃臺上擺著湖筆、徽墨、宣紙、端硯﹐都是上等貨色。\n",
	]));
	set("exits", ([
		"south" : __DIR__"street1",
	]));

	setup();
	replace_program(ROOM);
}

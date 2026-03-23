// Room: /d/qianchang/teahouse.c

inherit ROOM;

void create()
{
	set("short", "聚仙茶樓");
	set("long", @LONG
一座兩層的小茶樓，門口掛著「聚仙茶樓」的招牌，雖然名字取得
大氣，其實不過是間鄉鎮茶館。樓下大堂裡擺著十來張方桌，桌上
放著茶壺和瓜子碟。角落裡一個老頭正半瞇著眼睛說書，幾個茶客
聽得入了神。空氣中瀰漫著茶香和炒瓜子的味道，夾雜著人們的
談笑聲，倒是十分熱鬧。
LONG
	);
	set("objects", ([
		__DIR__"npc/tea_master" : 1,
	]));
	set("detail", ([
		"招牌" : "一塊漆成紅色的木頭招牌，上面寫著「聚仙茶樓」四個金字，漆色已經斑駁了。\n",
		"說書人" : "一個鬍子花白的老頭，正拍著醒木講著江湖上的奇聞異事。\n",
	]));
	set("exits", ([
		"south" : __DIR__"street2",
	]));

	setup();
	replace_program(ROOM);
}

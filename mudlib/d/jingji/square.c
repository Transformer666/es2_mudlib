// Room: /d/jingji/square.c

inherit ROOM;

void create()
{
	set("short", "京畿廣場");
	set("long", @LONG
京畿城中心的廣場氣勢非凡，地面鋪著漢白玉石板，在陽光下閃耀
著柔和的光澤。廣場中央立著一座高大的石碑，上面刻著歷代皇帝的聖
訓。北面是一間裝潢考究的驛館，東面則是威嚴的衙門。幾名衙役在廣
場上巡邏，神情肅穆，讓人不敢大聲喧嘩。
LONG
	);
	set("exits", ([
		"south" : __DIR__"street",
		"north" : __DIR__"inn",
		"east"  : __DIR__"yamen",
	]));

	set("objects", ([
		__DIR__"npc/guard" : 1,
	]));

	setup();
	replace_program(ROOM);
}

// Room: /d/chixiao/south_path.c

inherit ROOM;

void create()
{
	set("short", "村南小路");
	set("long", @LONG
一條雜草叢生的小路從村口往南延伸﹐路旁散落著一些碎石和枯
枝。空氣中瀰漫著一股潮溼的泥土味﹐遠處可以隱約看到一片荒蕪
的田地。路邊長著幾叢暗紅色的灌木﹐在微風中輕輕搖曳﹐發出沙
沙的聲響。偶爾有幾隻烏鴉從頭頂飛過﹐發出嘶啞的叫聲。
LONG
	);
	set("outdoors", "wild");
	set("exits", ([
		"north" : __DIR__"entrance",
	]));

	setup();
	replace_program(ROOM);
}

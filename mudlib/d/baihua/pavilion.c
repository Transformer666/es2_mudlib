// Room: /d/baihua/pavilion.c

inherit ROOM;

void create()
{
	set("short", "花亭");
	set("long", @LONG
一座六角涼亭掩映在繁花叢中﹐亭柱上雕刻著精緻的花卉紋樣。
亭內設有石凳石桌﹐供路人歇腳品茗。微風拂過﹐送來陣陣花香﹐
令人心曠神怡﹐塵世煩憂彷彿都隨風而去。
LONG
	);
	set("no_fight", 1);
	set("outdoors", "village");
	set("exits", ([
		"west" : __DIR__"bridge",
		"north" : __DIR__"east_path",
	]));

	setup();
	replace_program(ROOM);
}

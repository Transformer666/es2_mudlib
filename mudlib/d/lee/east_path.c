// Room: /d/lee/east_path.c

inherit ROOM;

void create()
{
	set("short", "村東小路");
	set("long", @LONG
村子東邊一條蜿蜒的泥土小路﹐路兩旁栽著幾棵桑樹﹐枝葉繁茂﹐
遮出一片涼蔭。遠處是一望無際的田野﹐金色的麥浪隨風翻滾。路邊
的草叢中不時傳來蟲鳴﹐幾隻蝴蝶在花間翩翩起舞﹐好一派悠然的鄉
間景致。
LONG
	);
	set("outdoors", "village");
	set("exits", ([
		"west" : __DIR__"pond",
		"north" : __DIR__"ancestral_hall",
	]));

	setup();
	replace_program(ROOM);
}

// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "忘川河");
	set("long", @LONG
一條漆黑如墨的河流在此緩緩流淌，河水中不時浮現出模糊的人臉，發出無聲的嘶喊。河面上漂浮著一層薄薄的磷光，散發著幽藍色的光芒。河邊的泥土冰涼入骨，踩上去會沉入半個腳掌。據說這條河流連接著生死兩界。
LONG
	);
	set("exits", ([
		"west" : __DIR__"dark_path",
	]));

	setup();
	replace_program(ROOM);
}

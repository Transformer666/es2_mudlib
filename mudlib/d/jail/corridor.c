// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "監獄走廊");
	set("long", @LONG
陰暗潮濕的石頭走廊向前延伸，兩旁是一間間用鐵欄杆隔開的牢房。走廊的地面上積著一層汙水，牆壁上掛著幾盞昏暗的油燈，搖曳的火光在牆上投下詭異的影子。空氣中瀰漫著一股令人作嘔的腐臭味。
LONG
	);
	set("exits", ([
		"south" : __DIR__"entrance",
		"east" : __DIR__"cell1",
		"west" : __DIR__"cell2",
		"north" : __DIR__"guard_room",
	]));

	setup();
	replace_program(ROOM);
}

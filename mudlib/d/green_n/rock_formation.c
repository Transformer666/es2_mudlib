// Room: /d/green_n/rock_formation.c

inherit ROOM;

void create()
{
	set("short", "亂石堆");
	set("long", @LONG
幾塊巨大的岩石突兀地矗立在草原上，像是遠古巨人隨手丟下的
玩具。岩石表面長滿了苔蘚和地衣，縫隙間還長出了幾棵頑強的矮
樹。石堆間形成了一些天然的洞穴，似乎有野獸在此棲息。
LONG
	);
	set("outdoors", "wilderness");
	set("objects", ([
		__DIR__"npc/wild_boar" : 1,
	]));
	set("detail", ([
		"洞穴" : "黑漆漆的洞口散發著一股腥臭味，裡面似乎住著什麼野獸。\n",
		"岩石" : "這些岩石質地堅硬，表面被風化得十分粗糙。\n",
	]));
	set("exits", ([
		"south" : __DIR__"windswept",
		"north" : __DIR__"cliff",
	]));

	setup();
	replace_program(ROOM);
}

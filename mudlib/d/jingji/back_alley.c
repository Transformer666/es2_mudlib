// Room: /d/jingji/back_alley.c

inherit ROOM;

void create()
{
	set("short", "後巷");
	set("long", @LONG
京畿繁華大道的背後，是一條幽暗狹窄的後巷。牆壁上爬滿了青
苔，地面有些濕滑。偶爾有幾隻野貓在屋頂間跳躍，巷子的盡頭隱約
傳來叮叮噹噹的打鐵聲。
LONG
	);
	set("objects", ([
		__DIR__"npc/passerby" : 1,
	]));
	set("exits", ([
		"north" : __DIR__"market",
		"west" : __DIR__"west_street",
	]));

	setup();
	replace_program(ROOM);
}

// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "冥想石室");
	set("long", @LONG
這是一間天然形成的石室，被巧妙地改造成了冥想修練的場所。室內光線柔和，中央放著一個蒲團，四壁上刻著各種內功心法的圖解。空氣中飄著淡淡的檀香，讓人心曠神怡。
LONG
	);
	set("no_fight", 1);
	set("exits", ([
		"west" : __DIR__"training_ground",
	]));

	setup();
	replace_program(ROOM);
}

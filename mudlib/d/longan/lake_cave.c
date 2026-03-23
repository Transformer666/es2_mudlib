// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "湖底洞穴");
	set("long", @LONG
從花園旁的小徑深入，穿過一片蘆葦叢，來到了一個隱匿在地下的
洞穴。洞穴中積滿了幽暗的湖水，水面泛著詭異的磷光。洞壁濕滑，
到處是巨大的鱗片和深深的爪痕。一股令人窒息的龍息瀰漫在潮濕的
空氣中，偶爾傳來低沉的龍吟，令人膽寒。
LONG
	);
	set("detail", ([
		"鱗片" : "巨大的漆黑鱗片散落在地，每一片都有巴掌大小，堅硬如鐵。\n",
		"爪痕" : "深深的爪痕遍佈洞壁，不知是何等兇猛的生物留下的。\n",
	]));
	set("no_clean_up", 1);
	set("exits", ([
		"south" : __DIR__"garden",
	]));

	setup();
	replace_program(ROOM);
}

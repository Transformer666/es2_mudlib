// Room: /d/jingji/sgate.c

inherit ROOM;

void create()
{
	set("short", "京畿南城門");
	set("long", @LONG
京畿南面的城門氣勢磅礴﹐高大的門樓上飛檐翹角﹐琉璃瓦在陽
光下閃閃發光。城門洞寬敞到可以讓三輛馬車並行﹐兩扇鑲銅大門足
有四五丈高﹐門上密密麻麻的銅釘排列整齊。數名身著官兵甲冑的守
衛在城門前巡邏﹐盤查著過往的行人和商旅。這裡是京畿重地的南大
門﹐連接著通往外界的官道。
LONG
	);
	set("outdoors", "city");
	set("objects", ([
		__DIR__"npc/gate_guard" : 2,
	]));
	set("exits", ([
		"south" : "/d/road/road4",
		"north" : __DIR__"entrance",
	]));

	setup();
	replace_program(ROOM);
}

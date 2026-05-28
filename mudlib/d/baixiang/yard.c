// Room: /d/baixiang/yard.c

inherit ROOM;

void create()
{
	set("short", "白象寺庭院");
	set("long", @LONG
這是白象寺的庭院﹐青磚墁地﹐當中一座丈餘高的青銅寶鼎終年香
火不斷﹐裊裊檀煙直上雲霄。庭院四周植著數株菩提古樹﹐樹下幾名灰
衣僧人捧著經卷往來其間﹐神情肅穆安詳。往北是供奉佛祖的大雄寶殿
﹐往東是僧人坐禪參修的禪房﹐往西是羅漢演武的演武場﹐往南則是寺
中的山門。
LONG
	);
	set("detail", ([
		"寶鼎" : "青銅寶鼎通體鏽綠﹐鼎腹鑄著纏枝蓮紋與梵文真言﹐爐中香灰
積得厚厚一層。
",
		"菩提" : "庭院中的菩提古樹枝繁葉茂﹐相傳佛祖於菩提樹下證道﹐寺中僧
人常在樹下參禪。
",
	]));
	set("outdoors", "snow");
	set("exits", ([
		"north" : __DIR__"hall",
		"east" : __DIR__"zen",
		"west" : __DIR__"arena",
		"south" : __DIR__"gate",
	]));

	setup();
}
// vim: set ts=4 sw=4 syntax=lpc

// Room: /d/tianshi/yard.c

inherit ROOM;

void create()
{
	set("short", "天師派庭院");
	set("long", @LONG
這是天師派的庭院﹐青磚墁地﹐當中一座三足銅鼎終年香火不斷﹐
裊裊青煙直上雲霄。庭院四周植著數株古柏﹐枝頭懸著一串串祈福的朱
紅符籙﹐隨風輕擺。幾名身著朱衣的弟子捧著經卷往來其間﹐神情肅穆
。往北是供奉三清的大殿﹐往東是弟子煉丹的丹房﹐往西是演法場﹐往
東北一條鋪著青石的小徑通向清冷的素心軒﹐隱隱透出寒氣﹐往東南一
條小徑通向臨風的玄風閣﹐隱隱透出罡氣﹐往西南一條小徑通向森然的紫
雷閣﹐隱隱透出雷氣﹐往南則是派中的山門。
LONG
	);
	set("detail", ([
		"銅鼎" : "三足銅鼎通體鏽綠﹐鼎腹鑄著雲雷紋飾﹐爐中香灰積得厚厚一
層。
",
		"符籙" : "古柏枝頭懸著的朱紅符籙以硃砂寫就﹐筆走龍蛇﹐隱隱透著一股
火氣。
",
	]));
	set("outdoors", "snow");
	set("exits", ([
		"north" : __DIR__"hall",
		"east" : __DIR__"danfang",
		"west" : __DIR__"arena",
		"northeast" : __DIR__"icehall",
		"southeast" : __DIR__"windhall",
		"southwest" : __DIR__"thunderhall",
		"south" : __DIR__"gate",
	]));

	setup();
}
// vim: set ts=4 sw=4 syntax=lpc

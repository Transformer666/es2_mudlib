// Room: /d/manglin/entrance.c

inherit ROOM;

void create()
{
	set("short", "莽林入口");
	set("long", @LONG
五堂鎮北門外﹐一條泥濘的小路通往一片茂密的叢林。林中樹木高
聳﹐枝葉交錯遮天蔽日﹐林中陰暗潮濕﹐不時傳來野獸的吼叫聲。一
塊木牌歪斜地插在路邊﹐上面寫著「莽林﹐非必要勿入」幾個字﹐字跡
已有些模糊了。
LONG
	);
	set("outdoors", "forest");
	set("exits", ([
		"south" : "/d/wutang/ngate",
		"north" : __DIR__"path1",
	]));

	setup();
	replace_program(ROOM);
}

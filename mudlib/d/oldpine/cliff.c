// Room: /d/oldpine/cliff.c

inherit ROOM;

void create()
{
	set("short", "斷崖");
	set("long", @LONG
一面陡峭的斷崖橫亙在眼前﹐崖下是一條湍急的溪流﹐發出嘩嘩
的水聲。崖邊生長著幾棵歪斜的松樹﹐根部死死地扒住岩石﹐在山風
中搖搖欲墜。從這裡可以遠眺四周的山林﹐景色壯麗﹐但腳下卻是萬
丈深淵﹐令人不寒而慄。崖邊的松枝上留有一些七彩的羽毛﹐似乎曾
有珍禽在此棲息。
LONG
	);
	set("outdoors", "mountain");
	set("detail", ([
		"羽毛" : "七彩的羽毛在陽光下閃閃發光﹐據說有一種叫鸂鷘的上古風鳥﹐偶爾會在此出沒。也許準備一些食物能引牠現身。\n",
		"松樹" : "幾棵歪斜的古松﹐根部死死扒住岩石﹐在山風中搖搖欲墜。\n",
	]));
	set("objects", ([
		__DIR__"npc/charming_bird" : 1,
	]));
	set("exits", ([
		"southwest" : __DIR__"road3",
	]));

	setup();
}

// Room: /d/oldpine/cliff.c

inherit ROOM;

void create()
{
	set("short", "斷崖");
	set("long", @LONG
一面陡峭的斷崖橫亙在眼前﹐崖下是一條湍急的溪流﹐發出嘩嘩
的水聲。崖邊生長著幾棵歪斜的松樹﹐根部死死地扒住岩石﹐在山風
中搖搖欲墜。從這裡可以遠眺四周的山林﹐景色壯麗﹐但腳下卻是萬
丈深淵﹐令人不寒而慄。一隻色彩斑斕的風鳥正棲息在崖邊的松枝上。
LONG
	);
	set("outdoors", "mountain");
	set("objects", ([
		__DIR__"npc/charming_bird" : 1,
	]));
	set("detail", ([
		"風鳥" : "那隻風鳥通體七彩﹐羽毛在陽光下閃閃發光﹐據說這種鳥叫鸂鷘﹐是上古風鳥的後裔。也許可以試著給牠餵食。\n",
		"松樹" : "幾棵歪斜的古松﹐根部死死扒住岩石﹐在山風中搖搖欲墜。\n",
	]));
	set("exits", ([
		"southwest" : __DIR__"road3",
	]));

	setup();
}

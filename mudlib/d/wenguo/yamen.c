// Room: /d/wenguo/yamen.c

inherit ROOM;

void create()
{
	set("short", "文國縣衙");
	set("long", @LONG
文國縣衙氣勢恢宏﹐大門上方高懸一塊「文國縣衙」的匾額﹐門
前立著一面鳴冤鼓。走進大堂﹐正中高掛著「明鏡高懸」四個金色大
字﹐下方是縣令升堂問案的公案﹐案上擺著驚堂木和文房四寶。大堂
兩側整齊地立著水火棍﹐肅穆威嚴。縣令正在堂中批閱公文﹐神情專
注。往北可以回到私塾。
LONG
	);
	set("no_fight", 1);
	set("objects", ([
		__DIR__"npc/official" : 1,
	]));
	set("detail", ([
		"匾額" : "匾額上的「文國縣衙」四個字蒼勁有力﹐據說是前任知府親筆所題。\n",
		"明鏡高懸" : "「明鏡高懸」四字以金漆書寫﹐提醒執法者要公正無私。\n",
		"鳴冤鼓" : "門前的鳴冤鼓是百姓告狀時敲擊用的﹐鼓面上的牛皮已經有些磨損了。\n",
	]));
	set("exits", ([
		"north" : __DIR__"study",
	]));

	setup();
	replace_program(ROOM);
}

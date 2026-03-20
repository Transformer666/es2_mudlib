// Room: /d/green_n/cliff.c

inherit ROOM;

void create()
{
	set("short", "懸崖邊");
	set("long", @LONG
草原在這裡戛然而止，一道陡峭的懸崖攔住了去路。懸崖下方是一
片幽深的峽谷，谷底傳來隱約的水聲。崖邊長著幾棵被風吹得歪歪斜
斜的松樹，枝幹向南方伸展，彷彿在逃避北方的寒風。從這裡可以遠
眺整片北草原的壯麗景色。
LONG
	);
	set("outdoors", "wilderness");
	set("detail", ([
		"懸崖" : "懸崖深不見底，崖壁上偶爾有幾叢野花從石縫中探出頭來。\n",
		"峽谷" : "峽谷中雲霧繚繞，谷底似乎有一條河流穿過。\n",
	]));
	set("exits", ([
		"south" : __DIR__"rock_formation",
	]));

	setup();
	replace_program(ROOM);
}

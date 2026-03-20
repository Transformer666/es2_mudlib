// Room: /d/snow/military_camp.c

inherit ROOM;

void create()
{
	set("short", "鎮部軍營");
	set("long", @LONG
這裡是雪亭鎮的鎮部軍營﹐營地四周用粗木樁圍起了一道柵欄﹐
幾頂灰色的帳篷整齊地排列在空地上。營地中央插著一面旗幟﹐在
風中獵獵作響。幾名士兵正在空地上操練﹐遠處傳來兵器碰撞的聲
音。南邊可以回到鄉校。
LONG
	);
	set("detail", ([
		"帳篷" : "灰色的軍用帳篷﹐看起來頗為結實﹐帳篷前掛著幾件曬乾的軍服。\n",
		"旗幟" : "一面寫著大大的「兵」字的旗幟﹐在寒風中飄揚。\n",
		"柵欄" : "用粗大的圓木樁釘成的柵欄﹐雖然簡陋但足以阻擋野獸。\n",
	]));
	set("objects", ([
		__DIR__"npc/recruiter" : 1,
	]));
	set("exits", ([
		"south" : __DIR__"court",
	]));

	setup();
	replace_program(ROOM);
}

// Room: /d/wutang/sgate.c

inherit ROOM;

void create()
{
	set("short", "五堂鎮南門");
	set("long", @LONG
這裡是五堂鎮的南門﹐也是鎮上最大最氣派的城門。高大的門樓上
懸掛著一塊黑底金字的匾額﹐上書「五堂鎮」三個大字。城門兩側各有
一名全副武裝的守衛把守﹐盤查著來往的旅人。門外是通往喬陰縣城的
官道﹐南來北往的商旅大多由此門進出。往北便回到鎮內廣場方向﹐
出城門往西南可通往喬陰縣城。
LONG
	);
	set("objects", ([
		__DIR__"npc/guard" : 2,
	]));
	set("exits", ([
		"north" : __DIR__"square_s",
		"southwest" : "/d/choyin/choyin_road",
	]));

	setup();
	replace_program(ROOM);
}

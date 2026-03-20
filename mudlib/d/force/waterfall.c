// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "瀑布修練處");
	set("long", @LONG
從懸崖上垂下一道白練般的瀑布，水勢洶湧，轟鳴聲震耳欲聾。瀑布下方有一個天然的水潭，水花四濺。潭邊的岩石上擺著幾個蒲團，這裡是修練者以瀑布沖身、鍛鍊內力的絕佳場所。
LONG
	);
	set("exits", ([
		"up" : __DIR__"cliff_edge",
	]));

	setup();
	replace_program(ROOM);
}

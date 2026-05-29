// vim: syntax=lpc

inherit ROOM;

private void
create()
{
  set("short", "木橋");
  set("long", @LONG
你現在來到一條橫過山溪的橋上﹐山溪雖不甚寬﹐但是深度卻有三
、四丈﹐因此這條橋對雪亭鎮對外的交通格外重要﹐橋下的溪水正發出
轟隆轟隆的巨響流過溪谷﹐往西是雪亭鎮﹐往東則通往著名的雪吟山莊
﹐莊主魚鐵山近年勢力日張﹐隱隱有問鼎武林盟主之心。
LONG
  );
  set("no_clean_up", 0);
  set("objects", ([ /* sizeof() == 1 */
	__DIR__"npc/guard" : 2,
  ]));
  set("outdoors", "snow");
  set("exits", ([ /* sizeof() == 2 */
	"west" : __DIR__"npath3",
	"east" : "/d/snowmanor/gate",
  ]));

  setup();
  replace_program(ROOM);
}

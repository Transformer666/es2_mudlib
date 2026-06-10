// vim: syntax=lpc

inherit ROOM;

private void
create()
{
  set("short", "河邊");
  set("long", @LONG
破舊大宅外，你眼前是兩條河流的匯流處，來自西北、東北的兩條
小河匯流後，緩緩的向西南流去。西北邊的河上原有一座小橋，橋身早
已朽斷，只剩幾根橋樁兀自立在水裡；東北沿河本有一條通往李家村的
小石子路，年前教山洪沖毀了，如今要去李家村，得回鎮裡出南門，從
郊野的田間小路走。
LONG
  );
  set("detail", ([ /* sizeof() == 2 */
	"小橋" : "一座巨檜木切削搭成的木橋，年深日久，橋身早已朽斷塌進河裡，\n只剩幾根烏黑的橋樁立在水中，看來是過不去了。\n",
	"小石子路" : "東北沿河原有一條小石子路通往李家村，年前一場山洪把路基沖\n得七零八落，碎石沒入泥淖，早已不能行走。\n",
  ]));
  set("outdoors", "snow");
  set("exits", ([ /* sizeof() == 1 */
	"west" : __DIR__"ruin1",
//	"northeast" : "/d/lee/r1",
  ]));

  setup();
  replace_program(ROOM);
}

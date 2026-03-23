// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "無底深淵");
	set("long", @LONG
在冥王座的東側，大地突然裂開一道巨大的深淵，深淵中漆黑一片，看不到底部。從深淵中不斷湧出冰冷的氣流，伴隨著似有若無的低語聲。深淵的邊緣搖搖欲墜，靠近時可以感受到一股強大的吸引力在拉扯著你的身體。
LONG
	);
	set("detail", ([
		"深淵" : "深淵中傳來一陣陣低沉的吼聲，似乎有某種遠古的巨獸被封印在其中，正試圖掙脫束縛。混沌之氣從裂縫中不斷湧出，令人不寒而慄。\n",
	]));
	set("exits", ([
		"west" : __DIR__"throne",
	]));

	setup();
	replace_program(ROOM);
}

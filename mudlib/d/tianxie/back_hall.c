inherit ROOM;

void create()
{
	set("short", "天邪後殿");
	set("long", @LONG
穿過幔帳後的暗門﹐來到天邪派的後殿。這裡比前殿更加陰暗﹐
四壁掛著黑色的布幔﹐空氣中瀰漫著一股濃重的血腥味。殿中央
擺著一張巨大的黑檀木椅﹐椅前的地面上刻著一個複雜的邪陣﹐
隱隱散發著暗紅色的光芒。這裡是大魔頭李東靈的居所﹐尋常人
等莫敢靠近。
LONG
	);
	set("detail", ([
		"邪陣" : "地面上的邪陣由鮮血繪製﹐紋路複雜詭異﹐隱隱透著一股令人窒息的邪氣。\n",
		"黑檀木椅" : "一張巨大的黑檀木椅﹐椅背上雕刻著一隻張牙舞爪的惡龍﹐做工極為精細。\n",
	]));
	set("objects", ([
		__DIR__"npc/lidongling" : 1,
	]));
	set("exits", ([
		"south" : __DIR__"hall",
	]));

	setup();
	replace_program(ROOM);
}

// Room: /d/lijun/riverbank.c

inherit ROOM;

void create()
{
	set("short", "河灘");
	set("long", @LONG
碼頭南邊是一片開闊的河灘﹐細沙和鵝卵石鋪滿了地面。河水在
此處放緩了腳步﹐形成一個淺淺的灣﹐水面平靜如鏡。幾條小漁船擱
淺在灘上﹐船底朝天曬著太陽。一個老翁蹲坐在河邊﹐手持釣竿﹐靜
靜地垂釣。這裡遠離喧囂﹐只聽得到流水聲和偶爾傳來的鳥叫。往北
走回到碼頭。
LONG
	);
	set("outdoors", "water");
	set("detail", ([
		"漁船" : "幾條小漁船﹐船身斑駁﹐看得出已經用了很多年﹐船艙裡還殘留著魚鱗和漁網。\n",
		"河水" : "河灘邊的河水清淺見底﹐可以看到水底的鵝卵石和游動的小魚。\n",
	]));
	set("objects", ([
		__DIR__"npc/fisherman" : 1,
	]));
	set("exits", ([
		"north" : __DIR__"dock",
	]));

	setup();
	replace_program(ROOM);
}

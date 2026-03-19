// Room: /d/sanyen/pillar.c

inherit ROOM;

void create()
{
	set("short", "石柱");
	set("long", @LONG
村口外面的空地上立著一根粗壯的石柱﹐約有丈許高。石柱表面坑
坑窪窪的﹐上面佈滿了拳頭和掌印留下的痕跡。據村民說﹐這根石柱是
從前住在這裡的一位武僧用來練功的﹐後來武僧走了﹐石柱就留了下來
﹐偶爾有路過的習武之人會在此試試拳腳。
LONG
	);
	set("outdoors", "village");
	set("exits", ([
		"south" : __DIR__"entrance",
	]));

	setup();
	replace_program(ROOM);
}

// Room: /d/wenguo/temple.c

#include <room.h>

inherit TEMPLE;

void create()
{
	set("short", "文國城隍廟");
	set("long", @LONG
文國縣的城隍廟規模不小﹐紅牆黃瓦﹐飛簷翹角﹐廟門前有一對
石獅子鎮守。廟內正殿供奉著城隍爺的金身塑像﹐面容威嚴﹐兩旁站
著牛頭馬面的判官像。大殿中央擺著一個碩大的銅香爐﹐香煙繚繞﹐
不時有信眾前來焚香祈福。廟裡的廟祝正在清掃殿堂。往北可以回到
廣場。
LONG
	);
	set("no_fight", 1);
	set("objects", ([
		__DIR__"npc/temple_keeper" : 1,
	]));
	set("detail", ([
		"神像" : "城隍爺的金身塑像高約八尺﹐頭戴冕冠﹐身披龍袍﹐面容威嚴而正氣凜然。\n",
		"香爐" : "銅香爐中插滿了線香﹐煙霧繚繞﹐空氣中瀰漫著檀香的氣味。\n",
		"石獅" : "一對石獅子蹲踞在廟門兩側﹐雕工精細﹐栩栩如生。\n",
	]));
	set("exits", ([
		"north" : __DIR__"square",
	]));

	setup();
	replace_program(TEMPLE);
}

// Room: /d/lijun/teahouse.c

#include <room.h>

inherit INN;

void create()
{
	set("short", "清月樓");
	set("long", @LONG
清月樓是鯉君渡唯一的茶樓兼客棧﹐門面不大﹐卻收拾得頗為雅
緻。一樓大廳擺著七八張方桌﹐桌上擺著青瓷茶壺和茶杯。靠牆的架
子上擺滿了各色茶葉和點心﹐一位茶娘正在忙碌地招呼客人。空氣中
瀰漫著淡淡的茶香和桂花糕的甜香。靠北有一道木製樓梯通往二樓﹐
東邊的大門開向渡口大街﹐南邊有扇小門通往河畔。
LONG
	);
	set("valid_startroom", 1);
	set("no_fight", 1);
	set("objects", ([
		__DIR__"npc/tea_lady" : 1,
	]));
	set("detail", ([
		"茶壺" : "青瓷茶壺﹐壺身上繪著淡淡的山水圖案﹐壺嘴冒著嫋嫋的熱氣。\n",
		"樓梯" : "一道窄窄的木製樓梯通往二樓﹐扶手磨得光滑﹐樓梯口掛著一盞寫著「雅座」的燈籠。\n",
		"架子" : "架子上擺放著一排排茶葉罐﹐有龍井、碧螺春、鐵觀音等各色好茶。\n",
	]));
	set("exits", ([
		"east" : __DIR__"street",
		"south" : __DIR__"riverside_w",
		"up" : __DIR__"teahouse_2f",
	]));

	setup();
}

// Room: /d/tianshi/gate.c

inherit ROOM;

void create()
{
	set("short", "天師派山門");
	set("long", @LONG
這裡是天師派的山門﹐一座青石牌坊巍然矗立﹐橫額上刻著「天師
派」三個古樸的篆字﹐兩旁石柱上鐫著一副對聯﹕「朱衣引火煉真丹﹐
丹鼎飛霞證大道」。坊後一條石階沿山而上﹐松柏夾道﹐隱隱有鐘磬之
聲隨風飄下。往北拾級而上便是派中的庭院﹐往西南沿著山道下去﹐可
回到雪亭鎮廣場的東邊。
LONG
	);
	set("detail", ([
		"牌坊" : "青石牌坊歷經風雨﹐「天師派」三字筆勢古拙﹐透著一股道門
氣象。
",
		"對聯" : "對聯寫的是「朱衣引火煉真丹﹐丹鼎飛霞證大道」﹐道盡了天師
派朱衣一脈以火證道的宗旨。
",
		"松柏" : "山道兩旁的松柏蒼翠挺拔﹐枝葉間掛著未化的殘雪。
",
	]));
	set("outdoors", "snow");
	set("exits", ([
		"north" : __DIR__"yard",
		"southwest" : "/d/snow/square_e",
	]));

	setup();
}
// vim: set ts=4 sw=4 syntax=lpc

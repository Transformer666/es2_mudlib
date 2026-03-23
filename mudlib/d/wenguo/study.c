// Room: /d/wenguo/study.c

inherit ROOM;

void create()
{
	set("short", "私塾");
	set("long", @LONG
這是一間寬敞明亮的私塾﹐屋內擺著十幾張書桌﹐桌上放著筆墨
和書本。正前方掛著一幅孔聖人的畫像﹐兩側懸著「學而不思則罔﹐
思而不學則殆」的對聯。從屋內傳來孩童們搖頭晃腦誦讀經書的聲音
﹐朗朗讀書聲令人心曠神怡。往北可回到西大街﹐往南通往縣衙。
LONG
	);
	set("no_fight", 1);
	set("detail", ([
		"畫像" : "孔聖人畫像上繪著一位慈祥的老者﹐手執書卷﹐神態安詳。\n",
		"對聯" : "對聯的字跡蒼勁有力﹐一看便知是出自名家手筆。\n",
	]));
	set("exits", ([
		"north" : __DIR__"street2",
		"south" : __DIR__"yamen",
	]));

	setup();
	replace_program(ROOM);
}

// Room: /d/snow/inn_stable.c

inherit ROOM;

void create()
{
    set("short", "馬房");
    set("long", @LONG
這裡是飲風客棧後面的馬房﹐幾匹騾馬拴在木欄邊﹐不時打著
響鼻刨著蹄子﹐馬槽裡添著新鮮的草料﹐空氣中瀰漫著一股糞草混
雜的氣味﹐牆角堆著幾捆乾草跟一輛卸了轅的板車﹐東北邊有一扇
木門通回客棧的大堂。
LONG
    );
    set("detail", ([ /* sizeof() == 2 */
	"馬槽" : "一溜長長的木頭馬槽釘在木欄邊上﹐槽裡的草料拌得勻勻的﹐看來店小二照料得相當盡心。",
	"草料" : "新鮮的草料散發著一股青草的香氣﹐幾匹騾馬埋著頭嚼得正歡。",
    ]));
    set("exits", ([ /* sizeof() == 1 */
	"northeast" : __DIR__"inn_hall",
    ]));

    setup();
    create_door("northeast", "木門", "southwest", 0);
}

// vim: set ts=4 sw=4 syntax=lpc

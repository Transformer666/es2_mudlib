// Room: /d/wutang/court.c

inherit ROOM;

void create()
{
    set("short", "五堂官府");
    set("long", @LONG
這裡是五堂鎮的官府﹐門前立著兩塊「肅靜」「迴避」的木牌﹐
衙門正堂高懸「明鏡高懸」的匾額。堂上擺著一張寬大的公案﹐案
上放著驚堂木和筆墨紙硯。東邊有一道小門通往別院。
LONG
    );
    set("no_fight", 1);
    set("objects", ([
	__DIR__"npc/inspector" : 1,
    ]));
    set("detail", ([
	"匾額" : "上面寫著「明鏡高懸」四個金色大字。\n",
	"公案" : "一張寬大的紅木公案﹐案上放著驚堂木和文房四寶。\n",
    ]));
    set("exits", ([
	"south" : __DIR__"street2",
	"east" : __DIR__"residence",
	"north" : __DIR__"ngate",
    ]));

    setup();
    replace_program(ROOM);
}

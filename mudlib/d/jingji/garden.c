// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "御花園");
    set("long", @LONG
衙門後方的一座精緻花園，園中亭台樓閣錯落有致，假山流水相映
成趣。花圃裡種植著各色牡丹和芍藥，開得嬌豔欲滴。一條鋪著鵝卵
石的小徑蜿蜒穿過一片修竹林，通往園中的涼亭。涼亭下擺著石桌石凳
，是官員們公務之餘品茶賞花之所。
LONG
    );
    set("exits", ([
        "west" : __DIR__"yamen",
    ]));
    set("no_fight", 1);

    setup();
    replace_program(ROOM);
}

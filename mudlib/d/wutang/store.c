// Room: /d/wutang/store.c

inherit ROOM;

void create()
{
    set("short", "五堂雜貨鋪");
    set("long", @LONG
這裡是五堂鎮的雜貨鋪﹐貨架上擺滿了各式各樣的日用雜貨﹐
從油鹽醬醋到針線布匹應有盡有。掌櫃的算盤打得噼里啪啦響﹐
一邊招呼客人一邊記帳。
LONG
    );
    set("no_fight", 1);
    set("exits", ([
	"east" : __DIR__"street1",
    ]));

    setup();
    replace_program(ROOM);
}

// vim: syntax=lpc
// 鯉君渡南岸 → 五堂碼頭 渡船

#include <room.h>

inherit JOURNEY;

private void create()
{
    set("short", "渡船上");
    set("long", @LONG
你坐上了渡船﹐船夫撐篙離岸﹐逆流往五堂鎮方向駛去。河水拍
打著船身﹐渡船緩緩前行。透過水霧﹐五堂碼頭的輪廓漸漸清晰。
LONG
    );
    set("from_room", "/d/lijun/ferry_south");
    set("to_room", __DIR__"dock");
    set("distance", 8);

    setup();
}

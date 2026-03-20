// vim: syntax=lpc
// 五堂碼頭 渡船：碼頭 → 鯉君渡南岸

#include <room.h>

inherit JOURNEY;

private void create()
{
    set("short", "渡船上");
    set("long", @LONG
你坐上了渡船﹐渡船夫撐起竹篙﹐渡船緩緩離開五堂碼頭。河水
渾濁而湍急﹐渡船在波浪中搖晃﹐渡船夫卻穩穩地站在船頭﹐熟練
地操控著方向。遠處的鯉君渡漸漸出現在視野中。
LONG
    );
    set("from_room", __DIR__"dock");
    set("to_room", "/d/lijun/ferry_south");
    set("distance", 8);

    setup();
}

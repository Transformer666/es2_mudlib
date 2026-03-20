// vim: syntax=lpc
// 鯉君渡 渡船：碼頭 → 南岸

#include <room.h>

inherit JOURNEY;

private void create()
{
    set("short", "渡船上");
    set("long", @LONG
你坐上了渡船﹐老艄公撐起竹篙﹐渡船緩緩離開碼頭。羿水的水
流十分湍急﹐渡船左搖右晃﹐老艄公卻穩穩地站在船頭﹐不時用竹
篙撥開漂來的枯枝。河面上水霧瀰漫﹐兩岸的景色漸漸模糊。
LONG
    );
    set("from_room", __DIR__"dock");
    set("to_room", __DIR__"ferry_south");
    set("distance", 5);

    setup();
}

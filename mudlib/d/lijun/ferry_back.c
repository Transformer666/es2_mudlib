// vim: syntax=lpc
// 鯉君渡 渡船：南岸 → 碼頭

#include <room.h>

inherit JOURNEY;

private void create()
{
    set("short", "渡船上");
    set("long", @LONG
你坐上了渡船﹐老艄公撐起竹篙﹐渡船離開南岸碼頭﹐逆流往北
岸駛去。河水拍打著船身﹐發出嘩嘩的聲響。透過水霧﹐北岸鯉君
渡的碼頭漸漸清晰起來。
LONG
    );
    set("from_room", __DIR__"ferry_south");
    set("to_room", __DIR__"dock");
    set("distance", 5);

    setup();
}

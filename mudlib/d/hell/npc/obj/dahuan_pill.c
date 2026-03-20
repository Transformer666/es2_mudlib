// dahuan_pill.c

inherit ITEM;

void create()
{
    set_name("大環丹", ({"dahuan_pill", "dahuan pill", "pill"}));
    set_weight(200);

    if( !clonep() ) {
        set("unit", "顆");
        set("value", 150000);
        set("long",
            "一顆散發著七彩光芒的丹藥，丹身渾圓如珠，表面流轉著\n"
            "淡淡的靈氣。據說此丹以聖木殘根為引，煉製而成，是地靈\n"
            "任務道具鏈中不可或缺的關鍵靈藥。\n");
    }
    setup();
}

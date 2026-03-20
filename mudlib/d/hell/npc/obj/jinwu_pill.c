// jinwu_pill.c

inherit ITEM;

void create()
{
    set_name("金屋內丹", ({"jinwu_pill", "jinwu pill", "pill"}));
    set_weight(300);

    if( !clonep() ) {
        set("unit", "顆");
        set("value", 200000);
        set("long",
            "一顆金光閃閃的內丹，丹身溫潤如玉，隱隱散發著龍吟之聲。\n"
            "據說此丹乃金屋中封印的遠古靈獸所遺，蘊含著強大的靈力，\n"
            "是地靈任務道具鏈中最終的關鍵材料。\n");
    }
    setup();
}

inherit ITEM;

void create()
{
    set_name("武陀藥箱", ({"medicine_box", "box"}));
    set_weight(3000);

    if( !clonep() ) {
        set("unit", "個");
        set("value", 2000);
        set("long",
            "一個精緻的木質藥箱﹐裡面分隔成許多小格﹐放著各種針\n"
            "灸器具和常用藥材。\n");
    }
    setup();
}

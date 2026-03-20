// vim: syntax=lpc
// old_journal.c - 大宅地窖藏的破舊手札

inherit ITEM;

void create()
{
    set_name("破舊手札", ({"old journal", "journal", "notebook"}));
    set_weight(200);
    if( !clonep() ) {
        set("unit", "本");
        set("value", 500);
        set("long",
            "一本年代久遠的手札﹐封面的皮革已經乾裂發黃。翻開來看﹐\n"
            "裡面用蠅頭小楷記載著一些武學心得﹐雖然大部分已經模糊不清﹐\n"
            "但偶爾能看到幾句關於內功運氣的口訣﹐似乎頗有道理。\n");
    }
    setup();
}

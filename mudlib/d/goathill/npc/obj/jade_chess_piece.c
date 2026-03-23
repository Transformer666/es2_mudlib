// vim: syntax=lpc
// Quest item: 隱士的玉棋子

inherit ITEM;

void create()
{
    set_name("玉棋子", ({"jade_chess_piece", "jade chess piece", "chess_piece", "chess piece"}));
    set_weight(100);

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 300);
        set("long",
            "一枚用山玉雕成的棋子﹐質地溫潤﹐大小正好一握。棋子上\n"
            "刻著精細的紋路﹐顯然是出自高手之手。這應該是一副手工棋\n"
            "具中的一枚﹐缺了它便湊不成完整的一副。\n");
    }
    setup();
}

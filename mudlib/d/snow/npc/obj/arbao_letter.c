// vim: syntax=lpc
// arbao_letter.c - 阿寶寫給阿明的信

inherit ITEM;

void create()
{
    set_name("阿寶的信", ({"arbao letter", "letter", "abao letter"}));
    set_weight(50);
    if( !clonep() ) {
        set("unit", "封");
        set("value", 0);
        set("long",
            "一封用粗紙折好的信件﹐信封上歪歪扭扭地寫著「阿明哥哥收」\n"
            "幾個字﹐字跡稚嫩﹐看得出寫信的人不太識字。信封上還沾著幾\n"
            "滴乾涸的淚痕。\n");
    }
    setup();
}

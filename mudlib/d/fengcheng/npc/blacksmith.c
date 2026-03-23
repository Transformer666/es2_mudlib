// NPC: /d/fengcheng/npc/blacksmith.c

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("鐵匠老王", ({"blacksmith", "wang", "old wang"}));
    set_race("human");
    set_class("commoner");
    set_level(18);

    set("age", 52);
    set("gender", "male");
    set("long",
        "一個身材魁梧的壯漢﹐赤著上身﹐露出滿身結實的肌肉﹐被爐\n"
        "火映得紅通通的。他就是風城鐵匠鋪的老王﹐據說年輕時也闖蕩\n"
        "過江湖﹐後來不知為什麼隱退到這偏遠的風城﹐開了這間鐵匠鋪。\n"
        "雖然已是半百之人﹐但掄起大錘來虎虎生風﹐力道驚人。\n");
    set("chat_chance", 2);
    set("chat_msg", ({
        "鐵匠老王一邊打鐵一邊說道﹕好鐵要千錘百煉﹐跟練武是一個道理。\n",
        "鐵匠老王擦了擦額頭的汗水﹐嘆道﹕年紀大了﹐體力不如從前了。\n",
        "鐵匠老王看了看你的兵器﹐搖了搖頭﹐似乎不太滿意。\n",
    }));
    setup();
    carry_money("coin", 150);
}

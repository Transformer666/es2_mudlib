// storyteller.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("說書先生", ({"storyteller", "wutang_storyteller"}));
    set_race("human");
    set_class("commoner");
    set_level(8);

    set("age", 45);
    set("long",
	"一個留著山羊鬍子的中年人﹐正搖頭晃腦地講述著天朝帝國的種\n"
	"種傳奇故事﹐旁邊圍了一圈聽眾。\n");
    set("chat_chance", 3);
    set("chat_msg", ({
	"說書先生拍案道﹕話說這天朝帝國﹐自開國以來已有數百年﹐英雄豪傑輩出不窮﹗\n",
	"說書先生說道﹕要說這世上最厲害的武功﹐莫過於封山派的劍法﹐一劍既出﹐鬼神皆驚﹗\n",
	"說書先生搖搖頭道﹕但說到最神秘的﹐還得數茅山派的道術﹐那可是能呼風喚雨的本事。\n",
	"說書先生壓低聲音道﹕聽說武山上有座古老的神殿﹐裡面住著一個神秘的老人﹐沒人知道他的來歷。\n",
	"說書先生道﹕各位看官﹐你們可聽說過上古異獸﹖傳說天朝各地都潛伏著這些可怕的怪物。\n",
	"說書先生道﹕虎刀門的韓笑韓大俠﹐那可是刀法天下第一﹐一手虎刀出神入化﹗\n",
    }));
    setup();
    carry_money("coin", 50);
}

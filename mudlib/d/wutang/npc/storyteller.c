// storyteller.c
// Supports quest: 別館內的欽差來五堂要做甚麼？

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
	"說書先生壓低聲音道﹕說起來﹐五堂鎮有一樁懸案﹐傳說一把叫「飲血」的名劍被人丟進了河裡﹐至今下落不明。\n",
    }));
    setup();
    carry_money("coin", 50);
}

void relay_say(object ob, string msg)
{
    if( !userp(ob) ) return;
    if( is_fighting() || is_chatting() ) return;

    if( strsrch(msg, "失蹤") >= 0 || strsrch(msg, "案件") >= 0
    ||  strsrch(msg, "調查") >= 0 || strsrch(msg, "欽差") >= 0
    ||  strsrch(msg, "御史") >= 0 ) {
	if( ob->query("quest/inspector_case_done") ) {
	    do_chat("說書先生壓低聲音道﹕聽說那件案子已經有了眉目﹐多虧了你呀。\n");
	    return;
	}
	if( ob->query_temp("pending/inspector_case") >= 1 ) {
	    do_chat(({
		"說書先生四下張望了一下﹐壓低聲音道﹕你也聽說了﹖\n",
		"說書先生說道﹕近來武山一帶確實有好幾個人莫名其妙地失蹤了。\n",
		"說書先生說道﹕有個樵夫跟我說﹐他有一次上山砍柴﹐在那座山洞裡看到一尊石雕像。\n",
		"說書先生壓低聲音道﹕他說那雕像下面好像有條密道﹐通往不知什麼地方。\n",
		"說書先生說道﹕從那以後他再也不敢上山了。你要是有膽量﹐可以去巫山洞窟裡看看。\n",
		"說書先生說道﹕對了﹐這事兒你跟御史大人說一聲﹐也許對他的案子有用。\n",
	    }));
	    ob->set_temp("pending/inspector_case", 2);
	    return;
	}
	do_chat("說書先生搖搖頭道﹕什麼失蹤不失蹤的﹐我可什麼都不知道。\n");
	return;
    }

    if( strsrch(msg, "巫山") >= 0 || strsrch(msg, "武山") >= 0
    ||  strsrch(msg, "洞窟") >= 0 ) {
	do_chat("說書先生壓低聲音道﹕武山上的洞窟﹖那地方可不簡單﹐聽說裡面有座古老的石雕像﹐還有些奇怪的符號。\n");
	return;
    }

    if( strsrch(msg, "飲血") >= 0 || strsrch(msg, "名劍") >= 0
    ||  strsrch(msg, "丟劍") >= 0 ) {
	if( ob->query("quest/yinxue_found_done") ) {
	    do_chat("說書先生驚訝地說道﹕什麼﹗你真的找到了飲血﹖真是不可思議﹗\n");
	    return;
	}
	do_chat(({
	    "說書先生壓低聲音道﹕你也聽說了那把飲血﹖\n",
	    "說書先生說道﹕傳說多年前有個劍客在五堂犯了事﹐官兵追捕時他把飲血丟進了河裡。\n",
	    "說書先生說道﹕碼頭南邊有個河灣﹐水流平緩﹐東西沉下去不容易被沖走。\n",
	    "說書先生說道﹕你要是有興趣﹐可以去那邊的淺灘找找看。\n",
	}));
	return;
    }
}

// qinchai.c -- 欽差柳明軒：奉旨南下五堂鎮、暫駐別館的緋袍欽差。
//              docs 主線疑團「別館內的欽差來五堂要做甚麼？」(docs/01-世界觀與
//              劇情/05-主線任務與NPC.md:31)之伏筆人物，並呼應 docs 05:23
//              「朝廷究竟有沒有關注侮天鬼傳說？」之疑團。docs 未給欽差任務之
//              完整解答，故本 NPC 純作 lore 對白與伏筆 hook(ask about 朝廷/
//              侮天鬼/聖木/欽差來意)——不臆造完整朝廷任務鏈/獎勵(caveat)。
//
// 機制：純 lore 對話 NPC(ask-handler)，不發物、不改技能、不推獎勵旗標。
//   旗標僅 query("quest/wutang_qinchai_lore")記「是否已聽過來意」(無獎勵)。
//
// 鐵則遵循：
//   #10：本檔無 ::die()/destruct()。
//   #11：本檔為 NPC(非房間)，不涉 replace_program。
//   #14：init() 招呼加 this_player()&&interactive() 護衛；不覆寫 relay_say。
//   handler 守衛：do_ask 開頭即 is_fighting()/is_chatting() 守衛。
//
// 範式來源：d/snow/npc/heiyilaoren.c(伏筆 NPC：ask-about 多 token、init 招呼
//   護衛、accept_fight)；侮天鬼/聖木 lore 語彙對齊 docs 01-05 主線疑團與
//   d/capital/saintroot.c(聖木殘根)之既有設定(僅讀以對齊，未改該檔)。

#include <ansi.h>
#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name(HIR "欽差" NOR, ({ "qinchai", "imperial envoy", "envoy", "柳明軒", "欽差", "欽差大人" }) );
	set("nickname", HIR "欽差柳明軒" NOR);
	set_attr("str", 22);
	set_attr("con", 21);
	set_attr("dex", 22);
	set_attr("int", 26);
	set_race("human");
	set_class("soldier");
	set_level(34);
	set_skill("unarmed", 70);
	set_skill("dodge", 70);
	set_skill("force", 65);
	set_skill("sword", 65);
	set_skill("parry", 65);
	set_skill("literate", 60);

	set("gender", "male");
	set("age", 43);
	set("long",
		"這位是奉旨南下的欽差柳明軒。他一襲緋色官袍﹐腰繫玉帶﹐生得\n"
		"面如冠玉、三縷長鬚﹐一雙眼睛卻精光四射﹐既有讀書人的儒雅﹐\n"
		"又透著官場歷練出來的城府。他端坐在公案之後﹐慢條斯理地翻看\n"
		"著卷宗﹐偶爾抬眼打量來客一眼﹐那目光便似要將人看穿。聽鎮上\n"
		"人說﹐這位欽差是月前到的五堂﹐既不查賦稅﹐也不問刑名﹐成日\n"
		"裡只召些三教九流的人來問些稀奇古怪的江湖傳聞﹐誰也猜不透朝\n"
		"廷千里迢迢派他來這小小五堂鎮﹐究竟所為何來。\n"
		"你或許可以問問他：ask qinchai about 來意。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"欽差執筆在卷宗上記下幾行小字﹐眉頭微微蹙起。\n",
		"欽差呷了一口茶﹐淡淡道﹕江湖之大﹐無奇不有﹐有些事 ... 朝廷不能不防。\n",
		"欽差抬眼掃過廳中﹐沉聲道﹕本欽差所問之事﹐爾等聽過便罷﹐切莫聲張。\n",
	}));
	setup();
	carry_object("/obj/area/obj/cloth")->wear();
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	if( this_player() && interactive(this_player()) && !is_fighting() ) {
		do_chat((: command,
			"say 你是何人﹖也罷﹐本欽差正要尋些走江湖的人問話。你且過來——本欽差有話問你。(ask qinchai about 來意)" :));
	}
}

int do_ask(string arg)
{
	object me = this_player();
	int heard;

	if( !arg )
		return notify_fail("你想問欽差大人甚麼﹖（試試 ask qinchai about 來意）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("欽差正凝神批閱卷宗﹐沒空理你。\n");

	if( !me ) return 0;

	heard = me->query("quest/wutang_qinchai_lore");

	// ── 來意 ──
	if( arg == "qinchai about 來意" || arg == "qinchai about 欽差"
	 || arg == "qinchai about 朝廷" || arg == "qinchai about errand" ) {
		if( !heard ) me->set("quest/wutang_qinchai_lore", 1);
		do_chat(({
			(: command, "say 本欽差奉的是密旨﹐來意本不該與你這江湖中人說。也罷——你既走南闖北﹐有些事﹐朝廷正要借你們的耳目。" :),
			(: command, "say 近年江湖上鬼影幢幢﹐動物war、蜈蚣亂、四鬼四神之說甚囂塵上﹐更有一樁古老的傳說 ... 漸漸又在民間流傳開來。朝廷不能不防——本欽差此來五堂﹐便是為查訪這傳說的虛實。" :),
		}));
		return 1;
	}

	// ── 侮天鬼傳說（呼應 docs 05:23「朝廷究竟有沒有關注侮天鬼傳說？」）──
	if( arg == "qinchai about 侮天鬼" || arg == "qinchai about 傳說"
	 || arg == "qinchai about 侮天" || arg == "qinchai about legend" ) {
		do_chat(({
			(: command, "say （欽差神色一肅﹐壓低了嗓子）你也聽過『侮天鬼』這名字﹖朝廷的史檔裡﹐確有這麼一筆——千百年前﹐曾有一頭禍亂天下的兇物被群仙合力封鎮﹐朝廷視之為國朝氣運所繫的頭等機密。" :),
			(: command, "say 近來各地封印鬆動的奏報雪片似地遞進京裡﹐聖上震怒﹐這才密遣本欽差等人分赴各方查訪。這五堂鎮的鎮天神廟、巫山雕像﹐皆是當年立封印的所在——本欽差來此﹐正為勘驗這幾道封印可還鎮得住。" :),
			(: command, "say 你若在江湖上聽得封印、聖木、四鬼四神之類的風聲﹐記著到別館來報與本欽差知道。朝廷 ... 是斷不會坐視這傳說成真的。" :),
		}));
		return 1;
	}

	// ── 聖木（呼應主線聖木殘根伏筆，d/capital/saintroot.c）──
	if( arg == "qinchai about 聖木" || arg == "qinchai about 封印"
	 || arg == "qinchai about saintwood" || arg == "qinchai about seal" ) {
		do_chat(({
			(: command, "say 聖木麼 ... （欽差眼神一凜）你竟也知道聖木﹖那是當年封鎮兇物的根本所繫﹐生於京畿地脈之下。本欽差接到的密報裡﹐正有人在京畿地底動了聖木的根節——此事干係重大﹐你若知道甚麼﹐務必如實道來。" :),
			(: command, "say 這五堂的封印與京畿的聖木﹐本是一脈相承的鎮邪大陣。封印若破、聖木若毀﹐當年鎮入地底的東西﹐便要重見天日了 ... 此事本欽差言盡於此﹐你好自為之。" :),
		}));
		return 1;
	}

	return notify_fail("欽差淡淡道﹕本欽差問的是正事﹐你若無要緊的話﹐便退下罷。（試試 ask qinchai about 來意／侮天鬼／聖木）\n");
}

int accept_object(object who, object ob)
{
	command("say 本欽差乃朝廷命官﹐豈會收受你江湖中人的東西﹖收回去罷。");
	return 0;
}

int accept_fight(object ob)
{
	do_chat((: command,
		"say 大膽﹗竟敢對朝廷欽差動手﹗來人哪﹐還不將這狂徒拿下﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc

// captain.c -- 雍府門前的護衛統領（純劇情伏筆，埋下「朝廷是否關注侮天鬼／聖木傳說」的疑團，不開任何任務）
//
// 設定：雍和首相位極人臣，近來常為著些「古怪的舊案」召人入府密議。此統領沉穩
//       多智，是相爺的心腹，口風極緊。玩家可向他打聽雍和、首相、朝廷之事，他只
//       給三分官場閒談，到了「朝廷是否關注侮天鬼/聖木舊事」這一節，更是諱莫如深
//       ——點到為止，不證實、不否認，只留一道伏筆。本 NPC 不開啟、不推進任何任務。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("護衛統領", ({ "guard captain", "captain", "menli" }) );
	set("nickname", "相府統領");
	set_attr("str", 24);
	set_attr("con", 22);
	set_attr("int", 20);
	set_race("human");
	set_class("fighter");
	set_level(22);

	set_skill("unarmed", 70);
	set_skill("sword", 65);
	set_skill("parry", 55);
	set_skill("dodge", 55);
	set_skill("force", 50);

	set("age", 38);
	set("gender", "male");
	set("long",
		"一個身形挺拔的護衛統領﹐按刀肅立在相府門側。他不似尋常\n"
		"門卒那般虛張聲勢﹐一身青色勁裝收拾得乾淨利落﹐腰間佩刀的\n"
		"刀柄被磨得發亮﹐顯是用慣了的。他目光沉靜內斂﹐掃過你時不\n"
		"動聲色﹐卻教人覺出一股深藏不露的精悍。聽聞他是相爺的心腹\n"
		"﹐口風極緊﹐相府裡的事﹐他知道的怕是比誰都多。\n"
		"你或許可以問問他﹕ask captain about 雍和。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"護衛統領按刀肅立﹐目光沉靜地掃過廣場上往來的人流。\n",
		"護衛統領對候見的謁客淡淡道﹕相爺今日不見客﹐諸位請回罷。\n",
		"護衛統領眉頭微不可察地一蹙﹐似在思忖著甚麼心事﹐旋即又恢復了沉靜。\n",
	}));
	setup();
	carry_object("/obj/area/obj/cloth")->wear();
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	if( this_player() && interactive(this_player()) ) {
		if( !is_fighting() )
			do_chat((: command,
				"say 這位客官﹐相府重地﹐閒人莫要在門前逗留。" :));
	}
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這位統領甚麼﹖（試試 ask captain about 雍和）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("護衛統領正按刀肅立﹐目不斜視﹐沒空理你。\n");

	// 雍和首相其人：官場閒談，點出位極人臣、聖眷正隆
	if( arg == "captain about 雍和"
	||  arg == "guard captain about 雍和"
	||  arg == "captain about 首相"
	||  arg == "guard captain about 首相"
	||  arg == "captain about 相爺"
	||  arg == "captain about premier"
	||  arg == "captain about minister" ) {
		do_chat(({
			(: command, "say 我家相爺諱雍和﹐位居首輔﹐佐天子調燮陰陽、總領百揆﹐這滿朝的文武﹐誰不敬讓三分。" :),
			(: command, "say 相爺近來聖眷正隆﹐府裡日日車馬盈門。客官若是來投謁的﹐先遞了名帖﹐在門前候著便是﹐莫要多問。" :),
		}));
		return 1;
	}

	// 朝廷／朝局：諱莫如深，並把話頭引向「相爺近來在查的古怪舊案」這道伏筆
	if( arg == "captain about 朝廷"
	||  arg == "guard captain about 朝廷"
	||  arg == "captain about 朝局"
	||  arg == "captain about 朝中"
	||  arg == "captain about court"
	||  arg == "captain about 官府" ) {
		do_chat(({
			(: command, "say 朝廷的事﹐豈是你我在這門前能議論的﹖客官慎言。" :),
			(: command, "say ……只是近來相爺確是憂心忡忡。半月來夜夜秉燭﹐召了幾位欽天監與禮部的老先生入府密議﹐翻的盡是些蟲蛀的舊檔。所議何事﹐連我也不得與聞。" :),
			(: command, "say 客官若無正經事﹐還是請回罷。這話﹐出得我口﹐入得你耳﹐切莫再對旁人提起。" :),
		}));
		return 1;
	}

	// 侮天鬼／聖木舊事：核心伏筆——統領大驚變色，諱莫如深，不證實、不否認，甚麼也不開
	if( arg == "captain about 侮天鬼"
	||  arg == "guard captain about 侮天鬼"
	||  arg == "captain about 聖木"
	||  arg == "guard captain about 聖木"
	||  arg == "captain about 舊案"
	||  arg == "captain about 卯木"
	||  arg == "captain about saintwood"
	||  arg == "captain about demon" ) {
		do_chat(({
			(: command, "say ……你方才說甚麼﹖" :),
			(: command, "say 護衛統領的臉色霎時沉了下來﹐按刀的手不自覺地緊了一緊﹐目光如刀般在你臉上來回逡巡。" :),
			(: command, "say 這四個字﹐豈是你一個外鄉人隨口便說得的﹖我不知你是從何處聽來這等市井荒誕的謠言——相爺府上﹐從不沾這些不經之談。" :),
			(: command, "say 我勸客官一句：有些事﹐知道得越少﹐活得越長。這話我只說一遍。速速離了相府門前﹐莫要自誤。" :),
		}));
		return 1;
	}

	// 統領本人／相府門禁：閒談，烘托其心腹身份與門庭森嚴
	if( arg == "captain about 統領"
	||  arg == "captain about captain"
	||  arg == "captain about 相府"
	||  arg == "captain about 雍府"
	||  arg == "guard captain about 相府"
	||  arg == "captain about mansion" ) {
		do_chat(({
			(: command, "say 在下不過是相府裡管些護衛門禁的粗人﹐當不得客官動問。" :),
			(: command, "say 這雍府門禁森嚴﹐非有相爺的手諭名帖﹐縱是王公也難擅入。客官還是莫在門前久留的好。" :),
		}));
		return 1;
	}

	return notify_fail("護衛統領沉著臉﹐並不答你﹐只按刀肅立。（試試 ask captain about 雍和）\n");
}

int accept_fight(object ob)
{
	do_chat((: command, "say 放肆﹗膽敢在相府門前撒野﹐你是活得不耐煩了﹗來人﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc

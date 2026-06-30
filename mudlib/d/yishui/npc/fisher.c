// fisher.c -- 煙波河灘上垂釣的老漁夫：羿水小魚村的 lore/氣氛 NPC。
//   村裡頂年長、頂見過世面的老人，獨坐青石垂釣看水。ask fisher about <題目>
//   可聽他講羿水這條河、小魚村的來歷風物、漁港蘆蕩的不太平等鄉野見聞。
//   純劇情閒談，不給物、不動旗標，與任何任務鏈無涉。
//
// 【runtime 鐵則】
//   - NPC 有自訂 init()(add_action do_ask "ask")；招呼 do_chat 加 interactive()
//     護衛（lesson #14：防 say-storm）。
//   - do_ask handler 守衛 is_fighting()/is_chatting()。不 replace_program。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("老漁夫", ({ "old fisher", "fisher", "yufu" }) );
	set("nickname", "老漁夫");
	set_race("human");
	set_class("commoner");
	set_level(8);

	set("age", 71);
	set("gender", "male");
	set("long",
		"一個白髮蒼蒼的老漁夫﹐脊背已被一輩子的風霜壓得佝僂了﹐\n"
		"一張臉曬得黧黑﹐溝壑也似的皺紋裡盡是水上歲月的痕跡。他枯瘦\n"
		"的手裡握著一根用了不知多少年的舊釣竿﹐眼神卻時時望向那無邊\n"
		"的煙波出神﹐像在看水﹐又像在想些極遙遠的事。他是這小魚村裡\n"
		"頂年長、也頂見過世面的人﹐你不妨向他打聽打聽這羿水的風物\n"
		"(ask fisher about 羿水)。\n");
	set("chat_chance", 5);
	set("chat_msg", ({
		"老漁夫望著煙波出神﹐良久﹐才悠悠地歎了口氣。\n",
		"老漁夫慢悠悠地把釣線往水裡一甩﹐也不大在乎釣不釣得著。\n",
		"老漁夫低聲哼起一支不成調的漁歌﹐調子蒼老而綿長。\n",
	}));

	setup();
}

void init()
{
	::init();
	// do_ask 須在任何早退之前註冊。
	add_action("do_ask", "ask");

	// 招呼加 interactive(this_player()) 護衛——只對真人(lesson #14)。
	if( this_player() && interactive(this_player()) && !is_fighting() )
		do_chat((: command,
			"say 客官也是循著羿水尋到這煙波深處來的麼﹖難得難得﹐坐下歇歇﹐聽老朽同你說說這河上的事。" :));
}

// lore 閒談（純劇情，不給物、不動旗標）：講羿水、小魚村來歷、漁港蘆蕩之不太平。
// handler 守衛 is_fighting()/is_chatting()。
int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想向老漁夫打聽些甚麼﹖(試試 ask fisher about 羿水)\n");
	if( is_fighting() || is_chatting() )
		return notify_fail("老漁夫正望著煙波出神﹐恍若未聞。\n");

	// 羿水這條河
	if( arg == "fisher about 羿水"
	||  arg == "fisher about 河"
	||  arg == "fisher about yishui" ) {
		do_chat(({
			"老漁夫收回望著煙波的目光﹐慢悠悠地說道﹕\n",
			(: command, "say 你腳下這條河，便是羿水嘍。它打那京畿城裡淌出來，一路東流，過了城便寬緩開來，成了這煙波蕩漾的水鄉。" :),
			(: command, "say 上游靠著河吃飯的，是漕幫那些扛糧運貨的漢子；下游靠著河吃飯的，便是咱這小魚村撒網捕魚的人家了。一條羿水，養著兩樣的人，也聽過兩樣的故事哪。" :),
		}));
		return 1;
	}

	// 小魚村的來歷
	if( arg == "fisher about 小魚村"
	||  arg == "fisher about 魚村"
	||  arg == "fisher about 村子"
	||  arg == "fisher about 村" ) {
		do_chat(({
			"老漁夫拿釣竿往村子的方向一指﹐眼裡有了些暖意﹕\n",
			(: command, "say 咱這小魚村哪，沒甚麼名堂，攏共也就十來戶打魚的人家，世世代代守著這片煙波過活。村裡的人，生在水上，老在水上，連名字都懶得起個響亮的，就喚作『小魚村』，圖個實在。" :),
			(: command, "say 日子是清苦了些，可你瞧這滿江的煙波、這點點的漁火——城裡人拿金山銀山，也未必換得來這份清靜自在哪。" :),
		}));
		return 1;
	}

	// 漁港蘆蕩之不太平（呼應 wharf 的水獺/漁霸獵場）
	if( arg == "fisher about 蘆蕩"
	||  arg == "fisher about 蘆葦蕩"
	||  arg == "fisher about 漁港"
	||  arg == "fisher about 水獺"
	||  arg == "fisher about 漁霸"
	||  arg == "fisher about 不太平" ) {
		do_chat(({
			"老漁夫的臉色沉了下來﹐長長地歎了口氣﹕\n",
			(: command, "say 唉，提起那漁港外的蘆蕩，近年是越發不太平嘍。蕩裡的水獺一年比一年兇，成群結隊地上岸來咬壞漁網、偷食簍裡的魚，連單身的後生都敢撲咬。" :),
			(: command, "say 更可恨的是那幾個橫行水上的『漁霸』，仗著一身蠻力，霸佔了蕩裡魚蝦最豐的好水，不許咱老實人下網，還時常勒索村人的漁獲。村裡人受夠了氣，卻又奈何他不得——客官若是有幾分身手，肯替咱漁人除一除這禍患，那可真是積德嘍。" :),
		}));
		return 1;
	}

	// 老漁夫自己
	if( arg == "fisher about 老漁夫"
	||  arg == "fisher about 你"
	||  arg == "fisher about 老朽"
	||  arg == "fisher about fisher" ) {
		do_chat(({
			"老漁夫渾濁的眼裡漾起一絲笑意﹕\n",
			(: command, "say 老朽麼？在這羿水上撒了五十多年的網嘍，這河裡哪一道汊、哪一片水深、哪一處藏魚，閉著眼睛也摸得著。如今老胳膊老腿，網撒不動了，便只來這河灘上坐坐、釣兩竿閒魚，看看這一江的煙波。" :),
			(: command, "say 看了一輩子的水，倒看出些道理來——這水啊，看著軟，繞著走，可它要去的地方，攔也攔不住。人活一世，能學得這水三分的脾性，便算沒白活了。" :),
		}));
		return 1;
	}

	return notify_fail("老漁夫側耳聽了聽﹐和氣地問﹕客官是想問這羿水？小魚村？還是那漁港蘆蕩的事？\n");
}

int accept_fight(object ob)
{
	do_chat((: command, "say 老朽一把年紀，與世無爭，客官同我這糟老頭子過不去做甚？" :));
	return notify_fail("老漁夫只顧望著煙波垂釣﹐對你視若無睹。\n");
}

// vim: set ts=4 sw=4 syntax=lpc

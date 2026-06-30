// fishlord.c -- 漁霸鐵頭蛟，霸佔羿水蘆蕩好水、欺凌漁人的水上惡棍。
//
// 結構沿用 /d/heifeng/npc/greywolf.c：可 kill、會還手、不主動攻擊路人(無 attitude)，
// 殺後只給 score(無錢)。戰力定在 level 32 一線——羿水漁港這片水鄉獵場的中段對手，
// 較蒼狼(26)更硬、合 lv 15-35 區間的高段；替受欺凌的漁人除此惡棍便是這一帶的快意事。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("漁霸鐵頭蛟", ({ "fish lord", "fishlord", "tietoujiao", "jiao" }) );
	// 仗一身蠻力橫行水上：氣力雄厚、形體粗壯、略諳水上拳腳。
	set_attr("con", 42);
	set_attr("str", 40);
	set_attr("dex", 28);
	set_race("human");
	set_class("commoner");
	set_level(32);

	// 蠻力剛猛、拳腳精熟、略諳吐納內力。
	set_skill("unarmed", 52);
	set_skill("dodge", 30);
	set_skill("parry", 34);
	set_skill("force", 30);

	// 厚其氣血，使之耐打、有來有往（量同蒼狼一線，較重）。
	advance_stat("kee", 50);

	set("age", 33);
	set("gender", "male");
	set("long",
		"一個赤膊光腳、橫行水上的惡棍——人稱漁霸『鐵頭蛟』。他生\n"
		"得膀闊腰圓﹐黝黑的脊背上虯結著一身腱子肉﹐胸前一道猙獰的舊\n"
		"疤﹐手裡橫著一桿沉甸甸的魚叉。他霸佔了蘆蕩裡魚蝦最豐的幾片\n"
		"好水﹐不許老實漁人下網﹐還時常勒索村人的漁獲﹐村人受其欺凌\n"
		"已久﹐敢怒而不敢言。此刻他叉著腰擋在水道口﹐斜睨著你﹐一臉\n"
		"橫肉滿是不耐。\n");
	// 純 score：江湖歷練(升級)、拳腳精熟、武術造詣、武學之道、實戰經驗。無錢幣。
	set("bounty", ([
		"survive"         : 460,
		"unarmed mastery" : 100,
		"martial art"     : 70,
		"martial mastery" : 36,
		"combat"          : 38,
	]));
	setup();
}

// 奉陪到底、凶悍反擊（他並不主動撲路人﹐由玩家 kill 起釁——替漁人出氣）。
int accept_fight(object ob)
{
	do_chat((: command, "say 漁霸鐵頭蛟啐了一口﹐橫起魚叉獰笑﹕哪來的雜碎敢管爺爺的閒事﹖叫你曉得這羿水是誰的天下﹗" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc

// fengshen_mirror.c -- 地獄地氣塔頂黑袍怪人相贈的奇珍：封神寶鏡。
//
// 來歷（承接 canon：docs 01-世界觀與劇情/05-主線任務與NPC.md「重要任務 NPC 一覽」一列
//   L122「黑袍怪人 @ 地獄地氣塔頂 → 封神寶鏡 + 離玄光熾」）：
//   京畿地脈所鍾、地氣磅礡之處那座上古地氣塔的塔頂，除卻那司一方地氣的地靈，尚有
//   一道形蹤詭秘的黑袍怪人，亙古守在這地氣最盛之巔。怪人不言來歷，只道自己看守著
//   兩件上古奇珍——一面封神寶鏡、一道離玄光熾。這面『封神寶鏡』乃上古封神一役所遺
//   的法鏡，鏡背鑄滿盤虬的封神古篆，鏡面幽幽流轉著一層青冥寒光；持鏡之人但凝神
//   照之，鏡中那縷封神古意便緩緩護住其心神、映照其本相，邪祟戾氣不敢欺近。怪人見
//   少俠能登臨這地氣絕頂、心志不為塔頂磅礡地氣所撼，便將這面寶鏡相贈，了一段塔頂
//   之緣。
//
// 形制：佩於頸上、貼身懸照的法鏡(F_NECK_EQ，wear_as "neck_eq"——以「懸照護身」的隨身
//   法鏡呈現最合「寶鏡」之意，鏡 sun_moon_relic/hunter_necklace 之 neck_eq 做法)。佩之
//   以 apply_armor/neck_eq 加成(僅用 driver 確實取用之 combat 鍵，見 feature/char/combat.c
//   及 feature/armor/neck_eq.c：armor/spi/per)——以「青冥寒光護心映本相、邪祟不近」對應
//   護體(armor)為主、佐以精神(spi)與感知(per)，量級貼合一面上古護身法鏡（略勝尋常符
//   籙、不逾神兵）。設 no_sell：黑袍怪人塔頂相贈之奇珍，玩家自當留用，斷不可變賣。
//
// 注意：黑袍怪人逐玩家 clone+move 同步交付（每位登頂者各得一面），鏡 chuanling/yang_charm
//   之做法：僅以 set("unique",1) 作風味標記，不 inherit F_UNIQUE，免多人佩鏡時意外自毀。

#include <ansi.h>
#include <armor.h>

inherit F_NECK_EQ;

void create()
{
	set_name(HIC "封神寶鏡" NOR,
		({ "fengshen mirror", "mirror", "封神寶鏡", "寶鏡", "鏡" }) );
	set_weight(800);
	setup_neck_eq();

	if( !clonep() ) {
		set("wear_as", "neck_eq");
		set("unit", "面");
		set("value", 1);
		set("unique", 1);
		set("no_sell", 1);
		set("long",
			"一面古樸沉厚的青銅法鏡，鏡身只巴掌大小，繫著一條揉得極韌\n"
			"的玄色絲絛，可懸於頸間貼身佩照。鏡背鑄滿了盤虬詰曲、密如蛛\n"
			"網的封神古篆，篆紋深處隱隱沁著一層青冥的幽光；鏡面則不染纖\n"
			"塵，幽幽流轉著一縷青冥寒光，凝神照之，鏡中竟似映出觀者的一\n"
			"點本相，邪祟戾氣俱被那寒光映得無所遁形。地氣塔頂那道黑袍怪\n"
			"人說，這便是上古封神一役所遺的『封神寶鏡』，鏡中封著一縷封\n"
			"神古意，佩之在身、凝神照之，能護心神、映本相，教那陰邪戾氣\n"
			"不敢欺近。入手沉沉，貼身竟透出一縷說不出的清冷與安定。\n"
			"(佩於頸上：wear mirror)\n");
		set("wear_msg",
			HIC "$N將那面封神寶鏡懸上頸間，鏡面青冥寒光霎時一盛，"
			"一縷清冷而安定的封神古意自鏡中漫出，沁入$N周身百骸，護住了心神。\n" NOR);
		set("remove_msg",
			"$N將那面封神寶鏡自頸間取下，鏡中那縷青冥寒光也隨之斂回鏡內。\n");
		// 上古護身法鏡：護體(armor)為主、佐以精神(spi)與感知(per)——青冥寒光護心映本相之賜。
		set("apply_armor/neck_eq", ([
			"armor" : 12,
			"spi"   : 4,
			"per"   : 3,
		]) );
	}

	setup();
}

// vim: set ts=4 sw=4 syntax=lpc

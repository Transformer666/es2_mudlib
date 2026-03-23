// vim: syntax=lpc
// 任務物品：失竊的古卷

#include <armor.h>

inherit ITEM;

void create()
{
	set_name("泛黃古卷", ({"ancient_manuscript", "manuscript", "scroll"}));
	set_weight(500);

	if( !clonep() ) {
		set("unit", "卷");
		set("value", 500);
		set("long",
			"一卷泛黃的手抄本﹐紙質雖然已經有些脆弱﹐但上面的字跡\n"
			"仍然清晰可辨。內容似乎記載著一段古老的劍術心法﹐旁邊\n"
			"還附有精細的招式圖解。卷首寫著「劍意殘篇」四個字。\n");
	}

	setup();
}

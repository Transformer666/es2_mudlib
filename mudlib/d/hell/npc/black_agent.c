// vim: syntax=lpc

#include <npc.h>

inherit F_FIGHTER;

void create()
{
	set_name("黑無常", ({"black_agent", "black", "heiwuchang"}));
	set_attr("str", 28);
	set_attr("dex", 26);
	set_attr("con", 25);
	set_attr("int", 22);
	set_attr("spi", 30);
	set_attr("wis", 24);
	set_race("malik");
	set_class("commoner");
	set_level(80);

	set_skill("unarmed", 120);
	set_skill("dodge", 100);
	set_skill("parry", 90);
	set_skill("force", 100);

	set("age", 5320);
	set("gender", "male");
	set("long",
		"黑無常屬於巫首族﹐他看起來膽識過人﹐一副天不怕地不怕的\n"
		"模樣。他負責搜尋那些亂殺無辜之人﹐帶到閻王面前接受審判。\n");

	set("chat_chance", 3);
	set("chat_msg", ({
		"黑無常冷冷地說道﹕殺人者﹐終將受到審判。\n",
		"黑無常環顧四周﹐似乎在搜尋著什麼人的蹤跡。\n",
		"黑無常沉聲道﹕閻王座前﹐善惡自有分曉。\n",
	}));

	setup();
	carry_object(STOCK_WEAPON("staff"))->wield();
	carry_object(STOCK_ARMOR("cloth"))->wear();
}

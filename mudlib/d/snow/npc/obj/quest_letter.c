// quest_letter.c - 驛站送信任務信件

inherit ITEM;

void create()
{
	set_name("信件", ({"letter", "quest letter", "mail"}));
	set_weight(50);
	if( !clonep() ) {
		set("unit", "封");
		set("value", 1);
		set("long",
			"一封用火漆封好的信件﹐信封上用工整的楷書寫著收件人的名字﹐\n"
			"看起來是一封頗為重要的書信。信封的角上蓋著驛站的朱印。\n");
	}
	setup();
}

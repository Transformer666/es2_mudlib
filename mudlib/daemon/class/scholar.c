inherit F_DBASE;

static void
create()
{
}

// 升級精氣神成長（docs 02/01）：每升一級，精(dex)/氣(con)/神(spi)依「屬性÷除數」隨機提升。
// 書生：精5/氣3/神3（精成長最慢、神氣偏快）。
void
advance_level (object me)
{
	if (!objectp(me)) return;
	me->advance_stat("gin", 1 + random(me->query_attr("dex") / 5));
	me->advance_stat("kee", 1 + random(me->query_attr("con") / 3));
	me->advance_stat("sen", 1 + random(me->query_attr("spi") / 3));
}

string
query_rank (object obj, string politness)
{
	if (!politness)
		return "書生";

	switch (politness) {
		case "self":
			return "在下";
		case "respectful":
			return "相公";
		case "rude":
		default:
			return "酸丁";
	}
}

// brother_praise()（docs 02-04 L24-32「聲望軸（職業專屬）」）：同職業互讚由
// cmds/usr/praise.c 呼叫，me=讚揚者、ob=被讚揚者。書生（文壇）對應現有「文學造詣」
// 聲望軸 = score key "literary fame"（data/chinese.o：score of literary fame = 文學造詣，
// 與 martial/negative fame 同屬 fame 類；不臆造新軸）。
void
brother_praise (object me, object ob)
{
	int lvl;

	if (!objectp(me) || !objectp(ob)) return;
	lvl = ob->query_level();
	if (lvl < 2) lvl = 2;
	ob->gain_score("literary fame", lvl - 1);
	me->gain_score("literary fame", 1);
}

// vim: set ts=4 sw=4 syntax=lpc

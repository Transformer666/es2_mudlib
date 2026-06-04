inherit F_DBASE;

static void
create()
{
}

// 升級精氣神成長（docs 02/01）：每升一級，精(dex)/氣(con)/神(spi)依「屬性÷除數」隨機提升。
// 和尚：精6/氣6/神6（全 6 最均衡、整體成長最緩）。
void
advance_level (object me)
{
	if (!objectp(me)) return;
	me->advance_stat("gin", 1 + random(me->query_attr("dex") / 6));
	me->advance_stat("kee", 1 + random(me->query_attr("con") / 6));
	me->advance_stat("sen", 1 + random(me->query_attr("spi") / 6));
}

string
query_rank (object obj, string politness)
{
	if (!politness)
		return "和尚";

	switch (politness) {
		case "self":
			return "貧僧";
		case "respectful":
			return "大師";
		case "rude":
		default:
			return "禿驢";
	}
}

// brother_praise()（docs 02-04 L24-32,45-47 同職業互讚加職業聲望）：和尚由 cmds/usr/
// praise.c 呼叫，me=讚揚者、ob=被讚揚者。docs 未列和尚專屬聲望軸，依指示退用通用
// 「聲望」軸 = score key "reputation"（data/chinese.o：score of reputation = 聲望；不臆造新軸）。
void
brother_praise (object me, object ob)
{
	int lvl;

	if (!objectp(me) || !objectp(ob)) return;
	lvl = ob->query_level();
	if (lvl < 2) lvl = 2;
	ob->gain_score("reputation", lvl - 1);
	me->gain_score("reputation", 1);
}

// vim: set ts=4 sw=4 syntax=lpc

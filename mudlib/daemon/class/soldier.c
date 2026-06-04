inherit F_DBASE;

static void
create()
{
}

// 升級精氣神成長（docs 02/01）：每升一級，精(dex)/氣(con)/神(spi)依「屬性÷除數」隨機提升。
// 軍人：精3/氣3/神8（精氣均衡偏快、神最慢）。
void
advance_level (object me)
{
	if (!objectp(me)) return;
	me->advance_stat("gin", 1 + random(me->query_attr("dex") / 3));
	me->advance_stat("kee", 1 + random(me->query_attr("con") / 3));
	me->advance_stat("sen", 1 + random(me->query_attr("spi") / 8));
}

string
query_rank (object obj, string politness)
{
	if (!politness)
		return "軍人";

	switch (politness) {
		case "self":
			return "末將";
		case "respectful":
			return "將軍";
		case "rude":
		default:
			return "丘八";
	}
}

// brother_praise()（docs 02-04 L33「戰場功勳｜軍人」）：同職業互讚由 cmds/usr/praise.c
// 呼叫，me=讚揚者、ob=被讚揚者。軍人對應「戰場功勳」軸 = score key "military service"
// （data/chinese.o：score of military service = 戰場功勳）。
void
brother_praise (object me, object ob)
{
	int lvl;

	if (!objectp(me) || !objectp(ob)) return;
	lvl = ob->query_level();
	if (lvl < 2) lvl = 2;
	ob->gain_score("military service", lvl - 1);
	me->gain_score("military service", 1);
}

// vim: set ts=4 sw=4 syntax=lpc

inherit F_DBASE;

static void
create()
{
}

// 升級精氣神成長（docs 02/01）：每升一級，精(dex)/氣(con)/神(spi)依「屬性÷除數」隨機提升。
// 盜賊：精2/氣4/神8（精=機敏/2 最高，反映靈巧路線）。
void
advance_level (object me)
{
	if (!objectp(me)) return;
	me->advance_stat("gin", 1 + random(me->query_attr("dex") / 2));
	me->advance_stat("kee", 1 + random(me->query_attr("con") / 4));
	me->advance_stat("sen", 1 + random(me->query_attr("spi") / 8));
}

string
query_rank (object obj, string politness)
{
	if (!politness)
		return "小偷";

	switch (politness) {
		case "self":
			return "小的";
		case "respectful":
			return "好漢";
		case "rude":
		default:
			return "賊子";
	}
}

// brother_praise()（docs 02-04 L31,47「盜賊 praise → 黑道聲望」）：同職業互讚由
// cmds/usr/praise.c 呼叫，me=讚揚者、ob=被讚揚者。盜賊對應「黑道聲望」軸 = score key
// "negative fame"（data/chinese.o：score of negative fame = 黑道聲望）。
void
brother_praise (object me, object ob)
{
	int lvl;

	if (!objectp(me) || !objectp(ob)) return;
	lvl = ob->query_level();
	if (lvl < 2) lvl = 2;
	ob->gain_score("negative fame", lvl - 1);
	me->gain_score("negative fame", 1);
}

// vim: set ts=4 sw=4 syntax=lpc

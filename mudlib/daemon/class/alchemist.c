inherit F_DBASE;

static void
create()
{
}

// 升級精氣神成長（docs 02/01）：每升一級，精(dex)/氣(con)/神(spi)依「屬性÷除數」隨機提升。
// 方士：精4/氣4/神4（全均衡）。
void
advance_level (object me)
{
	if (!objectp(me)) return;
	me->advance_stat("gin", 1 + random(me->query_attr("dex") / 4));
	me->advance_stat("kee", 1 + random(me->query_attr("con") / 4));
	me->advance_stat("sen", 1 + random(me->query_attr("spi") / 4));
}

string
query_rank (object obj, string politness)
{
	if (!politness)
		return "方士";

	switch (politness) {
		case "self":
			return "在下";
		case "respectful":
			return "神醫";
		case "rude":
		default:
			return "江湖郎中";
	}
}

// vim: set ts=4 sw=4 syntax=lpc

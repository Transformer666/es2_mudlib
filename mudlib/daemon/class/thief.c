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

// vim: set ts=4 sw=4 syntax=lpc

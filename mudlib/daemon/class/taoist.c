inherit F_DBASE;

static void
create()
{
}

// 升級精氣神成長（docs 02/01「升級時的精氣神成長」）：每升一級，精(dex)/氣(con)/神(spi)
// 依「屬性÷職業除數」隨機提升。道士：精4/氣4/神3（神=靈性/3 偏高，重法力）。
void
advance_level (object me)
{
	if (!objectp(me)) return;
	me->advance_stat("gin", 1 + random(me->query_attr("dex") / 4));
	me->advance_stat("kee", 1 + random(me->query_attr("con") / 4));
	me->advance_stat("sen", 1 + random(me->query_attr("spi") / 3));
}

string
query_rank (object obj, string politness)
{
	if (!politness)
		return "道士";

	switch (politness) {
		case "self":
			return "貧道";
		case "respectful":
			return "道長";
		case "rude":
		default:
			return "牛鼻子";
	}
}

// vim: set ts=4 sw=4 syntax=lpc

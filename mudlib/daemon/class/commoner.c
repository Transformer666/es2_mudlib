inherit F_DBASE;

static void
create()
{
}

// 升級精氣神成長（docs 02/01）：每升一級，精(dex)/氣(con)/神(spi)依「屬性÷除數」隨機提升。
// 平民：docs 表未列，取均衡 5/5/5 為預設（入派前的過渡身分，成長略緩於各正式職業）。
void
advance_level (object me)
{
	if (!objectp(me)) return;
	me->advance_stat("gin", 1 + random(me->query_attr("dex") / 5));
	me->advance_stat("kee", 1 + random(me->query_attr("con") / 5));
	me->advance_stat("sen", 1 + random(me->query_attr("spi") / 5));
}

string
query_rank (object obj, string politness)
{
	if (!politness)
		return "平民";

	switch (politness) {
		case "self":
			return "我是";
		case "respectful":
			return "朋友";
		case "rude":
		default:
			return "傢伙";
	}
}


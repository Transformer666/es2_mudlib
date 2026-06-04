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

// brother_praise()（docs 02-04 L24-32,45-47）：平民無門派、無專業聲望軸（docs L34、
// 且 praise.c help 言「本身仍屬平民身份…聲望之提升效果較差」）。cmds/usr/praise.c:42 以
// pro!="commoner" 守衛，平民互讚不會走到這裡；此處留同簽名 no-op 以維持各 class daemon
// 介面一致、避免日後其他呼叫端誤觸 undefined function。不另給聲望（平民無職業聲望）。
void
brother_praise (object me, object ob)
{
	// 平民無職業聲望軸，刻意不給分；保留同簽名空實作。
}

// vim: set ts=4 sw=4 syntax=lpc


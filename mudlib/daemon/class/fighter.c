inherit F_DBASE;

static void
create()
{
}

// 升級精氣神成長（docs 02-遊戲系統與機制/01「升級時的精氣神成長」；由 score.c gain_score
// 升級時 CLASS_D->advance_level 呼叫）：每升一級，精(gin←機敏dex)/氣(kee←根骨con)/神(sen←
// 靈性spi) 依「對應屬性÷職業除數」隨機提升(1 + random(屬性/除數))。屬性鍵：機敏=dex、根骨=
// con、靈性=spi（見 std/race/humanoid.c 三圍 floor 對應）。武者：精4/氣2/神8——氣=根骨/2 最
// 高，反映武者依內力作戰。
void
advance_level (object me)
{
	if (!objectp(me)) return;
	me->advance_stat("gin", 1 + random(me->query_attr("dex") / 4));
	me->advance_stat("kee", 1 + random(me->query_attr("con") / 2));
	me->advance_stat("sen", 1 + random(me->query_attr("spi") / 8));
}

string
query_rank (object obj, string politness)
{
	if (!politness)
		return "武者";

	switch (politness) {
		case "self":
			return "在下";
		case "respectful":
			return "英雄";
		case "rude":
		default:
			return "傢伙";
	}
}

// brother_praise()（docs 02-04 業力與聲望 L24-32,45-47「武者 praise → 武林聲望」）：
// 由 cmds/usr/praise.c 在「同職業互讚」時呼叫，me=讚揚者、ob=被讚揚者。
// 武者對應「武林聲望」軸 = score key "martial fame"（見 data/chinese.o：
// score of martial fame = 武林聲望）。在 praise.c 已給的 reputation 之外，
// 額外給被讚者武林聲望、讚者亦得少許，作為同門互讚之專業獎勵。
void
brother_praise (object me, object ob)
{
	int lvl;

	if (!objectp(me) || !objectp(ob)) return;
	lvl = ob->query_level();
	if (lvl < 2) lvl = 2;
	ob->gain_score("martial fame", lvl - 1);
	me->gain_score("martial fame", 1);
}

// vim: set ts=4 sw=4 syntax=lpc


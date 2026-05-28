inherit F_DBASE;

static void
create()
{
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

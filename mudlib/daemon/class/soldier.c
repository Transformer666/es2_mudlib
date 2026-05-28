inherit F_DBASE;

static void
create()
{
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

// vim: set ts=4 sw=4 syntax=lpc

inherit F_DBASE;

static void
create()
{
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

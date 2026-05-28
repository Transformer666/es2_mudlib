inherit F_DBASE;

static void
create()
{
}

string
query_rank (object obj, string politness)
{
	if (!politness)
		return "書生";

	switch (politness) {
		case "self":
			return "在下";
		case "respectful":
			return "相公";
		case "rude":
		default:
			return "酸丁";
	}
}

// vim: set ts=4 sw=4 syntax=lpc

inherit F_DBASE;

static void
create()
{
}

string
query_rank (object obj, string politness)
{
	if (!politness)
		return "和尚";

	switch (politness) {
		case "self":
			return "貧僧";
		case "respectful":
			return "大師";
		case "rude":
		default:
			return "禿驢";
	}
}

// vim: set ts=4 sw=4 syntax=lpc

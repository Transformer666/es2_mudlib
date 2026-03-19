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
            return "禪師";
        case "rude":
        default:
            return "禿驢";
    }
}

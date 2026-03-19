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
            return "將領";
        case "rude":
        default:
            return "傢伙";
    }
}

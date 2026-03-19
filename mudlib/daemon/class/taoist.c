inherit F_DBASE;

static void
create()
{
}

string
query_rank (object obj, string politness)
{
    if (!politness)
        return "道士";

    switch (politness) {
        case "self":
            return "貧道";
        case "respectful":
            return "真人";
        case "rude":
        default:
            return "妖道";
    }
}

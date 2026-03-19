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
            return "小人";
        case "respectful":
            return "藥師";
        case "rude":
        default:
            return "傢伙";
    }
}

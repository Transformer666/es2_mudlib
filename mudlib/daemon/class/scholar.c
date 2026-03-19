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
            return "小生";
        case "respectful":
            return "隱士";
        case "rude":
        default:
            return "書呆子";
    }
}

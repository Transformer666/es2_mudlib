inherit F_DBASE;

static void
create()
{
}

string
query_rank (object obj, string politness)
{
    if (!politness)
        return "盜賊";

    switch (politness) {
        case "self":
            return "在下";
        case "respectful":
            return "遊俠";
        case "rude":
        default:
            return "毛賊";
    }
}

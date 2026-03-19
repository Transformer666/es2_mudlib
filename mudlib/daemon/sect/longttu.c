// vim: syntax=lpc

inherit F_DBASE;

private void
create()
{
    seteuid(getuid());

    set("name", "龍圖");
    set("english_name", "longttu");
    set("class", "alchemist");
    set("paths", ([
        "醫師": "Physician - master of healing and medicine",
    ]));
    set("skills", ({
        "longttu neigong",
        "needle",
    }));
    set("location", "/d/longttu/study");

    DAEMON_D->register_object_daemon("sect:longttu");
}

string query_sect_name() { return query("name"); }
string query_class() { return query("class"); }
mapping query_paths() { return query("paths"); }

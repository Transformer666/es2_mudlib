// vim: syntax=lpc

inherit F_DBASE;

private void
create()
{
    seteuid(getuid());

    set("name", "白象寺");
    set("english_name", "baixiang");
    set("class", "monk");
    set("paths", ([
        "禪師": "Chan Master - enlightened meditation master",
        "羅漢": "Arhat - ascended warrior monk",
    ]));
    set("skills", ({
        "diamond hammer",
        "staff",
    }));
    set("location", "/d/baixiang/gate");

    DAEMON_D->register_object_daemon("sect:baixiang");
}

string query_sect_name() { return query("name"); }
string query_class() { return query("class"); }
mapping query_paths() { return query("paths"); }

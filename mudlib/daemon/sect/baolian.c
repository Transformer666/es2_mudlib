// vim: syntax=lpc

inherit F_DBASE;

private void
create()
{
    seteuid(getuid());

    set("name", "寶蓮寺");
    set("english_name", "baolian");
    set("class", "monk");
    set("paths", ([
        "比丘": "Monk - devoted practitioner of the dharma",
        "治癒僧": "Healer Monk - master of restorative arts",
    ]));
    set("skills", ({
        "staff",
    }));
    set("location", "/d/wutang/temple");

    DAEMON_D->register_object_daemon("sect:baolian");
}

string query_sect_name() { return query("name"); }
string query_class() { return query("class"); }
mapping query_paths() { return query("paths"); }

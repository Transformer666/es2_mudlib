// vim: syntax=lpc

inherit F_DBASE;

private void
create()
{
    seteuid(getuid());

    set("name", "天月庵");
    set("english_name", "tianyue");
    set("class", "monk");
    set("paths", ([
        "比丘尼": "Nun - devoted practitioner of the dharma",
        "治癒尼": "Healer Nun - master of restorative arts",
    ]));
    set("skills", ({
        "staff",
    }));
    set("location", "/d/tianyue/hall");

    DAEMON_D->register_object_daemon("sect:tianyue");
}

string query_sect_name() { return query("name"); }
string query_class() { return query("class"); }
mapping query_paths() { return query("paths"); }

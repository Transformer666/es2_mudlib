// vim: syntax=lpc

inherit F_DBASE;

private void
create()
{
    seteuid(getuid());

    set("name", "步玄派");
    set("english_name", "buxuan");
    set("class", "scholar");
    set("paths", ([
        "居士": "Hermit - reclusive scholarly master",
        "密探": "Spy - intelligence gatherer",
    ]));
    set("skills", ({
        "three rotations",
    }));
    set("location", "/d/wutang/court");

    DAEMON_D->register_object_daemon("sect:buxuan");
}

string query_sect_name() { return query("name"); }
string query_class() { return query("class"); }
mapping query_paths() { return query("paths"); }

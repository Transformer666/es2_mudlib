// vim: syntax=lpc

inherit F_DBASE;

private void
create()
{
    seteuid(getuid());

    set("name", "玄天教");
    set("english_name", "xuantian");
    set("class", "scholar");
    set("paths", ([
        "散人": "Wanderer - free-roaming scholar",
        "密探": "Spy - covert operative",
    ]));
    set("skills", ({
        "sword",
    }));
    set("location", "/d/wutang/temple");

    DAEMON_D->register_object_daemon("sect:xuantian");
}

string query_sect_name() { return query("name"); }
string query_class() { return query("class"); }
mapping query_paths() { return query("paths"); }

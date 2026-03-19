// vim: syntax=lpc

inherit F_DBASE;

private void
create()
{
    seteuid(getuid());

    set("name", "天邪派");
    set("english_name", "tianxie");
    set("class", "warrior");
    set("paths", ([
        "天邪弟子": "Tianxie Disciple - follower of the dark arts",
        "暗殺者": "Assassin - silent killer from the shadows",
    ]));
    set("skills", ({
        "phantom sword",
    }));
    set("location", "/d/tianxie/hall");

    DAEMON_D->register_object_daemon("sect:tianxie");
}

string query_sect_name() { return query("name"); }
string query_class() { return query("class"); }
mapping query_paths() { return query("paths"); }

// vim: syntax=lpc

inherit F_DBASE;

private void
create()
{
    seteuid(getuid());

    set("name", "哭笑門");
    set("english_name", "kuxiao");
    set("class", "warrior");
    set("paths", ([
        "護法": "Guardian - protector of the sect",
        "素衣衛": "Plain Guard - unassuming but deadly",
        "使者": "Messenger - swift envoy of the sect",
    ]));
    set("skills", ({
        "sword",
    }));
    set("location", "/d/kuxiao/hall");

    DAEMON_D->register_object_daemon("sect:kuxiao");
}

string query_sect_name() { return query("name"); }
string query_class() { return query("class"); }
mapping query_paths() { return query("paths"); }

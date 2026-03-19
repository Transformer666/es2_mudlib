// vim: syntax=lpc

inherit F_DBASE;

private void
create()
{
    seteuid(getuid());

    set("name", "雪吟莊");
    set("english_name", "xueyin");
    set("class", "warrior");
    set("paths", ([
        "浪人": "Drifter - wandering swordsman",
        "棄徒": "Abandoned - cast out but resilient",
        "天邪派弟子": "Tianxie Disciple - follower of the dark path",
    ]));
    set("skills", ({
        "sword",
    }));
    set("location", "/d/snow/ebridge");

    DAEMON_D->register_object_daemon("sect:xueyin");
}

string query_sect_name() { return query("name"); }
string query_class() { return query("class"); }
mapping query_paths() { return query("paths"); }

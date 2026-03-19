// vim: syntax=lpc

inherit F_DBASE;

private void
create()
{
    seteuid(getuid());

    set("name", "振武軍營");
    set("english_name", "zhenwu");
    set("class", "soldier");
    set("paths", ([
        "暴將": "Violent Commander - ruthless battlefield leader",
        "軍師": "Military Strategist - master of tactics and war",
    ]));
    set("skills", ({
        "tactic",
        "pike",
    }));
    set("location", "/d/zhenwu/gate");

    DAEMON_D->register_object_daemon("sect:zhenwu");
}

string query_sect_name() { return query("name"); }
string query_class() { return query("class"); }
mapping query_paths() { return query("paths"); }

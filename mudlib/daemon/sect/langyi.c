// vim: syntax=lpc

inherit F_DBASE;

private void
create()
{
    seteuid(getuid());

    set("name", "瑯夷");
    set("english_name", "langyi");
    set("class", "thief");
    set("paths", ([
        "金蛇門弟子": "Golden Snake - venomous and cunning",
        "暗探": "Spy - master of espionage",
    ]));
    set("skills", ({
        "dagger",
    }));
    set("location", "/d/wutang/lane2");

    DAEMON_D->register_object_daemon("sect:langyi");
}

string query_sect_name() { return query("name"); }
string query_class() { return query("class"); }
mapping query_paths() { return query("paths"); }

// vim: syntax=lpc

inherit F_DBASE;

private void
create()
{
    seteuid(getuid());

    set("name", "封山派");
    set("english_name", "fengshan");
    set("class", "warrior");
    set("paths", ([
        "劍靈": "Sword Spirit - master of sword arts",
        "山人": "Mountain Man - tough defensive fighter",
        "劍客": "Swordmaster - balanced swordsman",
    ]));
    set("skills", ({
        "fengshan sword",
    }));
    set("location", "/d/fengshan/gate");

    DAEMON_D->register_object_daemon("sect:fengshan");
}

string query_sect_name() { return query("name"); }
string query_class() { return query("class"); }
mapping query_paths() { return query("paths"); }

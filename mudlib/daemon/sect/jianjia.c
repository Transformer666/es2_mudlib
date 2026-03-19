// vim: syntax=lpc

inherit F_DBASE;

private void
create()
{
    seteuid(getuid());

    set("name", "劍甲門");
    set("english_name", "jianjia");
    set("class", "alchemist");
    set("paths", ([
        "劍甲士": "Sword Armor Knight - blends blade with alchemy",
    ]));
    set("skills", ({
        "sword",
        "needle",
    }));
    set("location", "/d/jianjia/hall");

    DAEMON_D->register_object_daemon("sect:jianjia");
}

string query_sect_name() { return query("name"); }
string query_class() { return query("class"); }
mapping query_paths() { return query("paths"); }

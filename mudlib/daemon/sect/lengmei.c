// vim: syntax=lpc

inherit F_DBASE;

private void
create()
{
    seteuid(getuid());

    set("name", "冷梅莊");
    set("english_name", "lengmei");
    set("class", "warrior");
    set("paths", ([
        "劍士": "Swordsman - skilled blade wielder",
        "古劍門傳人": "Ancient Sword Heir - inheritor of ancient techniques",
        "虎督": "Tiger Commander - fierce battlefield leader",
    ]));
    set("skills", ({
        "lengmei sword",
    }));
    set("location", "/d/snow/egate");

    DAEMON_D->register_object_daemon("sect:lengmei");
}

string query_sect_name() { return query("name"); }
string query_class() { return query("class"); }
mapping query_paths() { return query("paths"); }

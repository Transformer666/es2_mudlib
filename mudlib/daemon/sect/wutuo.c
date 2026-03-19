// vim: syntax=lpc

inherit F_DBASE;

private void
create()
{
    seteuid(getuid());

    set("name", "武陀");
    set("english_name", "wutuo");
    set("class", "alchemist");
    set("paths", ([
        "香主": "Incense Master - keeper of herbal secrets",
    ]));
    set("skills", ({
        "five defeat needle",
        "amazing needle",
    }));
    set("location", "/d/wutuo/hall");

    DAEMON_D->register_object_daemon("sect:wutuo");
}

string query_sect_name() { return query("name"); }
string query_class() { return query("class"); }
mapping query_paths() { return query("paths"); }

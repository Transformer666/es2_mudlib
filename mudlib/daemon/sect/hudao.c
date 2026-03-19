// vim: syntax=lpc

inherit F_DBASE;

private void
create()
{
    seteuid(getuid());

    set("name", "虎刀門");
    set("english_name", "hudao");
    set("class", "warrior");
    set("paths", ([
        "護衛": "Guard - loyal protector",
        "鬼才": "Dual Blade Genius - ambidextrous blade master",
        "太守": "Warlord - supreme martial commander",
    ]));
    set("skills", ({
        "tiger blade",
    }));
    set("location", "/d/hudao/gate");

    DAEMON_D->register_object_daemon("sect:hudao");
}

string query_sect_name() { return query("name"); }
string query_class() { return query("class"); }
mapping query_paths() { return query("paths"); }

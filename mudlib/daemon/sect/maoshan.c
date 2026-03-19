// vim: syntax=lpc

inherit F_DBASE;

private void
create()
{
    seteuid(getuid());

    set("name", "茅山派");
    set("english_name", "maoshan");
    set("class", "taoist");
    set("paths", ([
        "靈雲觀弟子": "Lingyun - disciple of the Spirit Cloud temple",
        "隱風觀弟子": "Yinfeng - disciple of the Hidden Wind temple",
        "幻霧觀弟子": "Huanwu - disciple of the Phantom Mist temple",
        "茅山劍士": "Maoshan Swordsman - blade-wielding taoist",
    ]));
    set("skills", ({
        "maoshan sword",
        "maoshan neigong",
        "taoshan milu",
    }));
    set("location", "/d/maoshan/gate");

    DAEMON_D->register_object_daemon("sect:maoshan");
}

string query_sect_name() { return query("name"); }
string query_class() { return query("class"); }
mapping query_paths() { return query("paths"); }

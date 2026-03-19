// vim: syntax=lpc

inherit F_DBASE;

private void
create()
{
    seteuid(getuid());

    set("name", "天師派");
    set("english_name", "tianshi");
    set("class", "taoist");
    set("paths", ([
        "朱衣": "Fire Acolyte - wielder of flame arts",
        "玄衣": "Wind Acolyte - master of wind techniques",
        "素衣": "Ice Acolyte - controller of frost",
        "紫衣": "Thunder Acolyte - channeler of lightning",
    ]));
    set("skills", ({
        "taiyi sword",
        "ziwei neigong",
    }));
    set("location", "/d/wutang/wushan_path3");

    DAEMON_D->register_object_daemon("sect:tianshi");
}

string query_sect_name() { return query("name"); }
string query_class() { return query("class"); }
mapping query_paths() { return query("paths"); }

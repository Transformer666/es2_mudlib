// vim: syntax=lpc

inherit F_DBASE;

private void
create()
{
    seteuid(getuid());

    set("name", "隱教");
    set("english_name", "yinjiao");
    set("class", "thief");
    set("paths", ([
        "黑龍使者": "Black Dragon Messenger - elite dark operative",
        "暗衛": "Shadow Guard - silent protector from the shadows",
    ]));
    set("skills", ({
        "dagger",
    }));
    set("location", "/d/wutang/wushan_cave");

    DAEMON_D->register_object_daemon("sect:yinjiao");
}

string query_sect_name() { return query("name"); }
string query_class() { return query("class"); }
mapping query_paths() { return query("paths"); }

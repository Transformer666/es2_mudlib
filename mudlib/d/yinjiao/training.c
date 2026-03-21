inherit ROOM;

void create()
{
    set("short", "練爪堂");
    set("long", @LONG
練爪堂中擺放著各種練功器械﹐牆上掛著幾副鷹爪形的金屬手套。
地面上刻著各種步法的軌跡﹐幾名弟子正在苦練鷹爪功﹐手指如鋼鉤
般抓向木樁。
LONG
    );
    set("exits", ([
        "west" : __DIR__"hall",
    ]));

    set("objects", ([
        __DIR__"npc/disciple" : 2,
    ]));

    setup();
    replace_program(ROOM);
}

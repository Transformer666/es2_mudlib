inherit ROOM;

void create()
{
    set("short", "密道");
    set("long", @LONG
從武山洞窟石壁後的暗門進入﹐一條幽深的密道向北延伸。密道狹
窄陰暗﹐兩壁潮濕﹐腳下的石板路高低不平。隱約可以聽到遠處傳來
的水滴聲。
LONG
    );
    set("exits", ([
        "south" : "/d/wutang/wushan_cave",
        "north" : __DIR__"gate",
    ]));

    setup();
    replace_program(ROOM);
}

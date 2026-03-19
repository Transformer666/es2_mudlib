inherit ROOM;

void create()
{
    set("short", "寶蓮寺山門");
    set("long", @LONG
寶蓮寺山門莊嚴肅穆﹐門楣上懸掛著一塊金色的匾額﹐上書「寶蓮
禪寺」四個大字。門前立著兩尊石刻的金剛力士﹐面目威嚴。門內傳來
悠揚的鐘聲和誦經聲。
LONG
    );
    set("exits", ([
        "south" : __DIR__"mountain_path",
        "north" : __DIR__"courtyard",
    ]));

    setup();
    replace_program(ROOM);
}

inherit ROOM;

void create()
{
    set("short", "藥庫");
    set("long", @LONG
藥庫中整齊地陳列著大量的藥材﹐分門別類地放在不同的架子上。空
氣中瀰漫著各種草藥混合的氣味。一些珍貴的藥材被放在上了鎖的木箱
中﹐看守得十分嚴密。
LONG
    );
    set("exits", ([
        "south" : __DIR__"garden",
    ]));

    setup();
    replace_program(ROOM);
}

// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "馬廄");
    set("long", @LONG
一座寬敞的馬廄，木欄杆隔出了十幾個馬位，裡面養著幾匹膘肥體
壯的戰馬。馬廄裡瀰漫著乾草和馬糞的氣味，地上鋪著厚厚的稻草。
一名馬夫正在給一匹棗紅色的戰馬刷洗毛皮，那馬兒不時甩甩尾巴，
似乎十分享受。牆角堆放著馬鞍、韁繩和其他馬具。
LONG
    );
    set("exits", ([
        "west" : __DIR__"barracks",
    ]));

    set("objects", ([ __DIR__"npc/stablehand" : 1 ]));

    setup();
    replace_program(ROOM);
}

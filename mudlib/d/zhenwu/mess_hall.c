// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "伙房");
    set("long", @LONG
練武場北面的軍營伙房，幾口大鐵鍋架在土灶上，鍋裡煮著粗糧
和燉肉，熱氣騰騰。牆角堆放著一袋袋的糧食和乾菜，幾串風乾的鹹
肉掛在橫樑上。吃飯的時辰一到，士兵們便排著隊領取飯食，軍營裡的
伙食雖然談不上精緻，但勝在量大實惠，足以讓操練了一整天的士兵們
填飽肚子。
LONG
    );
    set("exits", ([
        "south" : __DIR__"training",
    ]));
    set("objects", ([
        __DIR__"npc/cook" : 1,
    ]));

    setup();
}

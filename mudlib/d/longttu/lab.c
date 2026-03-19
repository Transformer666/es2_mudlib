inherit ROOM;

void create()
{
    set("short", "煉丹室");
    set("long", @LONG
煉丹室中央擺放著一座青銅煉丹爐﹐爐火正旺﹐一股奇異的藥香從
爐中飄出。四壁的架子上擺滿了各種瓶瓶罐罐﹐都是煉丹所需的材料
。一本翻開的丹方擱在桌上。
LONG
    );
    set("exits", ([
        "west"  : __DIR__"garden",
        "north" : __DIR__"study",
    ]));

    setup();
    replace_program(ROOM);
}

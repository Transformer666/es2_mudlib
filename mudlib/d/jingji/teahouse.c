// Room: /d/jingji/teahouse.c

inherit ROOM;

void create()
{
    set("short", "茶肆");
    set("long", @LONG
京畿一間雅致的茶肆﹐店內擺設著紫檀木桌椅﹐桌上擺著精美的青花
瓷茶具﹐茶香嫋嫋﹐沁人心脾。幾位身著錦袍的文士圍坐一桌﹐手持
書卷高談闊論﹐時而引經據典﹐時而撫掌大笑﹐好不風雅。
LONG
    );
    set("exits", ([
        "east" : __DIR__"library",
    ]));
    set("no_fight", 1);

    setup();
    replace_program(ROOM);
}

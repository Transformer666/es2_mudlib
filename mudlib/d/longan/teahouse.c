// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "茶館");
    set("long", @LONG
一間雅致的茶館，門口掛著一面寫有「龍井茶莊」的木牌。館內
擺設著幾張紅木茶桌，桌上放著精緻的紫砂壺和青花茶杯。幾位茶客
悠閒地品著香茗，低聲交談。角落裡一位說書先生正繪聲繪色地講述著
江湖故事，引得聽眾不時發出陣陣驚嘆。空氣中瀰漫著茉莉花茶的清
香，令人心曠神怡。
LONG
    );
    set("exits", ([
        "east" : __DIR__"street",
        "north" : __DIR__"back_street",
    ]));
    set("no_fight", 1);

    set("objects", ([ __DIR__"npc/tea_vendor" : 1 ]));

    setup();
}

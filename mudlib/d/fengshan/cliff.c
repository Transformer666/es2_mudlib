// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "斷崖");
    set("long", @LONG
劍道場東面的懸崖邊緣，腳下便是萬丈深淵，雲霧在崖壁間翻湧
不息。這裡是封山派最險峻的所在，只有技藝高超的弟子才敢在此練劍。
崖壁上有歷代高手以劍氣刻下的字跡，有的龍飛鳳舞，有的筆力萬鈞，
每一筆每一劃都蘊含著精深的劍意。山風在崖間呼嘯，如同萬劍齊鳴。
LONG
    );
    set("outdoors", "mountain");
    set("exits", ([
        "west" : __DIR__"sword_arena",
    ]));

    setup();
    replace_program(ROOM);
}

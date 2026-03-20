// Room: /d/babao/hall.c

inherit ROOM;

void create()
{
    set("short", "將軍府大堂");
    set("long", @LONG
將軍府的大堂寬敞氣派，正中央掛著一幅巨大的山水畫，兩側陳列
著各種兵器和盔甲，在燭光下閃著寒芒。大堂北面有一座高聳的樓閣，
那就是名震江湖的「八寶樓」。據說這座樓閣共有八層，每一層都盤踞
著一位武林高手，號稱「大漠八魔」。
LONG
    );
    set("detail", ([
        "兵器" : "牆上掛著各式各樣的兵器，都是精鋼打造，寒光凜凜。\n",
        "山水畫" : "一幅氣勢磅礴的山水畫，落款已經模糊不清。\n",
    ]));
    set("exits", ([
        "south" : __DIR__"entrance",
        "up" : __DIR__"floor1",
    ]));

    setup();
    replace_program(ROOM);
}

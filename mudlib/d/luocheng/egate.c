// Room: /d/luocheng/egate.c

inherit ROOM;

void create()
{
    set("short", "羅城東門");
    set("long", @LONG
這裡是羅城的東門﹐比西門更加高大雄偉﹐城門上方的箭樓巍然
聳立。東門外是一望無際的蘆葦蕩和水澤﹐據說那片蘆葦叢中常有
盜匪出沒﹐因此東門的守衛比西門嚴格得多。進出城門的商隊都要接
受仔細的盤查﹐以防奸細混入。
LONG
    );
    set("outdoors", "town");
    set("objects", ([
        __DIR__"npc/guard" : 2,
    ]));
    set("detail", ([
        "箭樓" : "箭樓上可以看到幾個弓手的身影﹐正在警惕地注視著城外的動靜。\n",
        "城門" : "城門厚重結實﹐門板上包著一層鐵皮﹐上面佈滿了歲月的鏽痕。\n",
    ]));
    set("exits", ([
        "west" : __DIR__"street2",
    ]));

    setup();
    replace_program(ROOM);
}

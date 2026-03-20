// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "天月庵山門");
    set("long", @LONG
天月庵的山門素雅端莊﹐門楣上懸掛著一塊木匾﹐上書「天月庵」
三個端正的楷書大字﹐墨色雖已有些褪淡﹐卻更顯古樸。門前兩側各
立著一尊白玉觀音像﹐慈眉善目﹐手持淨瓶和楊柳枝。門內飄來一陣
淡淡的檀香﹐令人心神寧靜。
LONG
    );
    set("detail", ([
        "木匾" : "一塊古樸的木匾﹐上面的字跡蒼勁有力﹐雖經風雨侵蝕仍然清晰可辨。\n",
        "觀音像" : "白玉雕成的觀音像﹐高約五尺﹐雕工精細﹐面容慈悲安詳。\n",
    ]));
    set("exits", ([
        "south" : __DIR__"mountain_path",
        "north" : __DIR__"courtyard",
    ]));

    setup();
    replace_program(ROOM);
}

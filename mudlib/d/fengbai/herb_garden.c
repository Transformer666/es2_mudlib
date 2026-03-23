// Room: /d/fengbai/herb_garden.c

inherit ROOM;

void create()
{
    set("short", "藥草園");
    set("long", @LONG
村子西南角有一片小小的藥草園﹐用竹籬笆圍了起來。園中種著
各種常見的藥草﹐有金銀花、黃芪、當歸、甘草等等﹐一股淡淡的
藥香瀰漫在空氣中。園子的主人顯然很用心﹐每一畦藥草都打理得
井井有條﹐旁邊還放著澆水的木桶和鋤頭。
LONG
    );
    set("outdoors", "village");
    set("detail", ([
        "金銀花" : "一叢金銀花正開得燦爛﹐黃白相間的花朵散發著清香。\n",
        "竹籬笆" : "用竹子編成的籬笆﹐雖然簡陋但紮得很結實。\n",
    ]));
    set("exits", ([
        "east" : __DIR__"street2",
    ]));

    setup();
    replace_program(ROOM);
}

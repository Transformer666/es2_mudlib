// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "庵前庭院");
    set("long", @LONG
庵前的庭院打理得十分整潔﹐青石地面纖塵不染。庭中種著幾株
桂花樹﹐枝繁葉茂。東邊有一座小小的放生池﹐池中養著幾尾錦鯉﹐
池旁立著一塊刻有「慈悲為懷」四字的石碑。幾名尼姑正在庭中打掃
落葉﹐一舉一動都顯得從容不迫。
LONG
    );
    set("detail", ([
        "桂花樹" : "幾株枝幹遒勁的桂花樹﹐雖然不在花期﹐但碧綠的葉子散發著淡淡的清香。\n",
        "放生池" : "一座用青石砌成的小水池﹐池水清澈﹐幾尾錦鯉在水中悠閒地游來游去。\n",
        "石碑" : "一塊磨光的青石碑﹐上面刻著「慈悲為懷」四個字﹐字體圓潤飽滿。\n",
    ]));
    set("objects", ([
        __DIR__"npc/greeter" : 1,
    ]));
    set("exits", ([
        "south" : __DIR__"gate",
        "north" : __DIR__"hall",
    ]));

    setup();
    replace_program(ROOM);
}

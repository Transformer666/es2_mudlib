// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "陰間入口");
    set("long", @LONG
一股陰冷刺骨的寒氣迎面撲來﹐眼前是一片昏暗的空間﹐四周瀰
漫著灰濛濛的霧氣。腳下的地面由黑色的石板鋪成﹐石板上刻滿了奇
異的符文﹐隱隱散發著暗淡的紅光。頭頂上方是一片虛無的黑暗﹐看
不到天空﹐也感受不到風。遠處隱約可以看到一條蜿蜒的石路通往更
深處。這裡便是傳說中的陰間了。往上方的裂縫可以回到人間。
LONG
    );
    set("detail", ([
        "符文" : "石板上刻著的符文古老而神秘﹐似乎是某種封印法陣﹐散發著微弱的光芒。\n",
        "霧氣" : "灰濛濛的霧氣在腳邊盤旋﹐冰冷刺骨﹐觸碰之處彷彿能聽到微弱的哀嚎聲。\n",
    ]));
    set("objects", ([
        __DIR__"npc/black_agent" : 1,
        __DIR__"npc/white_agent" : 1,
    ]));
    set("exits", ([
        "up"    : "/d/graveyard/shrine",
        "north" : __DIR__"path",
        "east"  : "/d/death/entrance",
    ]));

    setup();
    // 不使用 replace_program — 有自訂 receive_object
}

// 只有鬼魂能進入陰間
int receive_object(object ob, int from_inventory)
{
    if( ob->is_character() && ob->query("life_form") != "ghost" ) {
        tell_object(ob, "一股無形的力量將你彈了回去﹐活人不得進入陰間。\n");
        return 0;
    }
    return 1;
}

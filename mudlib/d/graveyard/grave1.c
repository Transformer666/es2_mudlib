// Room: /d/graveyard/grave1.c
// Quest: 荒塚祭文 (stele_prayer)
// Flow: grave_keeper mentions tombstone -> examine 墓碑 here -> pray -> reward

inherit ROOM;

void create()
{
    set("short", "荒塚");
    set("long", @LONG
雪亭鎮西北方的一片荒涼之地﹐遍地是雜草叢生的墳塚。大大小小
的墳包散落在枯黃的野草之間﹐有些墓碑已經歪斜倒塌﹐字跡模糊不清。
一股陰森森的寒氣從地底湧上來﹐即使是大白天也讓人渾身發冷。偶爾
能看到幾隻烏鴉停在枯樹上﹐不祥地嘎嘎叫著。
在一堆歪斜的墳塚之中﹐有一塊石碑(墓碑)的字跡比其他的清晰得
多﹐似乎被人經常擦拭。
LONG
    );
    set("outdoors", "wasteland");
    set("detail", ([
        "墓碑" : "這塊墓碑比周圍的墳塚要整齊許多﹐碑面上的字跡清晰可辨。\n"
            "碑文寫著：「趙子清之墓」﹐下方刻著幾行小字﹐但被苔蘚覆蓋﹐\n"
            "需要仔細辨認(examine 墓碑)才能讀出來。\n",
        "烏鴉" : "幾隻黑色的烏鴉蹲在枯樹上﹐偶爾發出不祥的叫聲。\n",
    ]));
    set("exits", ([
        "south" : __DIR__"entrance",
        "north" : __DIR__"grave2",
    ]));

    setup();
}

void init()
{
    add_action("do_examine", "examine");
    add_action("do_pray", "pray");
    add_action("do_pray", "worship");
}

int do_examine(string arg)
{
    object me;

    me = this_player();

    if( !arg || (strsrch(arg, "墓碑") < 0 && strsrch(arg, "碑") < 0
    &&  strsrch(arg, "stele") < 0 && strsrch(arg, "tombstone") < 0) )
        return 0;

    if( me->query("quest/stele_prayer_done") ) {
        write(
            "墓碑上的字跡依舊清晰：「趙子清之墓」。碑前似乎還殘留\n"
            "著你祭拜時的痕跡﹐空氣中的陰森感已經消散了不少。\n");
        return 1;
    }

    write(
        "你蹲下身來﹐小心翼翼地撥開墓碑上的苔蘚﹐辨認著碑文。\n"
        "\n"
        "碑文寫道：\n"
        "    「趙子清﹐雪亭鎮人﹐性好讀書﹐才學出眾。因得罪權貴﹐\n"
        "    被誣以盜竊之罪﹐含冤而死﹐年僅二十有三。其母思兒成疾﹐\n"
        "    不久亦亡。鄰里不忍﹐立此碑以記。」\n"
        "\n"
        "碑文下方還刻著一行小字﹕\n"
        "    「願有善心人為吾兒祭拜(pray)﹐使其魂魄安息。」\n");
    message("vision",
        "$N蹲在一塊墓碑前﹐仔細辨認著碑文。\n",
        environment(me), ({me}));

    me->set_temp("pending/stele_prayer", 1);
    return 1;
}

int do_pray(string arg)
{
    object me;

    me = this_player();

    if( arg && strsrch(arg, "墓碑") < 0 && strsrch(arg, "碑") < 0
    &&  strsrch(arg, "趙") < 0 && strsrch(arg, "grave") < 0 )
        return 0;

    if( me->query("quest/stele_prayer_done") ) {
        write("你在墓碑前默默合掌。微風拂過﹐似乎能感受到一絲溫暖的回應。\n");
        return 1;
    }

    if( !me->query_temp("pending/stele_prayer") ) {
        write("你在荒塚中合掌祈禱﹐但不知道該對誰祈禱。\n"
            "也許應該先看看那塊字跡清晰的墓碑。\n");
        return 1;
    }

    write(
        "你在趙子清的墓碑前虔誠地合掌﹐低聲念了幾句祝禱的話。\n"
        "\n"
        "忽然﹐一陣清風從墓碑後面吹來﹐帶著一股淡淡的花香。你隱約\n"
        "看到一個白衣書生的模糊身影在墓碑旁浮現﹐他面容清秀﹐目光\n"
        "溫和﹐朝你微微頷首致意。\n"
        "\n"
        "書生的聲音如風中的低語﹕「多謝你 ... 終於有人來了 ...」\n"
        "\n"
        "他的身影漸漸變淡﹐在消散之前﹐一枚晶瑩的玉符從光芒中緩緩\n"
        "飄落到你的掌心。空氣中的陰寒之氣消散了許多﹐這片墳塚似乎\n"
        "也變得安寧了一些。\n");
    message("vision",
        "$N在一塊墓碑前虔誠地合掌祭拜。\n"
        "一陣清風吹過﹐隱約有一道白色的光影在墓碑旁浮現﹐隨即消散。\n",
        environment(me), ({me}));

    me->set("quest/stele_prayer_done", 1);
    me->delete_temp("pending/stele_prayer");
    me->gain_score("quest", 80);

    clone_object(__DIR__"npc/obj/jade_amulet")->move(me);
    tell_object(me, "( 你獲得了一枚護身玉符 )\n");

    return 1;
}

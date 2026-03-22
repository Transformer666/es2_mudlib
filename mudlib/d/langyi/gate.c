inherit ROOM;

void create()
{
    set("short", "狼義門暗門");
    set("long", @LONG
一扇隱蔽在岩壁裂縫中的暗門﹐若非知情人指引﹐絕難發現。門框
以粗鐵鑄就﹐上面刻著一個模糊的狼頭圖案。推開暗門﹐一股陰冷的
氣息撲面而來﹐裡面是一條深不見底的地道。門外是一條荒僻的野道﹐
雜草叢生﹐少有人跡。
LONG
    );
    set("exits", ([
        "north"     : __DIR__"tunnel",
        "southeast" : "/d/road/wild_path2",
    ]));

    setup();
    replace_program(ROOM);
}

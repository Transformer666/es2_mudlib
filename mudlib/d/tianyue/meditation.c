// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "靜修室");
    set("long", @LONG
一間佈置簡樸的靜修室﹐四壁粉刷得潔白如雪﹐靠牆擺放著幾個
蒲團和木魚。室內光線柔和﹐從高處的小窗透進幾縷陽光﹐在地上投
下斑駁的光影。角落裡放著一座小小的香爐﹐裊裊的清煙緩緩上升。
在這裡靜坐片刻﹐便能感受到一股寧靜祥和的氣氛﹐令人心中的雜念
漸漸消散。
LONG
    );
    set("objects", ([
        __DIR__"npc/canyi" : 1,
    ]));
    set("exits", ([
        "west" : __DIR__"hall",
    ]));

    setup();
    replace_program(ROOM);
}

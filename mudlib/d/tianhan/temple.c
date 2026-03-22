// Room: /d/tianhan/temple.c

#include <room.h>

inherit TEMPLE;

void create()
{
    set("short", "寒山古廟");
    set("long", @LONG
一座年久失修的小廟，屋頂的瓦片殘缺不全，牆壁上的白灰大片大
片地剝落。廟裡供奉著一尊觀音石像，石像前擺著一個生了銅綠的香
爐，裡面殘留著幾根燃盡的香頭。廟裡冷冷清清，只有偶爾響起的木
魚聲打破這份寂靜，為這座荒涼的小村帶來一絲佛門的清淨之意。
LONG
    );
    set("no_fight", 1);
    set("detail", ([
        "石像" : "一尊觀音石像，雕工精細，面容慈悲。雖然廟宇破敗，石像卻被擦拭得乾乾淨淨。\n",
        "香爐" : "一個銅製香爐，表面已經發綠，裡面積著厚厚的香灰。\n",
    ]));
    set("exits", ([
        "south" : __DIR__"street2",
    ]));

    setup();
    replace_program(TEMPLE);
}

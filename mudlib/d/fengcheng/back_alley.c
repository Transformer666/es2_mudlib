// Room: /d/fengcheng/back_alley.c

inherit ROOM;

void create()
{
    set("short", "風城後巷");
    set("long", @LONG
一條狹窄陰暗的小巷﹐兩旁是高聳的石牆﹐只能容兩人並肩而過。
地上積著些髒水和枯葉﹐牆角堆放著幾個破舊的木箱。巷子裡很少
有人經過﹐偶爾能聽到牆那邊集市上傳來的叫賣聲。據說夜裡常有
野狗出沒﹐膽小的人都不敢走這條路。
LONG
    );
    set("detail", ([
        "木箱" : "幾個破舊的木箱﹐裡面空空如也﹐不知是誰丟棄在這裡的。\n",
        "石牆" : "高聳的石牆上爬滿了枯藤﹐牆面被風雪侵蝕得坑坑窪窪。\n",
    ]));
    set("exits", ([
        "north" : __DIR__"market",
    ]));

    setup();
    replace_program(ROOM);
}

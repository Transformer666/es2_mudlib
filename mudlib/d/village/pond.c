// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "村東池塘");
	set("long", @LONG
村子東邊有一方小小的池塘﹐水面上浮著幾片荷葉﹐幾尾錦鯉在
水中悠游。塘邊長著幾叢蘆葦﹐不時有蜻蜓停在葦尖上。池塘旁
放著幾塊洗衣石﹐看得出村裡的婦人常來此處浣衣。傍晚時分﹐
池塘倒映著夕陽﹐景色倒也別有一番韻味。
LONG
	);
	set("outdoors", "wilderness");
	set("exits", ([
		"west" : __DIR__"entrance",
	]));

	setup();
	replace_program(ROOM);
}

// Room: /d/sanyen/old_well.c

inherit ROOM;

void create()
{
	set("short", "枯井旁");
	set("long", @LONG
村子邊緣一口早已乾涸的老井﹐井沿的石頭被歲月侵蝕得斑駁不堪。
井邊倒著一只破木桶﹐繩索已經腐朽斷裂。井口黑洞洞的﹐往下望去
深不見底﹐偶爾有陣陰冷的風從井底吹上來﹐令人不寒而慄。附近的野
草長得格外茂盛﹐彷彿在掩蓋著什麼不為人知的秘密。
LONG
	);
	set("exits", ([
		"north" : __DIR__"east_lane",
		"west" : __DIR__"back_alley",
	]));

	setup();
	replace_program(ROOM);
}

// vim: syntax=lpc
// 任務獎勵：壓花書籤

inherit ITEM;

void create()
{
	set_name("壓花書籤", ({"pressed_flower_bookmark", "bookmark"}));
	set_weight(10);

	if( !clonep() ) {
		set("unit", "枚");
		set("value", 100);
		set("long",
			"一枚用竹片製成的小書籤﹐中間夾著一朵壓乾的紫色小花﹐\n"
			"雖然做工稚拙﹐卻透著一股純真的心意。書籤上歪歪扭扭地\n"
			"寫著「謝謝」兩個字。\n");
	}

	setup();
}

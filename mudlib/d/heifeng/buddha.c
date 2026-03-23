// Room: /d/heifeng/buddha.c
// Quest: buddha_relic - 石佛遺物
// Flow: look 字跡 -> wipe/clean inscription -> discover hole -> reach inside -> jade rosary

inherit ROOM;

void give_relic(object player);

void create()
{
	set("short", "石佛像");
	set("long", @LONG
路旁的草叢中有一尊半埋在土裡的石佛像﹐佛像已經殘破不堪﹐面
容模糊﹐但仍然可以看出是一尊結跏趺坐的佛陀像。佛像前面的地上
散落著一些野花﹐似乎有人偶爾會來此祭拜。石佛背後刻著幾行模糊
的字跡﹐已難以辨認。
LONG
	);
	set("detail", ([
		"字跡" : "石佛背後刻著幾行字﹐被泥土和青苔覆蓋﹐模糊難辨。如果把上面的泥苔擦掉﹐也許能看清楚。\n",
		"佛像" : "雖然殘破﹐但佛像的蓮花座依然完好。蓮花座底部似乎有些異樣。\n",
		"野花" : "幾朵不知名的野花﹐已經半枯了。\n",
		"蓮花座" : "佛像的蓮花座雕工精細﹐底部有一道細縫﹐像是可以打開的。\n",
	]));
	set("exits", ([
		"west" : __DIR__"road2",
	]));

	setup();
}

void init()
{
	add_action("do_wipe", "wipe");
	add_action("do_wipe", "clean");
	add_action("do_wipe", "擦");
	add_action("do_reach", "reach");
	add_action("do_reach", "探");
	add_action("do_reach", "open");
	add_action("do_reach", "打開");
}

int do_wipe(string arg)
{
	object player;

	player = this_player();
	if( !player ) return 0;

	if( !arg || (strsrch(arg, "字跡") < 0 && strsrch(arg, "inscription") < 0
	&&  strsrch(arg, "碑文") < 0 && strsrch(arg, "字") < 0
	&&  strsrch(arg, "佛") < 0 && strsrch(arg, "statue") < 0
	&&  strsrch(arg, "泥") < 0 && strsrch(arg, "苔") < 0) )
		return notify_fail("你想擦拭什麼？\n");

	if( player->query("quest/buddha_relic_done") ) {
		write("石佛背後的字跡已經被你擦拭乾淨﹐上面刻著一段佛偈。\n");
		return 1;
	}

	if( player->query_temp("pending/buddha_relic") ) {
		write(
			"你已經擦過了。字跡寫的是﹕\n"
			"「身是菩提樹﹐心如明鏡臺。時時勤拂拭﹐勿使惹塵埃。」\n"
			"蓮花座底部有一道細縫﹐也許可以打開看看。\n");
		return 1;
	}

	message_vision(
		"$N蹲下身來﹐仔細地用衣袖擦去石佛背後的泥苔。\n", player);

	write(
		"你擦去厚厚的泥苔﹐石佛背後的字跡漸漸顯露出來﹕\n"
		"「身是菩提樹﹐心如明鏡臺。時時勤拂拭﹐勿使惹塵埃。」\n\n"
		"你注意到蓮花座底部有一道細縫﹐似乎可以打開。\n");

	player->set_temp("pending/buddha_relic", 1);
	return 1;
}

int do_reach(string arg)
{
	object player;

	player = this_player();
	if( !player ) return 0;

	if( !arg || (strsrch(arg, "蓮花") < 0 && strsrch(arg, "底部") < 0
	&&  strsrch(arg, "細縫") < 0 && strsrch(arg, "lotus") < 0
	&&  strsrch(arg, "佛") < 0 && strsrch(arg, "statue") < 0
	&&  strsrch(arg, "座") < 0) )
		return notify_fail("你想打開什麼？\n");

	if( player->query("quest/buddha_relic_done") ) {
		write("蓮花座裡面的暗格已經空了。\n");
		return 1;
	}

	if( !player->query_temp("pending/buddha_relic") ) {
		write("蓮花座底部隱約有一道細縫﹐但你不太確定如何打開。也許先仔細觀察佛像會有發現。\n");
		return 1;
	}

	message_vision(
		"$N小心翼翼地沿著細縫用力一推﹐蓮花座底部的石板緩緩移開﹐"
		"露出一個小暗格。\n", player);

	call_out("give_relic", 2, player);
	return 1;
}

void give_relic(object player)
{
	object rosary;

	if( !player || environment(player) != this_object() ) return;
	if( player->query("quest/buddha_relic_done") ) return;

	rosary = new(__DIR__"npc/obj/jade_rosary");
	if( !rosary ) return;

	message("vision",
		"暗格裡面放著一串玉念珠﹐珠子上隱約刻著細小的梵文﹐"
		"散發著溫潤的光澤。\n",
		this_object());

	if( rosary->move(player) )
		rosary->move(this_object());

	player->set("quest/buddha_relic_done", 1);
	player->gain_score("quest", 100);
	player->delete_temp("pending/buddha_relic");

	message("vision",
		player->name() + "從暗格中取出玉念珠﹐握在手裡﹐一股寧靜祥和"
		"的感覺油然而生。\n",
		this_object());
}

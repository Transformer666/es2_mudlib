// Room: /d/lijun/riverbank.c
// Quest: 鯉君渡金鯉傳說 (golden_carp)
// Action: fish here with bamboo_pole to catch the golden carp

inherit ROOM;

int do_fish(string arg);
void fish_result(object player);

void create()
{
	set("short", "河灘");
	set("long", @LONG
碼頭南邊是一片開闊的河灘﹐細沙和鵝卵石鋪滿了地面。河水在
此處放緩了腳步﹐形成一個淺淺的灣﹐水面平靜如鏡。幾條小漁船擱
淺在灘上﹐船底朝天曬著太陽。一個老翁蹲坐在河邊﹐手持釣竿﹐靜
靜地垂釣。這裡遠離喧囂﹐只聽得到流水聲和偶爾傳來的鳥叫。往北
走回到碼頭。
LONG
	);
	set("outdoors", "water");
	set("detail", ([
		"漁船" : "幾條小漁船﹐船身斑駁﹐看得出已經用了很多年﹐船艙裡還殘留著魚鱗和漁網。\n",
		"河水" : "河灘邊的河水清淺見底﹐可以看到水底的鵝卵石和游動的小魚。\n",
	]));
	set("objects", ([
		__DIR__"npc/fisherman" : 1,
	]));
	set("exits", ([
		"north" : __DIR__"dock",
	]));

	setup();
}

void init()
{
	::init();
	add_action("do_fish", "fish");
}

int do_fish(string arg)
{
	object me, weapon;

	me = this_player();

	if( me->is_fighting() ) {
		write("你正在戰鬥中﹐沒辦法釣魚﹗\n");
		return 1;
	}

	if( me->query("quest/golden_carp_done") ) {
		write("你已經釣到過金鯉了﹐不需要再釣了。\n");
		return 1;
	}

	if( !me->query_temp("pending/golden_carp") ) {
		write("你隨意地往河裡看了看﹐不知道該釣什麼。也許可以先問問那位老翁。\n");
		return 1;
	}

	// Check if player has a bamboo_pole
	weapon = me->query_temp("wielding");
	if( !weapon || weapon->base_name() != __DIR__"npc/obj/bamboo_pole" ) {
		write("你得先拿一根竹竿才能釣魚。碼頭的行商那邊有賣。\n");
		return 1;
	}

	write("你將竹竿拋入水中﹐靜靜地等待魚兒上鉤……\n");
	message_vision("$N將竹竿拋入水中﹐靜靜地等待魚兒上鉤。\n",
		me);

	call_out("fish_result", 3 + random(3), me);
	return 1;
}

void fish_result(object player)
{
	object scale;

	if( !player || environment(player) != this_object() ) return;
	if( player->query("quest/golden_carp_done") ) return;

	if( random(100) < 40 ) {
		// Failure - normal catch
		write("竹竿猛地一沉﹐你用力一提——卻只釣到一條普通的小魚。\n",
			player);
		message("vision",
			"$N用力提起竹竿﹐卻只釣到一條小魚﹐有些失望。\n",
			environment(player), player);
		return;
	}

	// Success - golden carp!
	write(
		"忽然﹐水面下金光一閃﹐竹竿猛地被拉彎了﹗你死死握住竹竿﹐\n"
		"與水中的大魚拉鋸了好一會兒。一條渾身金光閃閃的大鯉魚躍出水\n"
		"面﹐在空中劃過一道金色的弧線﹐落在灘上不停地翻滾。\n"
		"\n"
		"你定睛一看﹐這鯉魚足有三尺來長﹐鱗片金光燦燦﹐雙目靈動有\n"
		"神﹐果然不是普通的魚。金鯉掙扎了一會兒﹐忽然安靜下來﹐化為\n"
		"一片金色的鱗片留在你手中﹐魚身則化作一道金光鑽回了水裡。\n",
		player);

	message("vision",
		"$N奮力拉起竹竿﹐一條金光閃閃的大鯉魚躍出水面﹗金鯉在灘上\n"
		"翻滾片刻﹐化為一道金光鑽回水中﹐只留下一片金色鱗片。\n",
		environment(player), player);

	scale = new(__DIR__"npc/obj/golden_scale");
	if( !scale->move(player) )
		scale->move(environment(player));

	player->set("quest/golden_carp_done", 1);
	player->delete_temp("pending/golden_carp");
	player->gain_score("quest", 80);
}

// Room: /d/caobang/hall.c
// 漕幫禮堂——漕幫在京畿（史部尚書府旁）的議事禮堂﹐也是漕幫這一幫派的總壇。
//
// 【幫派 daemon 種子】
//   本房間於 create() 內向中央幫派 daemon（CLAN_D = /daemon/misc/clan）登錄漕幫﹕
//     CLAN_D->register_clan("漕幫", "jiangyun");   // 以江隕(jiangyun)為創幫者﹔
//                                                  // daemon 內已存在則回 0（idempotent﹐每次載入皆可安全呼叫）
//     CLAN_D->set_hall("漕幫", base_name(this_object()));  // 將本禮堂登記為漕幫總壇
//   如此一來﹐漕幫自開機起便是 ccmd / list_clans 查得到的既有幫派﹐
//   而毋須改動 daemon 檔案本身。register_clan 為冪等﹐重載房間不會重複建幫或洗掉既有資料。
//
// 禮堂內常駐兩名純氣氛 NPC：江隕（漕幫在京畿的耆宿）、宋安江（禮堂分舵主）。
// 南穿漕幫巷回運河渡口（/d/caobang/lane），互為往返。

inherit ROOM;

void create()
{
	set("short", "漕幫禮堂");
	set("long", @LONG
這是漕幫在京畿的禮堂——緊傍著史部尚書府的一進軒敞廳堂。論
規制﹐遠不及尚書府的鐘鳴鼎食﹐卻自有一股漕運大幫的厚重氣派。當
廳一張烏木的長案﹐案後一把太師椅﹐壁上高懸著一面「漕」字大旗﹐
旗下供著漕幫歷代總舵主的牌位與一具鎮幫的鐵錨。兩壁掛著南北漕路
的水程圖﹐密密麻麻標著沿途的水驛、險灘與分舵。漕幫執掌天下漕
運﹐幫眾數十萬眾﹐沿著大運河南北分舵林立﹔這禮堂雖小﹐卻是漕幫
在天子腳下議事、待客、收徒的所在。堂上幾名管事的幫眾進進出出﹐
神色幹練。出禮堂往南﹐穿漕幫巷便回到運河渡口。
LONG
	);
	set("detail", ([
		"漕字大旗" : "壁上高懸著一面玄青底的大旗﹐當中拿白漆繪著斗大的一個「漕」字﹐旗角繡著翻捲的水波紋。這便是漕幫的幫旗了——大運河上往來的漕船﹐見了這面旗﹐莫不避讓三分。\n",
		"長案" : "當廳一張烏沉沉的烏木長案﹐案面厚重﹐擺著文房四寶與一函函的漕運帳冊。案後一把太師椅﹐是漕幫總舵主與分舵主議事時的座次﹐尋常幫眾不得擅坐。\n",
		"牌位" : "旗下一座神龕﹐供著漕幫歷代總舵主的牌位。漕幫源遠流長﹐自前朝開鑿大運河、設漕運糧道時便已立幫﹐傳到如今﹐這一輩輩的牌位排得齊整﹐受著合幫的香火。\n",
		"鐵錨" : "神龕前供著一具半人高的鐵錨﹐錨身鏽蝕斑駁﹐卻磨得稜角發亮。相傳這是漕幫開幫祖師當年那條漕船上的舊錨﹐世代供在禮堂﹐是漕幫鎮幫的信物﹐取一個「定得住風浪」的彩頭。\n",
		"水程圖" : "兩壁掛著幾幅南北漕路的水程圖﹐自江南的魚米之鄉一路標到京畿﹐沿途的水驛、險灘、閘口與漕幫的分舵都拿朱筆細細標出。單看這圖﹐便知漕幫的勢力沿著一條大運河鋪得有多遠。\n",
		"幫眾" : "堂上幾名管事的幫眾穿著利落的短打﹐腰間束著青帶﹐進進出出地理著漕運的帳目與貨單﹐神色幹練。漕幫號稱幫眾數十萬﹐這些在禮堂當差的﹐都是幫裡頭有些身份的人物了。\n",
	]));
	set("outdoors", "capital");
	set("no_fight", 1);
	set("objects", ([
		__DIR__"npc/jiangyun" : 1,
		__DIR__"npc/songanjiang" : 1,
	]));
	set("exits", ([ /* sizeof() == 1 */
		"south" : __DIR__"lane",
	]));

	// 向中央幫派 daemon 登錄漕幫為既有幫派﹐並把本禮堂設為總壇。
	// register_clan 冪等：daemon 內已有「漕幫」時回 0﹐故每次載入呼叫皆安全﹐
	// 不會重複建幫、不會覆蓋既有成員 / 金庫 / 紀錄。base_name(this_object())
	// 在 create() 內求得本藍圖路徑（/d/caobang/hall﹐不含 .c），正合 set_hall 所需。
	// 四鬼問環支線的創幫人正是江隕(jiangyun)﹐故以其 uid 為 founder。
	// 須先設 euid，否則 create() 內首次參照 CLAN_D 觸發 daemon 載入時無 effective
	// user →「Can't load objects when no effective user」→ 整個 create() 中止、房間載不起來。
	seteuid(getuid());
	CLAN_D->register_clan("漕幫", "jiangyun");
	CLAN_D->set_hall("漕幫", base_name(this_object()));

	setup();
	replace_program(ROOM);
}

// vim: set ts=4 sw=4 syntax=lpc

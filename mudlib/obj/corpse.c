

inherit ITEM;

// 腐爛分段對齊 docs：
//   玩家屍 (chard.c 傳入 base=90)：腐爛 3 / 變骨 4.5 / 化灰 6 分 -> 180 / 270 / 360 秒
//   MOB 屍  (chard.c 傳入 base=60)：腐爛 2 / 變骨 3   / 化灰 4 分 -> 120 / 180 / 240 秒
// 兩者皆為「累積 2*base / 3*base / 4*base」，即每段延遲 2*base, base, base。
// 玩家/MOB 判定：以 chard.c start_decay() 傳入的 base 區分 (>=90 視為玩家屍)，
// 不另改 chard.c (避免跨檔撞)。預設 base=60 (MOB) 作為未呼叫 start_decay 時的後備。
static int decayed = 0;
static int decay_interval = 60;

void create()
{
    set_name("無名屍體", ({ "corpse" }) );
    set("long", "這是一具無名屍體。\n");
    set("unit", "具" );
    setup();
}

// 玩家屍判定：chard.c 對玩家傳 base=90、對 MOB 傳 base=60。
// >=90 視為玩家屍 (僅供文字/旗標查詢，分段公式對兩者一致)。
int is_player_corpse() { return decay_interval >= 90; }

void
start_decay(int interval)
{
    if( interval < 1 ) interval = 1;

    decay_interval = interval;

    remove_call_out("decay");
    decayed = 0;
    // 第一段 (腐爛) 在 2*base 後發生：玩家 180s(3分) / MOB 120s(2分)。
    call_out("decay", decay_interval * 2);
}

int is_corpse() { return decayed < 2; }
int is_character() { return decayed < 1; }

string short() { return name() + "(" + capitalize(query("id")) + ")"; }

void decay()
{
    switch(++decayed) {
        case 1:
            say( query("name") + "開始腐爛了﹐發出一股難聞的惡臭。\n" );
            switch(query("gender")) {
                case "male":
                    set_name("腐爛的男屍", ({ "corpse" }) );
                    break;
                case "female":
                    set_name("腐爛的女屍", ({ "corpse" }) );
                    break;
                default:
                    set_name("腐爛的屍體", ({ "corpse" }) );
                    break;
            }
            set("long", "這具屍體顯然已經躺在這裡有一段時間了﹐正散發著一股腐屍的味道。\n");
            // 第二段 (變骨) 再過 base：玩家累積 270s(4.5分) / MOB 累積 180s(3分)。
            call_out("decay", decay_interval);
            break;
        case 2:
            say( query("name") + "被風吹乾了﹐變成一具骸骨。\n" );
            set_name("枯乾的骸骨", ({ "skeleton" }) );
            set("long", "這副骸骨已經躺在這裡很久了。\n");
            // 第三段 (化灰) 再過 base：玩家累積 360s(6分) / MOB 累積 240s(4分)。
            call_out("decay", decay_interval);
            break;
        case 3:
            say( "一陣風吹過﹐把" + query("name") + "化成骨灰吹散了。\n" );
            destruct(this_object());
            break;
    }
}

int receive_object(object oob, int from_inventory) { return 1; }

// vim: set ts=4 sw=4 syntax=lpc


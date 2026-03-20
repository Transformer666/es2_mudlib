# Agent Task 06：實作技能 Daemon（Skills）

## 目標

根據原版 ES2 mudlib 比對結果，實作所有缺少的技能 daemon，
並確保所有技能都有 `skill_improved()` 和 `skill_advanced()` 函數。

---

## 前置知識

技能 daemon 存放於 `mudlib/daemon/skill/`，參考 `automation/CLAUDE.md` 範本。

戰鬥技能模式：
```lpc
inherit SKILL;
mapping *actions = ({ ... });
void create() { seteuid(getuid()); DAEMON_D->register_skill_daemon("xxx"); setup(); }
void attack_using(object me, object opponent, object weapon) { ... }
int valid_enable(string usage) { return 0; }
void skill_improved(object me, string sk) { ... }
void skill_advanced(object me, string sk) { ... }
```

內功模式：額外有 `do_exercise()`, `halt_exercise()`, `exert_function()`

## 資料來源

原版技能列表（`gh api repos/mudchina/es2/contents/daemon/skill`）取得完整清單，
比對我們已有的技能，找出缺少的。

Blog 技能資料：
```
# 戰鬥系統
https://es2tips.blogspot.com/2014/09/es2.html                         # 戰鬥攻擊防禦設定
https://es2tips.blogspot.com/2014/10/mobnpc-swordbladepikeaxeneedlestaffunar.html  # 物理練功 Mob
https://es2tips.blogspot.com/2014/11/stakelionbuddhapillar.html       # 練功標靶

# 門派武功
https://es2tips.blogspot.com/2014/02/mao-shan-sword.html              # 茅山劍法
https://es2tips.blogspot.com/2014/02/taoism-cloud.html                # 天師道法素雲書
https://es2tips.blogspot.com/2015/11/blog-post_7.html                 # 金剛鎚法穿靈
https://es2tips.blogspot.com/2015/11/blog-post_77.html                # 天師道士幻劍術

# 道士法術系
https://es2tips.blogspot.com/2014/08/es2_47.html                      # 隱風觀（喚雨算命）
https://es2tips.blogspot.com/2014/08/es2_71.html                      # 靈雲觀（五雷幽冥三箭）
https://es2tips.blogspot.com/2014/08/es2_76.html                      # 幻霧觀（噬魂通靈鬼火）
https://es2tips.blogspot.com/2014/08/es2_75.html                      # 紫衣派（雷）
https://es2tips.blogspot.com/2014/08/es2_64.html                      # 素衣派（冰）
https://es2tips.blogspot.com/2014/08/es2_85.html                      # 玄衣派（風）
https://es2tips.blogspot.com/2014/08/es2_13.html                      # 朱衣派（火）
https://es2tips.blogspot.com/2013/06/blog-post_9349.html              # 四鬼招喚法

# 輕功 & 特殊技能
https://es2tips.blogspot.com/2014/10/blog-post_29.html                # 水神天龍走法
https://es2tips.blogspot.com/2013/05/blog-post_5878.html              # 八穴鬼徑走法
```

原版缺少的技能（可能需要實作）：
```
bloodystrike, bolomiduo, buddhism, celestial, celestrike
chanting, chaos-steps, cloudstaff, deisword, essencemagic
fall-steps, fonxanforce, fonxansword, fork, gouyee
iceforce, instruments, iron-cloth, jin-gang, jingang-staff
juechen-force, linbo-steps, literate, liuh-ken, notraces
perception, pyrobat-steps, qidaoforce, scratching, serpentforce
shortsong-blade, six-chaos-sword, snowshade-force, snowshade-sword
snowwhip, spells, spicyclaw, spider-array, spring-blade
stealing, stormdance, tao-mystery, taoism, tenderzhi
throwing, ts-fist, wu-shun, yirong
```

## 執行步驟

### Step 1：比對現有技能
```bash
# 我們有的
ls mudlib/daemon/skill/*.c | sed 's|.*/||;s|\.c||' | sort

# 原版有的
gh api repos/mudchina/es2/contents/daemon/skill --jq '.[].name' | sed 's|\.c||' | sort

# 差異
comm -23 <(原版) <(我們的)
```

### Step 2：優先順序

1. **基礎技能**（perception、stealing、literate — 非戰鬥通用技能）
2. **門派武功**（fonxansword、fonxanforce 等門派專屬）
3. **法術系統**（taoism、spells、buddhism、essencemagic）
4. **輕功系統**（chaos-steps、fall-steps、linbo-steps、notraces）
5. **特殊技能**（yirong 易容、throwing 暗器）

### Step 3：每個技能 daemon 必須

1. `inherit SKILL`
2. `DAEMON_D->register_skill_daemon("xxx")`
3. `skill_improved()` — 學習進度升級邏輯
4. `skill_advanced()` — 技能等級提升獎勵
5. **戰鬥技能需有完整招式系統**（見 Step 3A）
6. **內功技能需有練功系統**（見 Step 3B）

### Step 3A：戰鬥技能招式規範（actions mapping）

每個戰鬥技能必須有 `actions` mapping 陣列和 `attack_using()` 函數。
招式數量：至少 6 招，建議 8 招。

招式 mapping 格式：
```lpc
mapping *actions = ({
    ([
        "action":       "$N使一招「招式名」，$w刺向$n的$l",   // 攻擊描述
        "dodge":        -10,        // 閃避修正（負=難閃，正=好閃）
        "damae":        5,          // 傷害修正（注意：部分檔案用 damae 不是 damage）
        "damage_type":  "刺傷"      // 傷害類型：瘀傷/割傷/刺傷/斲傷
    ]),
    // ... 更多招式
});
```

**招式描述變數：**
- `$N` = 攻擊者名字
- `$n` = 防禦者名字
- `$w` = 武器名字
- `$l` = 攻擊部位（系統隨機填入）
- `$p` = 防禦者的「的」

**各武器類型的招式風格：**

| 類型 | damage_type | 招式風格 | 範例動作 |
|------|-------------|---------|---------|
| 劍 sword | 刺傷/割傷 | 刺、斬、劈、削 | 蹲低身子刺向、揮劍斬下、橫劍一劃 |
| 刀 blade | 割傷/斲傷 | 砍、劈、削、斬 | 揮刀劈下、橫刀一掃、反手一刀 |
| 匕首 dagger | 刺傷 | 刺、划、削 | 閃身刺出、反手一划、疾刺 |
| 針 needle | 刺傷 | 刺、點、挑 | 彈指射出、點向穴道、飛針刺出 |
| 棍 staff | 瘀傷 | 掃、砸、撥、點 | 橫掃過去、當頭一棒、點向穴道 |
| 槍 pike | 刺傷/割傷 | 刺、挑、掃 | 中平槍刺出、挑槍上撩、橫掃千軍 |
| 斧 axe | 割傷/斲傷 | 劈、砍、掃 | 當頭劈下、橫斧一掃、斜劈 |
| 鞭 whip | 瘀傷/割傷 | 抽、纏、掃 | 鞭梢抽出、纏住手腕、橫掃過去 |
| 徒手 unarmed | 瘀傷 | 拳、踢、肘、膝 | 握拳揮出、飛踢過去、肘擊 |
| 鎚 hammer | 瘀傷 | 砸、擊、壓 | 當頭砸下、橫擊過去、重壓 |

**門派武功招式命名規範：**
門派武功每招要有**招式名稱**，用「」包裹：
```lpc
"action": "$N使一招「峰回路轉」，手中$w刺向$n的$l"
"action": "$N一式「空山鳥語」，劍光霍霍斬向$n的$l"
```

參考已有的門派招式（`mudlib/daemon/skill/fengshan_sword.c`）：
```
峰回路轉、空山鳥語、御風而行、旭日東升、金光瀉地、童子引路、柳暗花明、空谷秋虹
```

每個門派武功需根據門派特色設計 6-8 個獨特招式名。

**interattack 陣列（攻擊間隔描述）：**
```lpc
string *interattack = ({
    "$N緊握著手中的$n﹐緩緩移動。\n",
    "$N目光銳利地注視著$n的動作。\n",
});
```

**attack_using 函數範本：**
```lpc
void attack_using(object me, object opponent, object weapon)
{
    int damage;
    if( !opponent ) {
        if( me->query_temp("last_attacked_target") )
            message_vision(CYN + interattack[random(sizeof(interattack))] + NOR, me, weapon);
        return;
    }
    damage = COMBAT_D->fight(me, opponent, "skill_name", actions[random(sizeof(actions))], weapon);
}
```

### Step 3B：內功技能練功系統

內功技能不需要 `actions`/`attack_using`，但需要：
```lpc
int valid_enable(string usage) { return usage == "force"; }

int do_exercise(object me)
{
    // 消耗精/氣/神，給予 improve_skill
    if( me->query_stat("gin") < 10 || me->query_stat("kee") < 10 ) {
        tell_object(me, "你覺得神困力乏﹐沒有辦法繼續練功了。\n");
        me->interrupt_me(me, "exhausted");
        return 1;
    }
    me->consume_stat("gin", 10);
    me->consume_stat("kee", 10);
    me->consume_stat("sen", 10);
    me->improve_skill("skill_name", random(me->query_attr("spi")/10) + 1);
    me->improve_skill("force", random(me->query_attr("int")/10) + 1);
    return 1;
}

int halt_exercise(object me, object owner, object from, string how) { return 1; }

varargs int exert_function(object me, string func, object target)
{
    switch(func) {
    case "skill_name":
        message_vision(HIY "$N盤膝而坐﹐運起內功心法。\n" NOR, me);
        me->start_busy((: do_exercise, me :), (: halt_exercise, me :));
        return 1;
    default:
        return notify_fail("此內功沒有這種功能。\n");
    }
}
```

參考已有的內功：`mudlib/daemon/skill/maoshan_neigong.c`

### Step 3C：法術技能系統

道士法術需要 `valid_enable` 回傳 `"magic"` 或 `"spell"`：
```lpc
int valid_enable(string usage) { return usage == "magic"; }
```

法術招式用 `damage_type` 標記元素類型（冰傷/火傷/雷傷/風傷）。

Blog 法術參考：
```
# 天師派四元素
https://es2tips.blogspot.com/2014/08/es2_75.html   # 紫衣派（雷）
https://es2tips.blogspot.com/2014/08/es2_64.html   # 素衣派（冰）
https://es2tips.blogspot.com/2014/08/es2_85.html   # 玄衣派（風）
https://es2tips.blogspot.com/2014/08/es2_13.html   # 朱衣派（火）

# 茅山三觀
https://es2tips.blogspot.com/2014/08/es2_47.html   # 隱風觀（喚雨、算命）
https://es2tips.blogspot.com/2014/08/es2_71.html   # 靈雲觀（五雷、幽冥三箭）
https://es2tips.blogspot.com/2014/08/es2_76.html   # 幻霧觀（噬魂、通靈、鬼火）
```

### Step 3D：輕功 / 非戰鬥技能

輕功技能不需要 `actions`，通常提供：
- `valid_enable` 回傳 `"dodge"` 或 `"movement"`
- 被動加成（透過 `skill_advanced` 給 dex/move 加成）

非戰鬥技能（perception、stealing、literate、yirong）：
- 各有特殊用途，不需要 `attack_using`
- 需要 `skill_improved` / `skill_advanced`
- 具體實作視技能而定

### Step 4：靜態驗證

```bash
for f in mudlib/daemon/skill/*.c; do
  name=$(basename "$f" .c)
  has_inherit=$(grep -c 'inherit SKILL' "$f")
  has_register=$(grep -c 'register_skill_daemon' "$f")
  has_improved=$(grep -c 'skill_improved' "$f")
  has_actions=$(grep -c '"action"' "$f")
  echo "$name: inherit=$has_inherit register=$has_register improved=$has_improved actions=$has_actions"
done
```

---

## 完成條件

- [ ] 所有缺少的技能 daemon 建立完成
- [ ] 所有戰鬥技能有至少 6 招招式（actions mapping）
- [ ] 所有門派武功招式有獨特招式名（用「」包裹）
- [ ] 所有內功技能有 do_exercise/halt_exercise/exert_function
- [ ] 所有技能 daemon 有 skill_improved/skill_advanced
- [ ] 靜態驗證通過

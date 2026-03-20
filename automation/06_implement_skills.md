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
5. 戰鬥技能需有 `attack_using()` 和 `actions` mapping

### Step 4：靜態驗證

```bash
for f in mudlib/daemon/skill/*.c; do
  name=$(basename "$f" .c)
  has_inherit=$(grep -c 'inherit SKILL' "$f")
  has_register=$(grep -c 'register_skill_daemon' "$f")
  has_improved=$(grep -c 'skill_improved' "$f")
  echo "$name: inherit=$has_inherit register=$has_register improved=$has_improved"
done
```

---

## 完成條件

- [ ] 所有缺少的基礎技能 daemon 建立完成
- [ ] 所有現有技能 daemon 有 skill_improved/skill_advanced
- [ ] 靜態驗證通過

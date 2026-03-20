對 mudlib 執行靜態驗證。

## 輸入

$ARGUMENTS = 驗證類別（rooms/npcs/daemons/equipment/exits/skills/all），預設 all

## 驗證項目

### rooms
```bash
# 檢查 inherit ROOM 或 INN 或 TEMPLE
# 檢查 set("short") 和 setup() 存在
for file in $(find mudlib/d/ -maxdepth 2 -name "*.c" ! -path "*/npc/*"); do ...
```

### npcs
```bash
# 檢查 #include <npc.h>、inherit F_*、set_name、setup()
for file in $(find mudlib/d/ -path "*/npc/*.c" ! -path "*/npc/obj/*"); do ...
```

### daemons
```bash
# race: inherit HUMANOID + register_race_daemon
# skill: inherit SKILL + register_skill_daemon + skill_improved
# sect: inherit F_DBASE + register_object_daemon
# class: inherit F_DBASE + query_rank
```

### exits（雙向連結）
```bash
# 每個房間的每個出口，確認目標房間有反向出口
```

### skills（技能完整性）
```bash
for f in mudlib/daemon/skill/*.c; do
  # 檢查 inherit/register/skill_improved/skill_advanced
  # 戰鬥技能檢查 actions 數量 >= 6
done
```

### 額外檢查
- aggressive 屬性：確認用 `set("attitude", "aggressive")` 不是 `set("aggressive", 1)`
- vision_of_ghost：掌門 lv50+ 和道士/和尚 NPC 有 `set_temp("apply/vision_of_ghost", 1)`
- 門派 location：sect daemon 的 location 指向存在的房間

輸出：PASS/FAIL 計數和失敗項目清單

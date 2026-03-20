根據指定的技能名稱建立 skill daemon。

## 輸入

$ARGUMENTS = 技能名稱（如 "fonxan sword" 或 "封山劍法"）

## 步驟

1. 讀取 `automation/wiki_reference.md` 確認該技能屬於哪個門派、什麼類型
2. 讀取 `automation/CLAUDE.md` 的「技能 Daemon (Skill)」範本
3. 讀取 `automation/06_implement_skills.md` 的 Step 3A-3D 了解各類型技能的規範
4. 判斷技能類型並選擇範本：

### 戰鬥技能（有招式）
- 參考：`mudlib/daemon/skill/fengshan_sword.c`
- 需要：`actions` mapping（至少 6 招，門派武功要有獨特招式名）
- 需要：`attack_using()`、`interattack`
- 需要：`skill_improved()` + `skill_advanced()`
- `damage_type`：劍=刺傷/割傷、刀=割傷/斲傷、拳=瘀傷、針=刺傷

### 內功技能（練功系統）
- 參考：`mudlib/daemon/skill/maoshan_neigong.c`
- 需要：`do_exercise()` + `halt_exercise()` + `exert_function()`
- 需要：`valid_enable` 回傳 `"force"`
- `skill_improved` 門檻 learn >= 1500
- `skill_advanced` 給 gin/kee/sen advance_stat

### 法術技能（道士系）
- `valid_enable` 回傳 `"magic"` 或 `"spell"`
- `damage_type` 用元素：冰傷/火傷/雷傷/風傷

### 非戰鬥技能（perception/stealing/literate）
- 不需要 `actions` 或 `attack_using`
- 需要 `skill_improved` + `skill_advanced`

5. 建立 `mudlib/daemon/skill/<name>.c`
6. 確認 `DAEMON_D->register_skill_daemon("<name>")` 的名稱與門派 daemon 的 `set("skills")` 一致
7. 靜態驗證：inherit SKILL、register、skill_improved、actions 數量
8. 輸出建立的檔案和招式列表

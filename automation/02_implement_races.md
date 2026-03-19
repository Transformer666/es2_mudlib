# Agent Task 02：實作種族（Races）

## 目標

根據 `docs/missing_content.json` 的 missing_races，
實作所有缺少的種族 daemon .c 檔案和 help 文本。

---

## 前置知識

種族 daemon 存放於 `mudlib/daemon/race/`，參考 `CLAUDE.md` 的「種族 Daemon (Race)」範本。

核心模式：
```lpc
#include <race.h>
inherit HUMANOID;

private void create()
{
    ::create();
    seteuid(getuid());
    set("karma", 5);
    set("civilized", 1);
    DAEMON_D->register_race_daemon("race_id");
}

void setup(object ob) { ... }       // 角色選種族時
void initialize(object ob) { ... }  // 初始化屬性
```

## 執行步驟

### Step 1：讀取資料
```
讀取 docs/wiki_content.json → races 區塊
讀取 docs/missing_content.json → missing_races 區塊
參考 mudlib/daemon/race/human.c 作為範本
```

### Step 2：對每個 missing race 產生 daemon 檔案

路徑：`mudlib/daemon/race/{race_id}.c`

10 個已知種族：
```
human      人類      業力：5
headless   刑天      業力：?（從 wiki 取得）
yenhold    厭火      業力：?
yaksa      夜叉      業力：?
malik      巫首      業力：?
woochan    無腸      業力：?
jiaojao    焦僥      業力：?
dingling   釘靈      業力：?
ashura     阿修羅    業力：?
rainnar    雨師妾    業力：?
blackteeth 黑齒      業力：?
```

### Step 3：產生 Help 文本

路徑：`mudlib/doc/help/player/races/{race_name}`

格式：
```
{種族名} ({英文名})
==================

{背景故事描述，2-3 段}

【種族特性】
  體力：+X
  敏捷：+X
  ...

【業力消耗】
  {數值} 點業力

【種族特殊能力】
  {如有特殊能力則描述}

相關指令：help races（查看所有種族列表）
```

### Step 4：靜態驗證

對每個新建的 .c 檔案進行靜態檢查：
- 確認 `#include <race.h>` 存在
- 確認 `inherit HUMANOID` 存在
- 確認 `DAEMON_D->register_race_daemon("xxx")` 存在
- 確認 `setup()` 和 `initialize()` 函數存在

### Step 5：更新進度記錄

更新 `docs/implementation_log.md` 的種族區塊。

---

## 完成條件

- [ ] 所有缺少的種族 daemon .c 檔案建立完成
- [ ] 所有種族 help 文本建立完成
- [ ] 靜態驗證通過
- [ ] `docs/implementation_log.md` 更新完成

# Agent Task 02：實作種族（Races）

## 目標

根據 `docs/missing_content.json` 的 races 區塊，
實作所有缺少的種族 daemon .c 檔案和 help 文本。

---

## 前置知識

種族 daemon 存放於 `mudlib/daemon/race/`，參考 `automation/CLAUDE.md` 的「種族 Daemon (Race)」範本。

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

## 資料來源

爬取以下 Wiki 頁面取得種族設定：
```
https://sites.google.com/site/es2mud/home/story-lines/zhong-zu-she-ding/human
https://sites.google.com/site/es2mud/home/story-lines/zhong-zu-she-ding/headless
https://sites.google.com/site/es2mud/home/story-lines/zhong-zu-she-ding/yenhold
https://sites.google.com/site/es2mud/home/story-lines/zhong-zu-she-ding/yaksa
https://sites.google.com/site/es2mud/home/story-lines/zhong-zu-she-ding/malik
https://sites.google.com/site/es2mud/home/story-lines/zhong-zu-she-ding/woochan
https://sites.google.com/site/es2mud/home/story-lines/zhong-zu-she-ding/jiaojao
https://sites.google.com/site/es2mud/home/story-lines/zhong-zu-she-ding/dingling
https://sites.google.com/site/es2mud/home/story-lines/zhong-zu-she-ding/ashura
https://sites.google.com/site/es2mud/home/story-lines/zhong-zu-she-ding/rainnar
https://sites.google.com/site/es2mud/home/story-lines/zhong-zu-she-ding/blackteeth
```

種族裝備參考（blog）：
```
https://es2tips.blogspot.com/2014/02/rainnar-cloth-ashura-mask.html   # 雨師妾袍+修羅之面
https://es2tips.blogspot.com/2014/02/girdle-of-headless.html          # 形天之怒
https://es2tips.blogspot.com/2014/01/woochan-ring.html                # 無腸寶珠
https://es2tips.blogspot.com/2014/01/dingling-legs.html               # 釘靈腿護
https://es2tips.blogspot.com/2014/01/jiaojaos-boots.html              # 焦僥靴
https://es2tips.blogspot.com/2014/01/yenhold-gauntlets.html           # 厭火之拳
https://es2tips.blogspot.com/2014/01/blog-post_29.html                # 巫首項鍊
```

## 執行步驟

### Step 1：讀取資料
```
讀取 docs/missing_content.json → races 區塊
參考 mudlib/daemon/race/human.c 作為範本
若 missing 為 0，直接跳過此 task
```

### Step 2：對每個 missing race 產生 daemon 檔案

路徑：`mudlib/daemon/race/{race_id}.c`

11 個種族：
```
human      人類      業力：5   文明
xingtian   刑天      業力：7   文明（headless）
yenhold    厭火      業力：8   文明
yaksha     夜叉      業力：9   文明
malik      巫首      業力：7   文明
woochan    無腸      業力：6   文明
jiaojao    焦僥      業力：6   文明
dingling   釘靈      業力：8   文明
asura      阿修羅    業力：10  非文明（好鬥）
rainnar    雨師妾    業力：7   文明
blackteeth 黑齒      業力：6   文明
```

### Step 3：產生 Help 文本

路徑：`mudlib/doc/help/player/races/{race_name}`

### Step 4：靜態驗證

對每個新建的 .c 檔案進行靜態檢查：
- 確認 `#include <race.h>` 存在
- 確認 `inherit HUMANOID` 存在
- 確認 `DAEMON_D->register_race_daemon("xxx")` 存在
- 確認 `setup()` 和 `initialize()` 函數存在

---

## 完成條件

- [ ] 所有缺少的種族 daemon .c 檔案建立完成
- [ ] 所有種族 help 文本建立完成
- [ ] 靜態驗證通過

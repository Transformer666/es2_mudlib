# Agent Task 01：分析缺少的內容

## 目標

掃描目前 mudlib 的現有內容，與 ES2 wiki 資料及原版 ES2 mudlib 比對，
產生完整的待實作清單。

---

## 執行步驟

### Step 1：爬取 Wiki 及外部資料

爬取以下所有頁面，儲存到 `docs/wiki_content.json`：

#### 1A. 官方 Wiki（Google Sites）

```
# 主線任務 & 世界觀
https://sites.google.com/site/es2mud/home/zhu-xian-ren-wu
https://sites.google.com/site/es2mud/home/story-lines/mythology
https://sites.google.com/site/es2mud/home/story-lines/li-shi-gu-shi

# 種族設定（11 種族）
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

# 地圖 & 城鎮
https://sites.google.com/site/es2mud/home/story-lines/zhong-zu-she-ding/guo-jia-de-tu
https://sites.google.com/site/es2mud/home/story-lines/zhong-zu-she-ding/tian-chao-de-tu
https://sites.google.com/site/es2mud/home/story-lines/zhong-zu-she-ding/tian-chao-de-tu/wutang
https://sites.google.com/site/es2mud/home/story-lines/zhong-zu-she-ding/tian-chao-de-tu/xueting

# 職業 & 門派（7 職業，每頁含該職業所有門派資料）
https://sites.google.com/site/es2mud/home/story-lines/zhi-ye-yu-men-pai/wu-zhe
https://sites.google.com/site/es2mud/home/story-lines/zhi-ye-yu-men-pai/he-shang
https://sites.google.com/site/es2mud/home/story-lines/zhi-ye-yu-men-pai/xiao-tou
https://sites.google.com/site/es2mud/home/story-lines/zhi-ye-yu-men-pai/fang-shi
https://sites.google.com/site/es2mud/home/story-lines/zhi-ye-yu-men-pai/shu-sheng
https://sites.google.com/site/es2mud/home/story-lines/zhi-ye-yu-men-pai/jun-ren
https://sites.google.com/site/es2mud/home/story-lines/zhi-ye-yu-men-pai/dao-shi

# 裝備 & 天地靈任務
https://sites.google.com/site/es2mud/home/wan-jia-yuan-chuang/equipment
https://sites.google.com/site/es2mud/home/wan-jia-yuan-chuang/tiandiling

# 新手指南
https://sites.google.com/site/es2mud/home/you-xi-jie-zi/noobguide01
```

#### 1B. 玩家攻略 Blog（es2tips）

```
# 新手必看
https://es2tips.blogspot.com/2013/05/es2-help.html
# 殺業鍛鍊（練功地點、NPC 分佈）
https://es2tips.blogspot.com/2013/05/es2_29.html
# 茅山道士設定（門派技能細節）
https://es2tips.blogspot.com/2014/08/es2_47.html
# 裝備實錄（武器防具資料）
https://es2tips.blogspot.com/
```

#### 1C. 原版 ES2 mudlib（GitHub，用於比對區域結構）

用 `gh api` 取得原版 mudlib 的區域列表：
```bash
gh api repos/mudchina/es2/contents/d --jq '.[].name'
```

原版區域（我們可能缺少的）：
- canyon（峽谷）, choyin（喬陰）, chuenyu（泉域）
- city（城市）, death（死亡領域）, force（內功修練區）
- goathill（羊山）, graveyard（墓園）, green/green.n（草原）
- ice（冰域）, jail（監獄）, latemoon（晚月）
- oldpine（古松林）, sanyen（三掩）, snow（雪亭鎮）
- temple（神殿）, village（村莊）, waterfog（水霧）

#### 1D. 原版技能 Daemon 列表（用於比對缺少的技能）

```bash
gh api repos/mudchina/es2/contents/daemon/skill --jq '.[].name'
```

已知原版有但我們可能缺少的技能 daemon：
- bloodystrike, bolomiduo, buddhism, celestial, celestrike
- chanting, chaos-steps, cloudstaff, deisword, essencemagic
- fall-steps, fonxanforce, fonxansword, fork, gouyee
- iceforce, instruments, iron-cloth, jin-gang, jingang-staff
- juechen-force, linbo-steps, literate, liuh-ken, notraces
- perception, pyrobat-steps, qidaoforce, scratching, serpentforce
- shortsong-blade, six-chaos-sword, snowshade-force, snowshade-sword
- snowwhip, spells, spicyclaw, spider-array, spring-blade
- stealing, stormdance, tao-mystery, taoism, tenderzhi
- throwing, ts-fist, wu-shun, yirong

---

### Step 1E：門派與職業對應表（從 wiki 整理）

在分析時使用以下已確認的門派結構：

**武者 (warrior):**
- 封山派 (fengshan) — 封山劍法、封山內功
- 冷梅莊 (lengmei) — 冷梅劍法
- 哭笑門 (kuxiao) — 虎刀
- 雪吟莊 (xueyin) — 無獨門武功
- 虎刀門 (hudao) — 虎刀

**和尚 (monk):**
- 寶蓮寺 (baolian) — 治療系
- 天月庵 (tianyue) — 治療系（尚未實作？）
- 白象寺 (baixiang) — 金剛鎚法、禪師/羅漢路線

**道士 (taoist):**
- 天師派 (tianshi) — 太乙劍法、紫微內功、元素法術
- 茅山派 (maoshan) — 茅山劍法、茅山內功
  - 靈雲觀 — 狀態異常
  - 隱風觀 — 治療
  - 幻霧觀 — 爆發傷害

**小偷 (thief):**
- 瑯夷 (langyi) — 奇針術
- 隱教 (yinjiao) — 陶山迷路（內功）

**方士 (alchemist):**
- 龍圖丹派 (longttu) — 龍圖內功、煉丹
- 武陀 (wutuo) — 五敗針法、針灸

**書生 (scholar):**
- 步玄派 (buxuan) — 三轉劍法
- 玄天教 (xuantian) — 控制系

**軍人 (soldier):**
- 振武軍營 (zhenwu) — 兵法戰術

**跨門派:**
- 劍甲門 (jianjia) — 方士可拜入
- 天邪派 (tianxie) — 幻影劍法

---

### Step 2：掃描現有 mudlib 內容

掃描以下目錄，列出所有已實作的 .c 檔案：

```bash
find mudlib/d/ -name "*.c" | sort
find mudlib/daemon/ -name "*.c" | sort
find mudlib/obj/ -name "*.c" | sort
find mudlib/doc/help/player/ -type f | sort
```

同時掃描技能系統完整性：
```bash
# 檢查所有 skill daemon 是否有 skill_improved/skill_advanced
for f in mudlib/daemon/skill/*.c; do
  name=$(basename "$f" .c)
  has_improved=$(grep -c 'skill_improved' "$f")
  has_advanced=$(grep -c 'skill_advanced' "$f")
  echo "$name: improved=$has_improved advanced=$has_advanced"
done

# 檢查所有 sect daemon 的 location 是否指向存在的房間
for f in mudlib/daemon/sect/*.c; do
  loc=$(grep 'set("location"' "$f" | grep -oP '"/[^"]+')
  if [ -n "$loc" ]; then
    target="mudlib${loc}.c"
    [ -f "$target" ] && echo "OK: $target" || echo "MISSING: $target (from $f)"
  fi
done
```

---

### Step 3：比對差異，產生待實作清單

比對 wiki_content.json 與現有檔案，輸出 `docs/missing_content.json`：

```json
{
  "summary": {
    "total_required": 0,
    "total_implemented": 0,
    "total_missing": 0,
    "completion_percentage": "0%"
  },
  "races": { "required": 11, "implemented": 0, "missing": 0 },
  "classes": { "required": 7, "implemented": 0, "missing": 0 },
  "sects": { "required": 18, "implemented": 0, "missing": 0 },
  "skills": {
    "required": 0,
    "implemented": 0,
    "missing": 0,
    "missing_list": [],
    "missing_skill_improved": [],
    "note": "比對原版 mudchina/es2 的 daemon/skill/ 目錄"
  },
  "areas": {
    "required": 0,
    "implemented": 0,
    "missing": 0,
    "missing_from_original": [],
    "note": "比對原版 mudchina/es2 的 d/ 目錄"
  },
  "missing_rooms": [],
  "missing_npcs": [],
  "missing_quests": [],
  "missing_help_texts": [],
  "missing_equipment": []
}
```

---

### Step 4：產生實作進度報告

輸出 `docs/implementation_log.md`，包含：
- 各類別完成度百分比
- 已實作項目清單
- 待實作項目清單（按優先順序）
- 與原版 ES2 的差異分析

---

## 完成條件

- [ ] `docs/wiki_content.json` 建立完成
- [ ] `docs/missing_content.json` 建立完成
- [ ] `docs/implementation_log.md` 建立完成
- [ ] 在終端機輸出總結摘要

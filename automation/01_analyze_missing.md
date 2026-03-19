# Agent Task 01：分析缺少的內容

## 目標

掃描目前 mudlib 的現有內容，與 ES2 wiki 資料比對，
產生完整的待實作清單。

---

## 執行步驟

### Step 1：爬取 Wiki 資料

爬取以下所有頁面，儲存到 `docs/wiki_content.json`：

```
https://sites.google.com/site/es2mud/home/zhu-xian-ren-wu
https://sites.google.com/site/es2mud/home/story-lines/mythology
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
https://sites.google.com/site/es2mud/home/story-lines/zhong-zu-she-ding/guo-jia-de-tu
https://sites.google.com/site/es2mud/home/story-lines/zhong-zu-she-ding/tian-chao-de-tu
https://sites.google.com/site/es2mud/home/story-lines/zhong-zu-she-ding/tian-chao-de-tu/wutang
https://sites.google.com/site/es2mud/home/story-lines/zhong-zu-she-ding/tian-chao-de-tu/xueting
https://sites.google.com/site/es2mud/home/story-lines/zhi-ye-yu-men-pai/he-shang
https://sites.google.com/site/es2mud/home/story-lines/zhi-ye-yu-men-pai/xiao-tou
https://sites.google.com/site/es2mud/home/story-lines/zhi-ye-yu-men-pai/fang-shi
https://sites.google.com/site/es2mud/home/story-lines/zhi-ye-yu-men-pai/shu-sheng
https://sites.google.com/site/es2mud/home/story-lines/zhi-ye-yu-men-pai/wu-zhe
https://sites.google.com/site/es2mud/home/story-lines/zhi-ye-yu-men-pai/jun-ren
https://sites.google.com/site/es2mud/home/story-lines/zhi-ye-yu-men-pai/dao-shi
https://sites.google.com/site/es2mud/home/wan-jia-yuan-chuang/equipment
https://sites.google.com/site/es2mud/home/wan-jia-yuan-chuang/tiandiling
https://sites.google.com/site/es2mud/home/you-xi-jie-zi/noobguide01
https://sites.google.com/site/es2mud/home/you-xi-jie-zi/noobguide02
```

輸出格式（`docs/wiki_content.json`）：
```json
{
  "races": [
    {
      "id": "human",
      "name": "人類",
      "karma_cost": 5,
      "description": "...",
      "lore": "..."
    }
  ],
  "classes": [
    {
      "id": "warrior",
      "name": "武者",
      "description": "..."
    }
  ],
  "sects": [
    {
      "id": "fengshan",
      "name": "封山派",
      "class": "warrior",
      "description": "..."
    }
  ],
  "towns": [
    {
      "id": "snow",
      "name": "雪亭鎮",
      "rooms": [],
      "npcs": [],
      "quests": []
    }
  ],
  "equipment": [],
  "mythology": "..."
}
```

---

### Step 2：掃描現有 mudlib 內容

掃描以下目錄，列出所有已實作的 .c 檔案：

```bash
find mudlib/d/ -name "*.c" | sort
find mudlib/daemon/ -name "*.c" | sort
find mudlib/obj/ -name "*.c" | sort
find mudlib/doc/help/player/ -type f | sort
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
  "missing_rooms": [],
  "missing_npcs": [],
  "missing_quests": [],
  "missing_help_texts": []
}
```

---

### Step 4：產生實作進度報告

輸出 `docs/implementation_log.md`

---

## 完成條件

- [ ] `docs/wiki_content.json` 建立完成
- [ ] `docs/missing_content.json` 建立完成
- [ ] `docs/implementation_log.md` 建立完成
- [ ] 在終端機輸出總結摘要

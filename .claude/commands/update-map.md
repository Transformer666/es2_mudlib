掃描所有房間的出口連接，自動生成世界地圖文字檔。

## 步驟

1. 用 Bash 掃描所有房間的 exits：
```bash
for f in $(find mudlib/d/ -name "*.c" ! -path "*/npc/*" ! -path "*/obj/*"); do
  area=$(echo "$f" | sed 's|mudlib/d/||;s|/.*||')
  room=$(basename "$f" .c)
  short=$(grep 'set("short"' "$f" | head -1 | sed 's/.*set("short", "//;s/".*//')
  exits=$(grep -A20 '"exits"' "$f" | grep '"' | grep ':' | sed 's/.*"\([^"]*\)".*/\1/g' | paste -sd',' -)
  echo "$area/$room|$short|$exits"
done
```

2. 用 Grep 找出所有區域之間的連接（跨 d/ 子目錄的 exit）

3. 根據掃描結果，用 ASCII 畫出世界地圖，格式如下：
```
                    ┌─────────┐
                    │ 天山山脈 │
                    └────┬────┘
                         │ south
                    ┌────┴────┐
       ┌────────────┤ 雪亭鎮  ├──────────┐
       │ west       │ 12 rooms│ east     │
  ┌────┴────┐      └────┬────┘    ┌────┴────┐
  │ 振武軍營 │           │ se      │ 李家村  │
  │ 6 rooms │      ┌────┴────┐   │ 3 rooms │
  └────┬────┘      │ 老松林  │   └─────────┘
       │ south     │ 5 rooms │
  ┌────┴────┐      └────┬────┘
  │ 五堂鎮  │           │ south
  │ 15 rooms│      ┌────┴────┐
  └────┬────┘      │  喬陰   │
       │ sw        │ 8 rooms │
       └───────────┴─────────┘
```

每個區域方塊顯示：
- 區域中文名
- 房間數量
- NPC 數量
- 連接方向

4. 在地圖底部加上統計：
```
=== 統計 ===
總區域數: N
總房間數: N
總 NPC 數: N
渡船路線: lijun↔ferry_south, wutang↔ferry_south
復活點: snow/small_temple, wutang/temple, choyin/temple, ...
```

5. 寫入 `docs/world_map.txt`

6. 如果 `docs/world_map.txt` 已存在，比對差異，顯示新增/刪除的連接

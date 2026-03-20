根據指定的區域建立房間。

## 輸入

$ARGUMENTS = 區域名稱（如 "longan" 或 "龍安"）

## 步驟

1. 讀取 `automation/wiki_reference.md` 中該區域相關段落
2. 讀取 `automation/CLAUDE.md` 的「世界地圖」段落，確認該區域的地理位置
3. 讀取 `automation/CLAUDE.md` 的「一般房間 (Room)」和「客棧房間 (INN)」範本
4. 掃描 `mudlib/d/$ARGUMENTS/` 目錄，列出已有的房間
5. 根據區域類型（城鎮/門派HQ/野外）決定需要哪些房間：
   - 城鎮：廣場、街道、客棧、商店、廟、城門
   - 門派HQ：大門、大廳、練武場、掌門室、弟子宿舍
   - 野外：入口、小路、空地、特殊地點
6. 建立缺少的房間，確保：
   - `inherit ROOM`（客棧用 `inherit INN`）
   - `set("short", ...)` + `set("long", @LONG...LONG)`
   - `set("exits", ([...]))` 所有出口雙向連結
   - `setup()` + `replace_program(ROOM)`（無自訂函數時）
   - 城隍廟用 `inherit TEMPLE`（需 `#include <room.h>`）
7. 驗證所有出口雙向可達
8. 輸出建立了哪些檔案

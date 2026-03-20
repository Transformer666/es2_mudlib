根據描述建立裝備。

## 輸入

$ARGUMENTS = 裝備名稱或描述（如 "蔑天劍" 或 "sword for fengshan"）

## 步驟

1. 讀取 `automation/CLAUDE.md` 的武器/防具範本和數值範圍表
2. 如果是 blog 提到的裝備，搜尋對應 URL 取得屬性
3. 判斷類型：

### 武器
- `#include <weapon.h>` + `inherit F_SWORD/F_BLADE/F_DAGGER/...`
- `setup_<type>(min, max, wc, reach)` 數值須在合理範圍內
- `set("wield_as", ({"type"}))` + `set("unit", "量詞")`
- NPC 攜帶的放 `d/<area>/npc/obj/`，傳奇武器放 `obj/weapon/`

### 防具
- `#include <armor.h>` + `inherit F_CLOTH/F_ARMOR/F_HEAD_EQ/...`
- `setup_<type>()` + `set("wear_as", "type")`
- `set("apply_armor/<type>", (["armor": N]))`
- NPC 攜帶的放 `d/<area>/npc/obj/`，傳奇防具放 `obj/armor/`

4. 都要有 `!clonep()` 包裹描述屬性
5. 都要有 `setup()` 結尾
6. 輸出建立的檔案和屬性

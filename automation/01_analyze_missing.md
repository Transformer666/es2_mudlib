# Agent Task 01：分析缺少的內容

## 目標

掃描目前 mudlib 的現有內容，與 ES2 wiki 資料及原版 ES2 mudlib 比對，
產生完整的待實作清單。

---

## 前置參考

**必讀**：`automation/wiki_reference.md` — 已整理的 Wiki 完整資料，包含：
- 神話設定（十三靈、宇宙賭約）
- 歷史時間線（5000 年 → 現在）
- 11 種族完整數據（業力/屬性上限/精氣神/被動主動能力）
- 7 職業 × 18 門派完整對應表（含路線/推薦種族）
- 城鎮謎題（雪亭 7 謎 + 五堂 6 謎）
- 主線任務線索 + 天地靈任務攻略
- PvP 戰鬥紀錄

先讀取 `automation/wiki_reference.md` 取得結構化資料，
再爬取以下頁面補充細節或確認最新內容。

---

## 執行步驟

### Step 1：爬取 Wiki 及外部資料

先讀取 `automation/wiki_reference.md` 作為基礎資料。
再爬取以下頁面補充或更新，儲存到 `docs/wiki_content.json`：

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

#### 1B. 玩家攻略 Blog（es2tips.blogspot.com — 完整 120+ 篇）

爬取所有文章，重點提取：NPC 名稱/位置、裝備屬性、門派設定、任務流程、地圖資訊。

```
# === 新手指南 & 系統說明 ===
https://es2tips.blogspot.com/2013/05/es2-help.html                    # 新手必看 Help
https://es2tips.blogspot.com/2014/07/es2.html                         # 主機狀態查詢（置頂）
https://es2tips.blogspot.com/2014/02/es2.html                         # 如何投胎
https://es2tips.blogspot.com/2014/09/es2.html                         # 戰鬥攻擊防禦基本設定
https://es2tips.blogspot.com/2013/06/reset-skill.html                 # 技能重置 Reset Skill
https://es2tips.blogspot.com/2014/09/es2-1-2014-sept.html             # 使用者體驗提升想法

# === 練功 & 殺業 ===
https://es2tips.blogspot.com/2013/05/es2_29.html                      # 鍛鍊殺業
https://es2tips.blogspot.com/2014/10/mobnpc-swordbladepikeaxeneedlestaffunar.html  # 物理練功 Mob/NPC
https://es2tips.blogspot.com/2014/11/stakelionbuddhapillar.html       # 練功標靶 stake/lion/buddha/pillar
https://es2tips.blogspot.com/2014/08/train-stone-parry-backstab.html  # 試煉石 Train stone
https://es2tips.blogspot.com/2014/11/6-minutes-mob-4-minutes.html     # 撿裝備時間測試

# === 門派 & 職業設定 ===
# 道士系
https://es2tips.blogspot.com/2014/08/es2.html                         # 道士設定總覽
https://es2tips.blogspot.com/2014/08/es2_59.html                      # 道士進階、茅山劍士
https://es2tips.blogspot.com/2014/08/es2_47.html                      # 隱風觀 茅山道士（喚雨、算命）
https://es2tips.blogspot.com/2014/08/es2_71.html                      # 靈雲觀 茅山道士（五雷、幽冥三箭）
https://es2tips.blogspot.com/2014/08/es2_76.html                      # 幻霧觀 茅山道士（噬魂、通靈）
https://es2tips.blogspot.com/2014/08/es2_75.html                      # 紫衣派 道士（雷）
https://es2tips.blogspot.com/2014/08/es2_64.html                      # 素衣派 道士（冰）
https://es2tips.blogspot.com/2014/08/es2_85.html                      # 玄衣派 道士（風）
https://es2tips.blogspot.com/2014/08/es2_13.html                      # 朱衣派 道士（火）
https://es2tips.blogspot.com/2014/02/taoism-cloud.html                # 天師道法【素雲書】
https://es2tips.blogspot.com/2014/02/mao-shan-sword.html              # 茅山劍法
https://es2tips.blogspot.com/2014/02/mao-shan-taoist.html             # 茅山老道
https://es2tips.blogspot.com/2014/02/blog-post.html                   # 茅山道士/茅山派
https://es2tips.blogspot.com/2014/01/blog-post_31.html                # 茅山劍士
https://es2tips.blogspot.com/2015/11/blog-post_77.html                # 天師道士裝備與幻劍術
# 武者系
https://es2tips.blogspot.com/2014/08/blog-post_23.html                # 虎刀門護衛進階
https://es2tips.blogspot.com/2014/08/han-xiao.html                    # 虎刀門掌門 韓笑
https://es2tips.blogspot.com/2015/11/blog-post_7.html                 # 金剛鎚法穿靈效果
# 軍人系
https://es2tips.blogspot.com/2014/09/soldiers.html                    # 士兵/軍人
https://es2tips.blogspot.com/2014/09/soldier-berserker.html           # 振武軍營士兵
https://es2tips.blogspot.com/2014/09/soldier-royal.html               # 京畿大內巡院
https://es2tips.blogspot.com/2014/10/soldierber.html                  # 軍師：戰術兵法
https://es2tips.blogspot.com/2014/10/blog-post.html                   # 振武軍營轉軍師
https://es2tips.blogspot.com/2014/11/byun.html                        # 振武軍營軍師 必勇
# 方士系
https://es2tips.blogspot.com/2014/09/blog-post.html                   # 龍圖丹派方士
https://es2tips.blogspot.com/2014/09/blog-post_17.html                # 針灸師 武陀灸堂
https://es2tips.blogspot.com/2014/09/blog-post_27.html                # 方士/針灸師進階
https://es2tips.blogspot.com/2014/08/blog-post.html                   # 龍圖丹派醫師 江述仁
# 書生系
https://es2tips.blogspot.com/2014/08/int-21.html                      # 步玄居士悟性裝
https://es2tips.blogspot.com/2014/08/nmb48yamadanana.html             # 步玄派弟子

# === 門派師父位置 ===
https://es2tips.blogspot.com/2014/10/es2.html                         # 職業師父的位置

# === NPC & Boss 戰鬥 ===
https://es2tips.blogspot.com/2015/11/vs_7.html                        # 天師道士 vs 駱易
https://es2tips.blogspot.com/2015/11/blog-post_27.html                # 天師道士 vs 劉乙忘玄
https://es2tips.blogspot.com/2015/11/vs.html                          # 天師道士 vs 梅影風
https://es2tips.blogspot.com/2015/11/blog-post_49.html                # 天師道士 vs 柳東蘆
https://es2tips.blogspot.com/2015/11/blog-post.html                   # 大魔頭 李東靈
https://es2tips.blogspot.com/2015/11/es2-jpg.html                     # 夜叉吞鬼
https://es2tips.blogspot.com/2014/11/dslee.html                       # 雪吟莊棄徒 李東靈
https://es2tips.blogspot.com/2014/08/black-hell-agent.html            # 勾魂使者 黑無常
https://es2tips.blogspot.com/2014/08/white-hell-agent.html            # 勾魂使者 白無常
https://es2tips.blogspot.com/2013/06/vs-mob.html                      # 滅心/滅名/滅慾/神衛 vs 風神
https://es2tips.blogspot.com/2013/05/blog-post_29.html                # 虎刀門護衛 孫漪

# === 八寶樓系列（Boss + 裝備）===
https://es2tips.blogspot.com/2013/05/1-book.html                      # 八寶樓(1) 歐陽芝
https://es2tips.blogspot.com/2013/05/2_29.html                        # 八寶樓(2) 司馬雷
https://es2tips.blogspot.com/2013/05/3_29.html                        # 八寶樓(3) 崇白虎
https://es2tips.blogspot.com/2013/05/4.html                           # 八寶樓(4) 馬鍾聖
https://es2tips.blogspot.com/2013/05/5_29.html                        # 八寶樓(5) 公孫微
https://es2tips.blogspot.com/2013/05/6_29.html                        # 八寶樓(6) 天神地鬼
https://es2tips.blogspot.com/2013/05/7.html                           # 八寶樓(7) 施鈺
https://es2tips.blogspot.com/2013/05/8.html                           # 八寶樓(8) 劍皇

# === 裝備資料（武器）===
https://es2tips.blogspot.com/2014/11/dragon-whip.html                 # 毒龍鞭
https://es2tips.blogspot.com/2014/11/lightning-bomb.html               # 霹靂雷火彈
https://es2tips.blogspot.com/2014/11/staff-of-eroticism-huge.html     # 交歡杖
https://es2tips.blogspot.com/2014/11/green-blade.html                 # 蕭尹：玉戒尺
https://es2tips.blogspot.com/2014/11/golden-beast-lance.html          # 金龍豹紋槍
https://es2tips.blogspot.com/2014/10/sword-of-killing-god.html        # 蔑天劍
https://es2tips.blogspot.com/2014/08/rapid-sword.html                 # 疾風劍
https://es2tips.blogspot.com/2014/08/essence-of-fish-psychic-sword.html  # 河魚腹珠 & 靈通劍
https://es2tips.blogspot.com/2014/03/jade-rod.html                    # 寒玉藥杵
https://es2tips.blogspot.com/2014/03/blog-post.html                   # 清風刀 血匕封喉等
https://es2tips.blogspot.com/2014/02/mirror-of-gods-black-spark.html  # 封神寶鏡+離玄光熾
https://es2tips.blogspot.com/2014/02/stange-copper-staff-celestial-bull-cane.html  # 玄烏杖+饕餮法杖
https://es2tips.blogspot.com/2014/02/loving-sword-silky-gloves.html   # 歸心似劍
https://es2tips.blogspot.com/2014/02/white-sword.html                 # 白色長劍
https://es2tips.blogspot.com/2014/01/staff-of-ancient-snow.html       # 萬年雪
https://es2tips.blogspot.com/2014/01/thunder-claw.html                # 雷熊爪
https://es2tips.blogspot.com/2013/08/blog-post_3785.html              # 藍涎刀
https://es2tips.blogspot.com/2013/08/blog-post_9762.html              # 藥王神劍
https://es2tips.blogspot.com/2013/08/blog-post_8637.html              # 易羅大劍
https://es2tips.blogspot.com/2013/08/blog-post_8.html                 # 鬼頭劈象刀
https://es2tips.blogspot.com/2013/08/blog-post_4.html                 # 雪魂匕
https://es2tips.blogspot.com/2013/07/blog-post.html                   # 追月流星劍
https://es2tips.blogspot.com/2013/07/liuye.html                       # 邪門歪刀
https://es2tips.blogspot.com/2013/06/blog-post_3.html                 # 天都劍 水月劍
https://es2tips.blogspot.com/2013/06/image.html                       # 天命刃 天靈 穹氤
https://es2tips.blogspot.com/2013/05/blog-post_2462.html              # 風雷刀等8把武器
https://es2tips.blogspot.com/2014/10/dragon-needle.html               # 盤龍針
https://es2tips.blogspot.com/2014/10/gin-pike.html                    # 紫金鳳頭錐
https://es2tips.blogspot.com/2014/10/seal-of-chaos-broken-seal.html   # 混沌之印
https://es2tips.blogspot.com/2014/01/blog-post_6513.html              # 追風劍+霹靂雷火彈
https://es2tips.blogspot.com/2014/01/blog-post_3410.html              # 六靈妖姬鞭
https://es2tips.blogspot.com/2014/01/blog-post_7305.html              # 古刃旋芒

# === 裝備資料（防具 & 飾品）===
https://es2tips.blogspot.com/2014/11/dragon-armor-staff-huge-or-parrydodge.html  # 怒龍錦冑
https://es2tips.blogspot.com/2014/11/soul-crystal.html                # 靈魂水晶
https://es2tips.blogspot.com/2014/11/blessed-jade.html                # 萬福寶玉
https://es2tips.blogspot.com/2014/11/dragon-bone.html                 # 靈骨
https://es2tips.blogspot.com/2014/08/skull-rosary.html                # 白骨念珠
https://es2tips.blogspot.com/2014/08/dragon-soul-ring.html            # 龍戒
https://es2tips.blogspot.com/2014/08/corrosive-hands.html             # 腐蝕之手
https://es2tips.blogspot.com/2014/03/symbol-of-dao.html               # 邪骨指環
https://es2tips.blogspot.com/2014/03/jin-ju.html                      # 九天鳳珠
https://es2tips.blogspot.com/2014/02/rainnar-cloth-ashura-mask.html   # 雨師妾袍+修羅之面
https://es2tips.blogspot.com/2014/02/girdle-of-headless.html          # 形天之怒
https://es2tips.blogspot.com/2014/01/topaz-belt.html                  # 黃玉佩
https://es2tips.blogspot.com/2014/01/blog-post_29.html                # 巫首項鍊
https://es2tips.blogspot.com/2014/01/blog-post_4623.html              # 冷雪手護+雲羅絲衣
https://es2tips.blogspot.com/2014/01/woochan-ring.html                # 無腸寶珠
https://es2tips.blogspot.com/2014/01/dingling-legs.html               # 釘靈腿護
https://es2tips.blogspot.com/2014/01/jiaojaos-boots.html              # 焦僥靴
https://es2tips.blogspot.com/2014/01/yenhold-gauntlets.html           # 厭火之拳
https://es2tips.blogspot.com/2014/01/blog-post_29.html                # 巫首項鍊
https://es2tips.blogspot.com/2013/08/blog-post_9676.html              # 雷火天狼罩
https://es2tips.blogspot.com/2013/08/blog-post.html                   # 龍思羽+封印冰環
https://es2tips.blogspot.com/2013/07/blog-post_29.html                # 鱷神系列裝備
https://es2tips.blogspot.com/2013/06/super-skin.html                  # 混元一氣袋
https://es2tips.blogspot.com/2013/06/blog-post_15.html                # 白熊系列裝備
https://es2tips.blogspot.com/2013/05/blog-post_30.html                # 青銅/鐵棘等21件裝備總覽
https://es2tips.blogspot.com/2013/05/blog-post_493.html               # 封印雷環+穿靈等12件
https://es2tips.blogspot.com/2013/06/blog-post_4.html                 # 舞璃戒指

# === 地點 & NPC ===
https://es2tips.blogspot.com/2014/03/blog-post_7114.html              # ES2 地圖（大略相對位置）
https://es2tips.blogspot.com/2014/03/blog-post_2376.html              # 域水客棧（天寒村）
https://es2tips.blogspot.com/2014/11/blog-post_4.html                 # 書：用書換符紙
https://es2tips.blogspot.com/2014/11/es2.html                         # 書：名山書肆等地點
https://es2tips.blogspot.com/2014/11/str-5.html                       # 買道具的兩個地方
https://es2tips.blogspot.com/2014/11/blog-post.html                   # 聲望：京畿神社功德箱
https://es2tips.blogspot.com/2014/02/fortune-teller-teller-zhang-fortune.html  # 算命先生位置
https://es2tips.blogspot.com/2014/02/pot-well-bucket.html             # 常見水缸/水井/大水桶
https://es2tips.blogspot.com/2014/02/es.html                          # 常見當鋪
https://es2tips.blogspot.com/2014/02/es2_3.html                       # 坐船+釣魚地點
https://es2tips.blogspot.com/2013/05/es2.html                         # 鬼魂常出現的地方

# === 任務 & 劇情 ===
https://es2tips.blogspot.com/2014/10/beggar-crone-maro-dagger-watermelon.html  # 老乞婆任務
https://es2tips.blogspot.com/2013/05/blog-post_7503.html              # 任蕭蕭任務支線
https://es2tips.blogspot.com/2013/05/blog-post_5878.html              # 八穴鬼徑走法
https://es2tips.blogspot.com/2014/02/blog-post_8.html                 # 神之心打法
https://es2tips.blogspot.com/2013/06/blog-post_7143.html              # 混沌之印+混沌獸
https://es2tips.blogspot.com/2013/05/blog-post_4347.html              # 龍安鎮+黑龍+九轉異龍珠
https://es2tips.blogspot.com/2013/05/blog-post_2986.html              # 百藥谷：赤龍+封山
https://es2tips.blogspot.com/2013/05/blog-post_9262.html              # 大蜈蚣+聖木殘根
https://es2tips.blogspot.com/2013/05/seal.html                        # 風神+風之印記

# === 上古妖獸 ===
https://es2tips.blogspot.com/2014/11/blog-post_9.html                 # 上古妖獸8隻總覽
https://es2tips.blogspot.com/2014/11/art-concept-inferno-dog-ritual-monkey.html  # 妖獸美術概念

# === 玩家角色紀錄 ===
https://es2tips.blogspot.com/2014/03/boyo.html                        # 虎刀門弟子 博佑
https://es2tips.blogspot.com/2014/03/cclai.html                       # 黑龍左使 你好
https://es2tips.blogspot.com/2014/03/vvcheng.html                     # 龍圖丹派弟子 鄭兩兩
https://es2tips.blogspot.com/2014/03/spinlocks.html                   # 寶蓮寺弟子 善想
https://es2tips.blogspot.com/2014/03/polynomial.html                  # 天月庵弟子 poly
https://es2tips.blogspot.com/2014/03/gigiyiyi.html                    # 茅山真人 擊耀
https://es2tips.blogspot.com/2014/03/spinlock.html                    # 白象寺羅漢 史賓
https://es2tips.blogspot.com/2014/10/gfmul.html                       # 紫衣派道士 雷道
https://es2tips.blogspot.com/2014/10/liu-ke.html                      # 劉可角色裝備

# === 聲望 & 門派仇恨 ===
https://es2tips.blogspot.com/2013/05/blog-post_6121.html              # 黑道/武林/青邪/戰場聲望
https://es2tips.blogspot.com/2014/11/vs.html                          # 會結仇 vs 不會結仇的派別
https://es2tips.blogspot.com/2013/06/1.html                           # 黑道聲望(1) 裝備
https://es2tips.blogspot.com/2013/06/2.html                           # 黑道聲望(2) 裝備
https://es2tips.blogspot.com/2013/06/3.html                           # 黑道聲望(3) 裝備
https://es2tips.blogspot.com/2014/08/equalizer.html                   # 毒刀胡惑 解除仇恨

# === 其他系統 ===
https://es2tips.blogspot.com/2014/10/blog-post_29.html                # 水神天龍走法
https://es2tips.blogspot.com/2014/02/blog-post_26.html                # 江湖藝人 張小簽
https://es2tips.blogspot.com/2014/02/blog-post_23.html                # 幫包包加標籤
https://es2tips.blogspot.com/2014/02/ghosts.html                      # 各種鬼魂
https://es2tips.blogspot.com/2014/10/blog-post_28.html                # 各種中毒症狀
https://es2tips.blogspot.com/2013/05/es2-tintin-automatic-duel.html   # 自動擂台比武
https://es2tips.blogspot.com/2014/07/es2-expect-script.html           # 防砍檔自動登入 Expect
https://es2tips.blogspot.com/2013/06/blog-post_9349.html              # 四鬼招喚法
https://es2tips.blogspot.com/2013/05/blog-post_882.html               # 食物：紅燒雞等
https://es2tips.blogspot.com/2013/05/blog-post_28.html                # 文國縣天風客棧食物
https://es2tips.blogspot.com/2013/06/blog-post_9707.html              # 水龍經換奇兵精意
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

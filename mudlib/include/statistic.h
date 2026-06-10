// statistic.h

#ifndef __STATISTIC_H__
#define __STATISTIC_H__

#define NUM_STATISTICS		4

#define TYPE_STATIC		0
#define TYPE_HEALTH		1
#define TYPE_WASTING	2

// prototypes

mapping query_exhausted();
mapping query_destroyed();
mapping query_notified();
void clear_statistic_flags();

int query_stat(string what);
// 下三式回傳型別須與 feature/statistic.c 實作一致為 mixed：呼叫端以 undefinedp()
// 區分「stat 未定義」與「stat==0」，undefined 必須能穿透。型別不符會讓玩家在
// 建角/update 首次編譯時看到 "Return type doesn't match prototype" 警告。
mixed query_stat_current(string what);
mixed query_stat_effective(string what);
mixed query_stat_maximum(string what);
mixed query_stat_regenerate(string what);
int set_stat_current(string what, int val);
int set_stat_effective(string what, int val);
int set_stat_maximum(string what, int val);
mixed set_stat_regenerate(string what, mixed val);
void start_regenerate();
varargs int consume_stat(string type, int damage, object who);
varargs int damage_stat(string type, int damage, object who);
int supplement_stat(string type, int heal);
int heal_stat(string type, int heal);
int health_regenerator(object me, string stat, int max, int eff, int cur);
int wasting_regenerator(object me, string stat, int max, int eff, int cur);

#endif

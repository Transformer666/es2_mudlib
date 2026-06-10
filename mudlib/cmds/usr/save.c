

#include <login.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
    object link_ob;
    int last_save, delta_t;
    
    seteuid(getuid());

    if( !objectp(link_ob = me->link()) )
        return notify_fail("你不是經由正常連線進入﹐不能儲存。\n");

    if( environment(me)->query("valid_startroom") ) {
        me->set("startroom", base_name(environment(me)));
        write("當你下次連線進來時﹐會從這裡開始。\n");
    }

    if( !wizardp(me)
    &&  (last_save = me->query_temp("last_save"))
    &&  (delta_t = (time()/60 - last_save)) < 1 ) {
        return notify_fail("不用急, 1 分鐘內只能儲存一次。\n");
    }

#ifdef SAVE_USER
    if( (int)me->save() ) {
        write("檔案儲存完畢。\n");
        me->set_temp("last_save", (int)(time()/60) );
        return 1;
    } else {
        write("儲存失敗。\n");
        return 0;
    }
#else
    return notify_fail("系統目前不儲存使用者資料。\n");
#endif
}

int help(object me)
{
    write(@HELP
指令格式﹕save

把你辛苦奮鬥的結果存起來。為了提升系統效率, 目前兩次 save 之時間間距最短為
一分鐘。系統每隔數分鐘也會自動幫你存檔, quit、死亡、斷線時亦會自動 save。
see also: quit, backup
HELP
    );
    return 1;
}


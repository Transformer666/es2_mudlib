

#include <login.h>
#include <ansi.h>
inherit F_CLEAN_UP;

varargs int clan_line(string msg,int emote);

int main(object me, string arg)
{
    object who, obj;
    string target;

    // function 1: check all clans
    if( !arg ) {
	seteuid( getuid() );
	write("目前已有的幫派如下: \n\n");
        write( CLAN_D->list_clans() );
	write("\n欲加入一個幫派請找長老級以上玩家申請加入幫派。\n");
	return 1;
    }

    seteuid( getuid() );

    // function 2: verify - get clan symbol for a clan member
    if( arg == "verify" ) {	
	if( !me->query("clan/clan_name") ) 
	    return notify_fail("你並非幫派成員。\n");
	if( !present("clan symbol", me) ) {
	    obj = new("/obj/clan_symbol");
	    tell_object(me, "你得到一個新的幫派信物。\n");
	    obj->move(me);
	    return 1; }
	else return notify_fail("你已經有一個信物了。\n");
    }

    // function 3: leave - leave this clan
    if( arg == "leave" ) {
	if( me->query("clan/clan_level") > 1 )
	    return notify_fail("請先把職位降至一般幫眾。\n");
	log_file("CLAN",sprintf("[%s] %s: %s(%s) leaves\n",
	    ctime(time()), me->query("clan/clan_name"), me->name(),
	    me->query("id")) );
	clan_line("本人宣佈, 即刻起退出" + me->query("clan/clan_name")
	    + "。\n");
	// 自中央幫派 daemon 移除本人 (在刪除玩家 clan/* 快取之前先取得幫名)。
	CLAN_D->remove_member(me->query("clan/clan_name"), me->query("id"));
	me->delete("clan/clan_name");
	me->delete("clan/clan_level");
	me->delete("clan/nick");
	me->delete("clan/rank");
	if( obj = present("clan symbol", me) )
	    destruct(obj);
#ifdef SAVE_USER
	me->save();
#endif
	return 1;
    }

    // function: treasury - 查詢本幫金庫餘額 (任何幫眾皆可)。
    if( arg == "treasury" ) {
	if( !me->query("clan/clan_name") )
	    return notify_fail("你並非幫派成員。\n");
	write(HIY"【"+me->query("clan/clan_name")+"】金庫目前餘額: "
	    + CLAN_D->query_treasury(me->query("clan/clan_name"))
	    + " 文。\n"NOR);
	return 1;
    }

    // function: status - 一覽本幫的交戰 / 結盟 / 領地狀態 (任何幫眾皆可)。
    // (Phase-3) 無參數子指令，故置於 sscanf 切割之前 (同 treasury)。
    if( arg == "status" ) {
	string clan;
	string *wars, *allies, *terr;
	int j;

	if( !me->query("clan/clan_name") )
	    return notify_fail("你並非幫派成員。\n");
	clan = me->query("clan/clan_name");
	wars   = CLAN_D->query_wars(clan);
	allies = CLAN_D->query_allies(clan);
	terr   = CLAN_D->query_territory(clan);
	write(HIY"【"+clan+"】幫派現況\n"NOR);
	write(HIR"  交戰: "NOR
	    + (sizeof(wars) ? implode(wars, "、") : "（無，天下太平）") + "\n");
	for( j = 0; j < sizeof(wars); j++ )
	    write(sprintf("        對【%s】戰功累計 %d 筆\n",
		wars[j], CLAN_D->query_war_score(clan, wars[j])));
	write(HIG"  結盟: "NOR
	    + (sizeof(allies) ? implode(allies, "、") : "（無）") + "\n");
	write(HIC"  領地: "NOR
	    + (sizeof(terr) ? implode(terr, "、") : "（無）") + "\n");
	return 1;
    }

    // function: territory - 列出本幫所有領地 (任何幫眾皆可)。
    if( arg == "territory" ) {
	string clan;
	string *terr;

	if( !me->query("clan/clan_name") )
	    return notify_fail("你並非幫派成員。\n");
	clan = me->query("clan/clan_name");
	terr = CLAN_D->query_territory(clan);
	if( !sizeof(terr) ) {
	    write(HIC"【"+clan+"】目前尚未占據任何領地。\n"NOR);
	    return 1;
	}
	write(HIC"【"+clan+"】目前的勢力範圍:\n"NOR);
	write("  " + implode(terr, "\n  ") + "\n");
	return 1;
    }

    // following function should classify function name
    if( sscanf(arg, "%s %s", arg, target)!=2 )
	return notify_fail("請用help ccmd查詢正確的指令格式。\n");

    // function: deposit - 任何幫眾把身上的錢存入金庫。
    // (置於 find_player 之前: 參數為金額/稱號而非玩家 id)
    if( arg == "deposit" ) {
	int amount;
	string clan;

	if( !me->query("clan/clan_name") )
	    return notify_fail("你並非幫派成員。\n");
	clan = me->query("clan/clan_name");
	if( sscanf(target, "%d", amount) != 1 || amount <= 0 )
	    return notify_fail("指令格式: ccmd deposit <金額>。\n");
	if( (int)me->can_afford(amount) != 1 )
	    return notify_fail("你身上沒有這麼多現錢﹐或湊不出整數。\n");
	me->pay_money(amount);
	CLAN_D->deposit(clan, amount);
	log_file("CLAN", sprintf("[%s] %s: %s(%s) deposits %d\n",
	    ctime(time()), clan, me->name(), me->query("id"), amount));
	clan_line(me->name() + "存入金庫 " + amount + " 文﹐金庫餘額 "
	    + CLAN_D->query_treasury(clan) + " 文。\n");
	return 1;
    }

    // function: withdraw - 幫主/長老(職等>=2) 自金庫提錢入袋。
    if( arg == "withdraw" ) {
	int amount;
	string clan;
	object coin;

	if( !me->query("clan/clan_name") )
	    return notify_fail("你並非幫派成員。\n");
	clan = me->query("clan/clan_name");
	if( me->query("clan/clan_level") < 2 )
	    return notify_fail("只有長老級以上才能動用金庫。\n");
	if( sscanf(target, "%d", amount) != 1 || amount <= 0 )
	    return notify_fail("指令格式: ccmd withdraw <金額>。\n");
	if( CLAN_D->query_treasury(clan) < amount )
	    return notify_fail("金庫裡沒有這麼多錢。\n");

	// 給玩家錢: clone 一份 coin、設額、move 進玩家身上
	// (combined.c::move 會與身上既有 coin 自動合併)。
	seteuid( getuid() );
	coin = new("/obj/money/coin");
	coin->set_amount(amount);
	if( !coin->move(me) ) {
	    destruct(coin);
	    return notify_fail("你身上帶不了這許多錢﹐提少一點吧。\n");
	}
	// 入袋成功才自金庫扣款 (withdraw 失敗會回 -1﹐理應已被上面餘額檢查擋掉)。
	if( CLAN_D->withdraw(clan, amount) < 0 ) {
	    // 理論上不會發生: 防守性回補並退回剛給的錢。
	    if( coin = present("coin_money", me) )
		coin->add_amount( - amount );
	    return notify_fail("金庫餘額不足﹐提領失敗。\n");
	}
	log_file("CLAN", sprintf("[%s] %s: %s(%s) withdraws %d\n",
	    ctime(time()), clan, me->name(), me->query("id"), amount));
	clan_line(me->name() + "自金庫提出 " + amount + " 文﹐金庫餘額 "
	    + CLAN_D->query_treasury(clan) + " 文。\n");
	return 1;
    }

    // function: rank - 幫主(職等3) 重新命名某職等的階級稱號。
    if( arg == "rank" ) {
	int level;
	string title, clan;

	if( !me->query("clan/clan_name") )
	    return notify_fail("你並非幫派成員。\n");
	clan = me->query("clan/clan_name");
	if( me->query("clan/clan_level") < 3 )
	    return notify_fail("只有幫主才能更改階級稱號。\n");
	if( sscanf(target, "%d %s", level, title) != 2 )
	    return notify_fail("指令格式: ccmd rank <職等1~3> <稱號>。\n");
	if( level < 1 || level > 3 )
	    return notify_fail("職等只能是 1(幫眾)、2(長老) 或 3(幫主)。\n");
	// >12 bytes ≈ >4 漢字。原 cestablish 曾用 strlen>4(byte) 誤拒 2 字中文(各 6 bytes)﹐此處改用 12 放行 4 漢字。
	if( strlen(title) > 12 )
	    return notify_fail("稱號過長﹐請用四個漢字以內。\n");
	if( !CLAN_D->set_rank_title(clan, level, title) )
	    return notify_fail("更改階級稱號失敗。\n");
	log_file("CLAN", sprintf("[%s] %s: %s(%s) renames rank %d to %s\n",
	    ctime(time()), clan, me->name(), me->query("id"), level, title));
	clan_line("本幫職等" + level + "的稱號即刻起改為「" + title + "」。\n");
	return 1;
    }

    // ======================================================================
    // Phase-3 (decision D)：幫戰(war/peace)、結盟(ally/unally)、領地(claim)。
    //
    // 這幾個子指令的 <target> 是「幫派名稱」(war/peace/ally/unally) 或
    // 「領地名稱」(claim)，而非玩家 id，故全部置於下方 find_player(target)
    // 之前處理 (與 deposit/withdraw/rank 同列)。權限一律限幫主 (clan_level==3)。
    // 實際狀態變動全部委派給 CLAN_D，本檔只做權限與輸入檢查、廣播與記錄。
    // ======================================================================

    // function: war - 幫主向另一個幫派宣戰，雙方進入交戰狀態。
    if( arg == "war" ) {
	string clan;

	if( !me->query("clan/clan_name") )
	    return notify_fail("你並非幫派成員。\n");
	clan = me->query("clan/clan_name");
	if( me->query("clan/clan_level") < 3 )
	    return notify_fail("只有幫主才能對外宣戰。\n");
	if( target == clan )
	    return notify_fail("總不能對自己的幫派宣戰吧?\n");
	if( !CLAN_D->query_clan(target) )
	    return notify_fail("江湖上並無「" + target + "」這個幫派。\n");
	if( CLAN_D->query_war(clan, target) )
	    return notify_fail("本幫與【" + target + "】早已是交戰之局了。\n");
	if( CLAN_D->query_ally(clan, target) )
	    return notify_fail("【" + target
		+ "】是本幫盟友，要宣戰請先以 ccmd unally "
		+ target + " 解除盟約。\n");
	if( !CLAN_D->declare_war(clan, target) )
	    return notify_fail("宣戰失敗。\n");
	log_file("CLAN", sprintf("[%s] %s: %s(%s) declares WAR on %s\n",
	    ctime(time()), clan, me->name(), me->query("id"), target));
	clan_line(HIR"本幫即刻起向【" + target + "】宣戰! 凡我幫眾，"
	    "於戰場上格殺該幫之人乃是正當幫戰，不論紅黑!\n"NOR);
	message("system", HIR"天朝公告: 【" + clan + "】向【" + target
	    + "】宣戰，江湖再起波瀾!\n"NOR, users());
	return 1;
    }

    // function: peace - 幫主與另一個交戰中的幫派休戰。
    if( arg == "peace" ) {
	string clan;

	if( !me->query("clan/clan_name") )
	    return notify_fail("你並非幫派成員。\n");
	clan = me->query("clan/clan_name");
	if( me->query("clan/clan_level") < 3 )
	    return notify_fail("只有幫主才能議和休戰。\n");
	if( !CLAN_D->query_clan(target) )
	    return notify_fail("江湖上並無「" + target + "」這個幫派。\n");
	if( !CLAN_D->query_war(clan, target) )
	    return notify_fail("本幫與【" + target + "】並未交戰，何來休戰?\n");
	if( !CLAN_D->end_war(clan, target) )
	    return notify_fail("休戰失敗。\n");
	log_file("CLAN", sprintf("[%s] %s: %s(%s) makes PEACE with %s\n",
	    ctime(time()), clan, me->name(), me->query("id"), target));
	clan_line(HIG"本幫即刻起與【" + target + "】休戰，干戈暫息。\n"NOR);
	message("system", HIG"天朝公告: 【" + clan + "】與【" + target
	    + "】握手言和，刀兵入庫。\n"NOR, users());
	return 1;
    }

    // function: ally - 幫主與另一個幫派結盟 (雙方狀態)。
    if( arg == "ally" ) {
	string clan;

	if( !me->query("clan/clan_name") )
	    return notify_fail("你並非幫派成員。\n");
	clan = me->query("clan/clan_name");
	if( me->query("clan/clan_level") < 3 )
	    return notify_fail("只有幫主才能與他幫結盟。\n");
	if( target == clan )
	    return notify_fail("自己跟自己結什麼盟?\n");
	if( !CLAN_D->query_clan(target) )
	    return notify_fail("江湖上並無「" + target + "」這個幫派。\n");
	if( CLAN_D->query_ally(clan, target) )
	    return notify_fail("本幫與【" + target + "】早已是盟友了。\n");
	if( CLAN_D->query_war(clan, target) )
	    return notify_fail("本幫正與【" + target
		+ "】交戰，要結盟請先以 ccmd peace "
		+ target + " 休戰。\n");
	if( !CLAN_D->add_ally(clan, target) )
	    return notify_fail("結盟失敗。\n");
	log_file("CLAN", sprintf("[%s] %s: %s(%s) allies with %s\n",
	    ctime(time()), clan, me->name(), me->query("id"), target));
	clan_line(HIG"本幫即刻起與【" + target + "】結為盟友，守望相助!\n"NOR);
	message("system", HIG"天朝公告: 【" + clan + "】與【" + target
	    + "】締結盟約!\n"NOR, users());
	return 1;
    }

    // function: unally - 幫主解除與某盟友幫派的盟約。
    if( arg == "unally" ) {
	string clan;

	if( !me->query("clan/clan_name") )
	    return notify_fail("你並非幫派成員。\n");
	clan = me->query("clan/clan_name");
	if( me->query("clan/clan_level") < 3 )
	    return notify_fail("只有幫主才能解除盟約。\n");
	if( !CLAN_D->query_clan(target) )
	    return notify_fail("江湖上並無「" + target + "」這個幫派。\n");
	if( !CLAN_D->query_ally(clan, target) )
	    return notify_fail("本幫與【" + target + "】並非盟友。\n");
	if( !CLAN_D->remove_ally(clan, target) )
	    return notify_fail("解除盟約失敗。\n");
	log_file("CLAN", sprintf("[%s] %s: %s(%s) unallies %s\n",
	    ctime(time()), clan, me->name(), me->query("id"), target));
	clan_line(HIY"本幫即刻起與【" + target + "】解除盟約。\n"NOR);
	return 1;
    }

    // function: claim - 幫主把一塊地域納入本幫領地。
    // 預設可宣示「腳下這間房間所在的地域」(target=="here")，或直接給地域名。
    // 領地先到先得：已被他幫占據者無法搶占 (CLAN_D->add_territory 會擋)。
    if( arg == "claim" ) {
	string clan, area, owner;

	if( !me->query("clan/clan_name") )
	    return notify_fail("你並非幫派成員。\n");
	clan = me->query("clan/clan_name");
	if( me->query("clan/clan_level") < 3 )
	    return notify_fail("只有幫主才能為本幫宣示領地。\n");
	// "here" → 取腳下房間所在的地域 (outdoors 標籤)，否則直接用所給名稱。
	if( target == "here" ) {
	    if( !environment(me) )
		return notify_fail("你現在這個地方無法宣示為領地。\n");
	    area = environment(me)->query("outdoors");
	    if( !stringp(area) || area == "" )
		area = base_name(environment(me));
	} else
	    area = target;
	owner = CLAN_D->query_territory_owner(area);
	if( owner == clan )
	    return notify_fail("「" + area + "」已是本幫的領地了。\n");
	if( stringp(owner) )
	    return notify_fail("「" + area + "」已被【" + owner
		+ "】占據，須待其釋出方能宣示。\n");
	if( !CLAN_D->add_territory(clan, area) )
	    return notify_fail("宣示領地失敗。\n");
	log_file("CLAN", sprintf("[%s] %s: %s(%s) claims territory %s\n",
	    ctime(time()), clan, me->name(), me->query("id"), area));
	clan_line(HIC"本幫即刻起將「" + area + "」納入勢力範圍!\n"NOR);
	return 1;
    }

    // function 4: nick - change clan nickname
    if( arg == "nick" ) {
	me->set("clan/nick", target);
	tell_object(me, "Ok.\n");
	return 1 ;
    }

    // searching target
    //who = present(target, environment(me));
    who = find_player(target);
    if( !who || !userp(who) ) return notify_fail("沒有這個人。\n");

    // function 5: join - apply to join a clan
    if( arg == "join" ) {
        if( me->query("clan/clan_name") ) 
	    return notify_fail("你已加入過幫派，請先脫離原來幫派。\n");
	if( who->query("clan/clan_level") < 2 )
	    return notify_fail("此人並非幫派長老。\n");

	if( !present(target, environment(me)) )
	    return notify_fail("這裡沒有這個人。\n");

	message_vision(HIW"$N向$n申請加入"+who->query("clan/clan_name")
	+"。\n"NOR, me, who);
	me->set_temp("clan/apply", 1);
	return 1;
    }

    // following cmds only clan member can use them
    if( !me->query("clan/clan_name") ) return notify_fail("你並非幫派成員。\n");
    // the cmds need clan_level > 1 
    if( me->query("clan/clan_level") < 2 )
	return notify_fail("錯誤指令用法，或幫派職等不足。\n");    

    // function 6: accept - accept somebody join my clan
    if( arg == "accept" ) {
	if( !arg ) return notify_fail("你想收誰入幫??\n");

        if( !present(target, environment(me)) )
            return notify_fail("這裡沒有這個人。\n");

	if( who->query_temp("clan/apply") ) {
	    obj = new("/obj/clan_symbol");
	    obj->move(who);
	    seteuid( geteuid() );
	    who->delete_temp("clan/apply");
	    who->set("clan/clan_name", me->query("clan/clan_name"));
	    who->set("clan/rank", "幫眾");
	    who->set("clan/nick", "無");
	    who->set("clan/clan_level", 1);

	    // 在中央幫派 daemon 登錄新幫眾 (職等1), 離線亦可查得。
	    CLAN_D->add_member(me->query("clan/clan_name"), who->query("id"), 1);

	    log_file("CLAN", sprintf("[%s] %s: %s(%s) accepts %s(%s)\n",
		ctime(time()), me->query("clan/clan_name"), me->name(),
		me->query("id"), who->name(), who->query("id")));

	    tell_object(who, HIY+me->name() + "交給你一個幫派信物。\n"NOR);
	    clan_line("歡迎"+who->name()+"加入" +
		me->query("clan/clan_name") + "!!\n"); }
        else {
            tell_object(me, "此人並未向你申請加入幫派。\n");
	}
	return 1;
    }

    // check if same clan
    if( who->query("clan/clan_name") != me->query("clan/clan_name") )
	return notify_fail("他不是本幫成員。\n");

    // function 7: kickout - kickout someone from clan members  
    if( arg == "kickout" ) {
	if( target == me->query("id") ) 
	    return notify_fail("要叛幫請用: ccmd leave.\n");
	if( who->query("clan/clan_level") == 2 
	&& me->query("clan/clan_level") != 3 ) 
	    return notify_fail("長老必需由幫主親自處理。\n");
	if( who->query("clan/clan_level") == 3 )
	    return notify_fail("不行。\n");

        seteuid( getuid() );
	if( who->query("clan/clan_level") == 2 ) {
	    // 重設長老數目
	    me->add("clan/elder", -1); }
	clan_line("即刻起, " + who->name() + "不再是本幫幫眾。\n");
	log_file("CLAN",sprintf("[%s] %s: %s(%s) kickouts %s(%s)\n",
	    ctime(time()), me->query("clan/clan_name"), me->name(),
	    me->query("id"), who->name(), who->query("id")) );
	tell_object(who, HIY"你已經不再是" +
	    who->query("clan/clan_name") + "的幫眾了。\n"NOR);
	// 自中央幫派 daemon 移除被逐者 (在刪除其 clan/* 快取之前先取得幫名)。
	CLAN_D->remove_member(who->query("clan/clan_name"), who->query("id"));
	who->delete("clan/clan_name");
	who->delete("clan/clan_nick");
	who->delete("clan/clan_level");
	who->delete("clan/rank");
	if( obj = present("clan symbol", who) )
	    destruct(obj);
#ifdef SAVE_USER
	me->save();
	who->save();
#endif
	return 1;
    }

    // the cmds for clan leader
    if( me->query("clan/clan_level") < 3 )
	return notify_fail("錯誤指令用法，或幫派職等不足。\n");

    // function : promote - promote the level of clan member
    if( arg == "promote" ) {
	if( target == me->query("id") ) return notify_fail("不行!\n");
	if( who->query("class") == "commoner" )
	    return notify_fail("平民能力不足以擔任要職。\n");
	if( me->query_temp("clan/change_leader") ) {
	    me->delete_temp("clan/change_leader");
	    clan_line("本人已完成讓位儀式, 即刻起, 由"
		+ who->name() + "繼任" + me->query("clan/clan_name")
		+ me->query("clan/rank") + "之職。\n");

	    seteuid( getuid() );
	    who->set("clan/clan_level", 3);
	    who->set("clan/elder", me->query("clan/elder"));
	    who->set("clan/rank", me->query("clan/rank"));
	    tell_object(who, HIY"你的職位由長老升為" +
	    	me->query("clan/rank") + "。\n"NOR);
	    // 中央幫派 daemon: 讓位 - who 升幫主(3), me 降長老(2)。
	    CLAN_D->set_member_level(me->query("clan/clan_name"),
		who->query("id"), 3);
	    CLAN_D->set_member_level(me->query("clan/clan_name"),
		me->query("id"), 2);
	    me->delete("clan/elder");
	    me->set("clan/clan_level", 2);
	    me->set("clan/rank", "長老");
	    tell_object(me, HIY"你的職位由" + who->query("clan/rank") +
		"降為長老。\n"NOR);
#ifdef SAVE_USER
	    me->save();
	    who->save();
#endif
	    log_file("CLAN", sprintf("[%s] %s changes %s: %s(%s) to %s(%s)\n",
		ctime(time()), me->query("clan/clan_name"), 
		who->query("clan/rank"), me->name(), me->query("id"),
		who->name(), who->query("id")) );
	    return 1;
	}

	if( who->query("clan/clan_level") == 2 ) {
	    if( who->query("level") < 40 ) {
		tell_object(me, "此人能力不足以擔當"
		    + me->query("clan/rank")+"之職。\n");
		return 1;
	    }
	    tell_object(me, HIY"注意!! 此舉將使" + who->name() +
		"取代你目前的" + me->query("clan/rank") + "地位," +
		"若是正確請再輸入一次。\n"NOR);
	    me->set_temp("clan/change_leader", 1);
	    return 1;
	}

	if( me->query("clan/elder") > 2 )
	    return notify_fail("本幫長老人數已滿, 無法再收新長老。\n");

	if( who->query("level") < 20 ) 
	    return notify_fail("此人能力不足以擔當長老之職。\n");

	clan_line("即刻起, " + who->name() + "升為" +
	    me->query("clan/clan_name") + "長老。\n");
	seteuid( getuid() );
	me->add("clan/elder", 1);
	if( who->query("clan/elder") )
	    who->delete("clan/elder");
	who->set("clan/clan_level", 2);
	who->set("clan/rank", "長老");
	// 中央幫派 daemon: 升任長老(職等2)。
	CLAN_D->set_member_level(me->query("clan/clan_name"),
	    who->query("id"), 2);
	log_file("CLAN", sprintf("[%s] %s: %s(%s) promotes %s(%s)\n",
	    ctime(time()), me->query("clan/clan_name"), me->name(),
	    me->query("id"), who->name(), who->query("id")) );
#ifdef SAVE_USER
	me->save();
	who->save();
#endif
	return 1;
    }

    // function 9 : demote - demote the level of clan member
    if( arg == "demote" ) {
	if( target == me->query("id") ) 
	    return notify_fail("你必需先傳位給長老\n");

	if( who->query("clan/clan_level") == 1 )
	    return notify_fail("他的職等已是最低了, 無法再降。\n");

	clan_line("即刻起, 取消 " + who->name() + "長老之職, 降為一般幫眾。\n");
	seteuid( getuid() );
	me->add("clan/elder", -1);
	who->set("clan/clan_level", 1);
	who->set("clan/rank","幫眾");
	// 中央幫派 daemon: 降為幫眾(職等1)。
	CLAN_D->set_member_level(me->query("clan/clan_name"),
	    who->query("id"), 1);
	log_file("CLAN", sprintf("[%s] %s: %s(%s) demotes %s(%s)\n",
	    ctime(time()), me->query("clan/clan_name"), me->name(),
	    me->query("id"), who->name(), who->query("id")) );
#ifdef SAVE_USER
	me->save();
	who->save();
#endif
	return 1;
    }
}

varargs int clan_line(string msg, int emote) 
{
    object *usr, me, obj;
    int i, tmp;

    me = this_player();

    if(!msg) return notify_fail("你要對本幫派的同伴說什麼﹖\n");

    if( me->query_temp("pending/hidden") ) {
        tmp = me->query_temp("pending/hidden");
        me->delete_temp("pending/hidden");
    }

    if( !obj = present("clan symbol", me) )
	return notify_fail("請先取得幫派信物。\n");

    usr = filter_array(users(), "filter_clan", obj);
    if(sizeof(usr))
        for(i=0; i<sizeof(usr); i++)
            if (emote)
                message("system", HIY"【"+me->query("clan/clan_name")+"】"
                HIW+msg+"\n"NOR, usr[i]);
            else
                message("system", HIY"【"+me->query("clan/clan_name")+"】"
                +me->name()+"("+me->query("id")+")："HIW
                +msg+"\n"NOR, usr[i]);

    if( tmp > 0 ) {
        me->set_temp("pending/hidden", tmp); }
    return 1;
}

int help(object me)
{
write(@HELP
本指令為幫派專用指令, 指令格式:
   1. ccmd: 可查詢目前已成立的幫派及負責人
   2. ccmd verify: 補發信物
   3. ccmd leave: 叛幫
   4. ccmd nick <敘述>: 更改你在幫派的匿稱
   5. ccmd join <玩家id>: 申請加入幫派
   6. ccmd treasury: 查詢本幫金庫餘額
   7. ccmd deposit <金額>: 把身上的錢存入本幫金庫
   8. ccmd status: 一覽本幫的交戰/結盟/領地現況
   9. ccmd territory: 列出本幫所有領地
HELP
	);

    if( me->query("clan/clan_level") > 1 ) {
write(@HELP
  10. ccmd accept <玩家id>: 接受加入幫派申請
  11. ccmd kickout <玩家id>: 取消該玩家之幫派資格
  12. ccmd withdraw <金額>: 自本幫金庫提錢入袋 (限長老級以上)
HELP
        );
    }

    if( me->query("clan/clan_level") > 2 ) {
write(@HELP
  13. ccmd promote <玩家id>: 提昇幫眾職等
  14. ccmd demote <玩家id>: 降低幫眾職等
  15. ccmd rank <職等1~3> <稱號>: 更改某職等的階級稱號 (限幫主)
  16. ccmd war <幫派名>: 向另一幫派宣戰 (限幫主)
  17. ccmd peace <幫派名>: 與交戰幫派休戰 (限幫主)
  18. ccmd ally <幫派名>: 與另一幫派結盟 (限幫主)
  19. ccmd unally <幫派名>: 解除與某幫派的盟約 (限幫主)
  20. ccmd claim <地域名|here>: 將一塊地域納入本幫領地 (限幫主)
HELP
	);
    }
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc


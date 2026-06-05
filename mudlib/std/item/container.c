// container.c

#include <ansi.h>

inherit ITEM;

void setup()
{
	// 必須先呼 ::setup()：ITEM::setup()(std/item.c) 做 seteuid(getuid()) 與
	//   set_default_object(clone 的藍本 dbase 回退)。漏呼會使**所有** CONTAINER_ITEM
	//   的 clone euid=0、dbase 無藍本回退——丹鼎 new() 報 *Attempt to create object
	//   without effective UID、只設藍本的 identity 旗標在 clone 上讀不到(見 lesson #13)。
	//   COMBINED_ITEM(std/item/combined.c) 一向有呼 ::setup()，此處補齊以與之一致。
	::setup();
	if( !query("exits") )
		set("exits/out", (: environment :));
}

// This function allows the object ob to be moved into the inventory of
// this object by returning 1 on called.
int accept_object(object player, object ob) { return 1; }

// This function prevents players from getting objects from the inventory
// of this object by returning 1 on called.
int hold_object(object ob)
{
	return query("closed") != 0;
}

// This is the look command processor called when player is inside this 
// object.
int do_look(object me, string arg)
{
	string long;

	if( long = query("inside_long") ) write(long);
	else write("你現在正在一" + query("unit") + name() + "裡。\n");

	if( !query("closed") && query("exits/out") )
		write("要離開這裡可以用 " HIW + "go out" + NOR "。\n");

	if( query("transparent") ) {
		write("從這裡你可以看到外面：\n");
		environment()->do_look(me, arg);
	}

	return 1;
}

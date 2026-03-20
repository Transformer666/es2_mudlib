// vim: syntax=lpc
// recruiter_reply.c - 招兵官給阿寶的回信

inherit ITEM;

void create()
{
    set_name("回信", ({"reply letter", "reply", "letter"}));
    set_weight(50);
    if( !clonep() ) {
        set("unit", "封");
        set("value", 0);
        set("long",
            "一封蓋有軍營印鑑的回信﹐上面用端正的字跡寫著幾行字﹕\n"
            "「阿明年初已隨部隊調往南方駐防﹐一切平安﹐勿念。待軍務\n"
            "稍歇便會回鎮探親。」下方署名是振武軍營招兵官。\n");
    }
    setup();
}

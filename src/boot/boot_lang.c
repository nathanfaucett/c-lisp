#ifndef __LISP_BOOT_LANG_C__
#define __LISP_BOOT_LANG_C__


static void lisp_boot_lang(lisp_State* state) {
    lisp_String_boot(state);
    lisp_Symbol_boot(state);
}


#endif

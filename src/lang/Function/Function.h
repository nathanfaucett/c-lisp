#ifndef __LISP_LANG_FUNCTION_H__
#define __LISP_LANG_FUNCTION_H__

/*
(Function {
    name      Symbol,
    params    List<Annotation>,
    returns   List<Annotation>,
    bodies    List<List<Any>>,
    templates Map<Symbol, Any>
})
*/

static lisp_Object* lisp_Function_call(lisp_State* state, lisp_Object* fn, lisp_Object* args, lisp_Object* scope);

static lisp_bool lisp_Function_equal(lisp_State* state, lisp_Object* a, lisp_Object* b);

static lisp_Object* lisp_Function_export_call(lisp_State* state, lisp_Object* args, lisp_Object* scope);
static lisp_Object* lisp_Function_export_to_string(lisp_State* state, lisp_Object* args, lisp_Object* scope);
static lisp_Object* lisp_Function_export_equal(lisp_State* state, lisp_Object* args, lisp_Object* scope);

static void lisp_Function_boot(lisp_State* state);


#endif

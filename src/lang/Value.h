#ifndef __LISP_LANG_VALUE_H__
#define __LISP_LANG_VALUE_H__


typedef struct lisp_Value {
    lisp_u64 ref_count;
    void* value;
    struct lisp_Value* values;
    struct lisp_Value* type;
} lisp_Value;

static lisp_Value* lisp_Value_alloc(lisp_State* state, lisp_Value* type);
static void lisp_Value_dealloc(lisp_State* state, lisp_Value* value);

lisp_Value* lisp_Value_ref(lisp_Value* value);
void lisp_Value_deref(lisp_State* state, lisp_Value* value);

static lisp_u64 lisp_Value_map_index_of(lisp_State* state, struct lisp_Map* map, lisp_Value* symbol);
static lisp_Value* lisp_Value_map_get(lisp_State* state, struct lisp_Map* map, lisp_Value* symbol);

lisp_Value* lisp_Value_call_arg0(lisp_State* state, lisp_Value* object, lisp_Value* symbol, lisp_Scope* scope);
lisp_Value* lisp_Value_call_arg1(lisp_State* state, lisp_Value* object, lisp_Value* symbol, lisp_Value* arg0, lisp_Scope* scope);
lisp_Value* lisp_Value_call(lisp_State* state, lisp_Value* object, lisp_Value* symbol, lisp_Value* args, lisp_Scope* scope);

#endif

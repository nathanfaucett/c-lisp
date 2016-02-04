#ifndef __LISP_CORE_STATE_H__
#define __LISP_CORE_STATE_H__


typedef struct lisp_State {
    struct lisp_Heap* heap;
    struct lisp_Scope* scope;

    struct lisp_Value* Type;

    struct lisp_Value* Any;

    struct lisp_Value* Annotation;
    struct lisp_Value* Nil;

    struct lisp_Value* Collection;
    struct lisp_Value* Indexed;
    struct lisp_Value* Keyed;

    struct lisp_Value* List;
    struct lisp_Value* ListNode;
    struct lisp_Value* Map;

    struct lisp_Value* Callable;
    struct lisp_Value* Native;
    struct lisp_Value* Function;
    struct lisp_Value* Macro;

    struct lisp_Value* Char;
    struct lisp_Value* String;
    struct lisp_Value* Symbol;

    struct lisp_Value* Number;
    struct lisp_Value* Real;
    struct lisp_Value* Float;
    struct lisp_Value* Integer;
    struct lisp_Value* Signed;
    struct lisp_Value* Unsigned;

    struct lisp_Value* Float32;
    struct lisp_Value* Float64;

    struct lisp_Value* UInt;
    struct lisp_Value* UInt8;
    struct lisp_Value* UInt16;
    struct lisp_Value* UInt32;
    struct lisp_Value* UInt64;

    struct lisp_Value* Int;
    struct lisp_Value* Int8;
    struct lisp_Value* Int16;
    struct lisp_Value* Int32;
    struct lisp_Value* Int64;

    struct lisp_Value* Bool;

    struct lisp_Value* nil;
    struct lisp_Value* true;
    struct lisp_Value* false;
    struct lisp_Value* empty_list;
    struct lisp_Value* empty_map;
} lisp_State;

static lisp_State* lisp_State_new(void);
static void lisp_State_delete(lisp_State* state);

static void* lisp_State_alloc(lisp_State* state, lisp_size size);
static void lisp_State_dealloc(lisp_State* state, void* value);


#endif

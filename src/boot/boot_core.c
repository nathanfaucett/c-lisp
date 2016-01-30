#ifndef __LISP_BOOT_CORE_C__
#define __LISP_BOOT_CORE_C__


static void lisp_boot_core(lisp_State* state) {
    state->Callable = lisp_boot_create_AbstractType(state, state->Any, "Callable");
    state->Function = lisp_boot_create_Type(state, state->Callable, sizeof(lisp_Function), "Function", lisp_Function_alloc, NULL, lisp_Function_mark);
    state->Macro = lisp_boot_create_Type(state, state->Callable, sizeof(lisp_Macro), "Macro", lisp_Macro_alloc, NULL, lisp_Macro_mark);

    state->Collection = lisp_boot_create_AbstractType(state, state->Any, "Collection");
    state->Indexed = lisp_boot_create_AbstractType(state, state->Collection, "Indexed");
    state->Keyed = lisp_boot_create_AbstractType(state, state->Collection, "Keyed");

    ((lisp_Type*) state->String->data)->super = state->Indexed;
    ((lisp_Type*) state->Seq->data)->super = state->Indexed;
    ((lisp_Type*) state->Map->data)->super = state->Keyed;

    state->Number = lisp_boot_create_AbstractType(state, state->Any, "Number");
    state->Real = lisp_boot_create_AbstractType(state, state->Number, "Real");
    state->AbstractFloat = lisp_boot_create_AbstractType(state, state->Real, "AbstractFloat");
    state->Integer = lisp_boot_create_AbstractType(state, state->Real, "Integer");
    state->Signed = lisp_boot_create_AbstractType(state, state->Integer, "Signed");
    state->Unsigned = lisp_boot_create_AbstractType(state, state->Integer, "Unsigned");

    ((lisp_Type*) state->Bool->data)->super = state->Integer;

    state->Float16 = lisp_boot_create_BytesType(state, state->AbstractFloat, 2, "Float16");
    state->Float32 = lisp_boot_create_BytesType(state, state->AbstractFloat, 4, "Float32");
    state->Float64 = lisp_boot_create_BytesType(state, state->AbstractFloat, 8, "Float64");

    state->UInt8 = lisp_boot_create_BytesType(state, state->Unsigned, 1, "UInt8");
    state->UInt16 = lisp_boot_create_BytesType(state, state->Unsigned, 2, "UInt16");
    state->UInt32 = lisp_boot_create_BytesType(state, state->Unsigned, 4, "UInt32");
    state->UInt64 = lisp_boot_create_BytesType(state, state->Unsigned, 8, "UInt64");

    state->Int8 = lisp_boot_create_BytesType(state, state->Signed, 1, "Int8");
    state->Int16 = lisp_boot_create_BytesType(state, state->Signed, 2, "Int16");
    state->Int32 = lisp_boot_create_BytesType(state, state->Signed, 4, "Int32");
    state->Int64 = lisp_boot_create_BytesType(state, state->Signed, 8, "Int64");

    if (sizeof(lisp_size) == 8) {
        state->UInt = state->UInt64;
        state->Int = state->Int64;
    } else {
        state->UInt = state->UInt32;
        state->Int = state->Int32;
    }

    state->nil = lisp_Value_alloc(state, state->Nil);
    state->scope = lisp_Scope_alloc(state, NULL);

    lisp_Scope_def(state->scope, ((lisp_Type*) state->Type->data)->name, state->Type);

    lisp_Scope_def(state->scope, ((lisp_Type*) state->Any->data)->name, state->Any);/*
    lisp_Scope_def(state->scope, ((lisp_Type*) state->Nil->data)->name, state->Nil);

    lisp_Scope_def(state->scope, ((lisp_Type*) state->Callable->data)->name, state->Callable);
    lisp_Scope_def(state->scope, ((lisp_Type*) state->Macro->data)->name, state->Macro);
    lisp_Scope_def(state->scope, ((lisp_Type*) state->Function->data)->name, state->Function);

    lisp_Scope_def(state->scope, ((lisp_Type*) state->Char->data)->name, state->Char);
    lisp_Scope_def(state->scope, ((lisp_Type*) state->String->data)->name, state->String);
    lisp_Scope_def(state->scope, ((lisp_Type*) state->Symbol->data)->name, state->Symbol);

    lisp_Scope_def(state->scope, ((lisp_Type*) state->Number->data)->name, state->Number);
    lisp_Scope_def(state->scope, ((lisp_Type*) state->Real->data)->name, state->Real);
    lisp_Scope_def(state->scope, ((lisp_Type*) state->AbstractFloat->data)->name, state->AbstractFloat);
    lisp_Scope_def(state->scope, ((lisp_Type*) state->Integer->data)->name, state->Integer);
    lisp_Scope_def(state->scope, ((lisp_Type*) state->Signed->data)->name, state->Signed);
    lisp_Scope_def(state->scope, ((lisp_Type*) state->Unsigned->data)->name, state->Unsigned);

    lisp_Scope_def(state->scope, ((lisp_Type*) state->Float16->data)->name, state->Float16);
    lisp_Scope_def(state->scope, ((lisp_Type*) state->Float32->data)->name, state->Float32);
    lisp_Scope_def(state->scope, ((lisp_Type*) state->Float64->data)->name, state->Float64);

    lisp_Scope_def(state->scope, ((lisp_Type*) state->UInt->data)->name, state->UInt);
    lisp_Scope_def(state->scope, ((lisp_Type*) state->UInt8->data)->name, state->UInt8);
    lisp_Scope_def(state->scope, ((lisp_Type*) state->UInt16->data)->name, state->UInt16);
    lisp_Scope_def(state->scope, ((lisp_Type*) state->UInt32->data)->name, state->UInt32);
    lisp_Scope_def(state->scope, ((lisp_Type*) state->UInt64->data)->name, state->UInt64);

    lisp_Scope_def(state->scope, ((lisp_Type*) state->Int->data)->name, state->Int);
    lisp_Scope_def(state->scope, ((lisp_Type*) state->Int8->data)->name, state->Int8);
    lisp_Scope_def(state->scope, ((lisp_Type*) state->Int16->data)->name, state->Int16);
    lisp_Scope_def(state->scope, ((lisp_Type*) state->Int32->data)->name, state->Int32);
    lisp_Scope_def(state->scope, ((lisp_Type*) state->Int64->data)->name, state->Int64);

    lisp_Scope_def(state->scope, ((lisp_Type*) state->Bool->data)->name, state->Bool);

    lisp_Scope_def(state->scope, ((lisp_Type*) state->Collection->data)->name, state->Collection);
    lisp_Scope_def(state->scope, ((lisp_Type*) state->Indexed->data)->name, state->Indexed);
    lisp_Scope_def(state->scope, ((lisp_Type*) state->Keyed->data)->name, state->Keyed);

    lisp_Scope_def(state->scope, ((lisp_Type*) state->Seq->data)->name, state->Seq);
    lisp_Scope_def(state->scope, ((lisp_Type*) state->Map->data)->name, state->Map);

    lisp_Scope_def(state->scope, ((lisp_Type*) state->Nil->data)->name, state->nil);
    */
}


#endif

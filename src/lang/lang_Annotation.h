#ifndef __LISP_LANG_ANNOTATION_H__
#define __LISP_LANG_ANNOTATION_H__


#define LISP_IDX_ANNOTATION_TYPE 0
#define LISP_IDX_ANNOTATION_SUBTYPES 1


lisp_Object* lisp_Annotation_new(lisp_State* state, lisp_Object* Type);
lisp_Object* lisp_Annotation_new_types(lisp_State* state, lisp_Object* Type, lisp_Object* Types);


#endif

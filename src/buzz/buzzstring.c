#include "buzzstring.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>

/****************************************/
/****************************************/

#define function_register(TABLE, FNAME, FPOINTER)                       \
   buzzvm_push(vm, (TABLE));                                            \
   buzzvm_pushs(vm, buzzvm_string_register(vm, (FNAME), 1));            \
   buzzvm_pushcc(vm, buzzvm_function_register(vm, (FPOINTER)));         \
   buzzvm_tput(vm);

/****************************************/
/****************************************/

int buzzstring_register(buzzvm_t vm) {
   /* Make "string" table */
   buzzobj_t t = buzzheap_newobj(vm->heap, BUZZTYPE_TABLE);
   /* Register methods */
   function_register(t, "length", buzzstring_length);
   function_register(t, "sub", buzzstring_sub);
   /* Register "string" table */
   buzzvm_pushs(vm, buzzvm_string_register(vm, "string", 1));
   buzzvm_push(vm, t);
   buzzvm_gstore(vm);
   /* All done */
   return vm->state;
}

/****************************************/
/****************************************/

int buzzstring_length(buzzvm_t vm) {
   /* Make sure one parameter has been passed */
   buzzvm_lnum_assert(vm, 1);
   /* Get the string */
   buzzvm_lload(vm, 1);
   buzzvm_type_assert(vm, 1, BUZZTYPE_STRING);
   const char* s = buzzvm_stack_at(vm, 1)->s.value.str;
   /* Get its length and put it on the stack */
   buzzvm_pushi(vm, strlen(s));
   /* All done */
   return buzzvm_ret1(vm);
}

/****************************************/
/****************************************/

int buzzstring_sub(buzzvm_t vm) {
   /* Make sure two or three parameters have been passed */
   if(buzzvm_lnum(vm) != 2 &&
      buzzvm_lnum(vm) != 3) {
      vm->state = BUZZVM_STATE_ERROR;
      vm->error = BUZZVM_ERROR_LNUM;
      asprintf(&vm->errormsg, "%s: expected 2 or 3 parameters, got %" PRId64, buzzvm_error_desc[vm->error], buzzvm_lnum(vm));
      return (vm)->state;
   }
   /* Get the string and its length */
   buzzvm_lload(vm, 1);
   buzzvm_type_assert(vm, 1, BUZZTYPE_STRING);
   const char* s = buzzvm_stack_at(vm, 1)->s.value.str;
   int32_t ls = strlen(s);
   /* Get the starting index */
   buzzvm_lload(vm, 2);
   buzzvm_type_assert(vm, 1, BUZZTYPE_INT);
   int32_t n = buzzvm_stack_at(vm, 1)->i.value;
   if(n >= ls) {
      /* Out of bounds */
      buzzvm_pushnil(vm);
      return buzzvm_ret1(vm);
   }
   /* Get the ending index */
   int32_t m = ls;
   if(buzzvm_lnum(vm) == 3) {
      buzzvm_lload(vm, 3);
      buzzvm_type_assert(vm, 1, BUZZTYPE_INT);
      m = buzzvm_stack_at(vm, 1)->i.value;
      if(m < n) {
         /* Out of bounds */
         buzzvm_pushnil(vm);
         return buzzvm_ret1(vm);
      }
      else if(m >= ls)
         /* Readjust m, because it goes beyond the string limits */
         m = ls;
   }
   /* Make new string for the substring */
   char* s2 = (char*)malloc(m - n + 1);
   strncpy(s2, s + n, m - n);
   s2[m - n] = 0;
   buzzvm_pushs(vm, buzzvm_string_register(vm, s2, 0));
   free(s2);
   /* All done */
   return buzzvm_ret1(vm);
}

/****************************************/
/****************************************/

int buzzstring_tostring(buzzvm_t vm) {
   /* Make sure one parameter has been passed */
   buzzvm_lnum_assert(vm, 1);
   /* Get the object */
   buzzvm_lload(vm, 1);
   buzzobj_t o = buzzvm_stack_at(vm, 1);
   /* Make sure it's an int or a float */
   if(o->o.type != BUZZTYPE_INT &&
      o->o.type != BUZZTYPE_FLOAT) {
      /* Can't convert */
      buzzvm_pushnil(vm);
   }
   /* Perform conversion */
   char* str;
   if(buzzvm_stack_at(vm, 1)->o.type == BUZZTYPE_INT)
      asprintf(&str, "%" PRId32, o->i.value);
   else
      asprintf(&str, "%f", o->f.value);
   buzzvm_pushs(vm, buzzvm_string_register(vm, str, 0));
   free(str);
   /* All done */
   return buzzvm_ret1(vm);
}

/****************************************/
/****************************************/

int buzzstring_toint(buzzvm_t vm) {
   /* Make sure one parameter has been passed */
   buzzvm_lnum_assert(vm, 1);
   /* Get the string */
   buzzvm_lload(vm, 1);
   buzzvm_type_assert(vm, 1, BUZZTYPE_STRING);
   const char* s = buzzvm_stack_at(vm, 1)->s.value.str;
   /* Convert the string to int */
   char* endptr;
   int32_t i = strtod(s, &endptr);
   /* Was the conversion successful? */
   if((errno != 0 && i == 0) || /* An error occurred */
      (endptr == s)) {         /* No digit found */
      /* Yes, an error occurred */
      buzzvm_pushnil(vm);
   }
   else {
      /* All OK, return converted value */
      buzzvm_pushi(vm, i);
   }
   /* All done */
   return buzzvm_ret1(vm);
}

/****************************************/
/****************************************/

int buzzstring_tofloat(buzzvm_t vm) {
   /* Make sure one parameter has been passed */
   buzzvm_lnum_assert(vm, 1);
   /* Get the string */
   buzzvm_lload(vm, 1);
   buzzvm_type_assert(vm, 1, BUZZTYPE_STRING);
   const char* s = buzzvm_stack_at(vm, 1)->s.value.str;
   /* Convert the string to int */
   char* endptr;
   float f = strtof(s, &endptr);
   /* Was the conversion successful? */
   if((errno != 0 && f == 0) || /* An error occurred */
      (endptr == s)) {          /* No digit found */
      /* Yes, an error occurred */
      buzzvm_pushnil(vm);
   }
   else {
      /* All OK, return converted value */
      buzzvm_pushf(vm, f);
   }
   /* All done */
   return buzzvm_ret1(vm);
}

/****************************************/
/****************************************/
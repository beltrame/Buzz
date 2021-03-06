#include "buzzmath.h"
#include "buzztype.h"
#include <stdio.h>
#include <math.h>

/****************************************/
/****************************************/

#define function_register(TABLE, FNAME)                                 \
   buzzvm_push(vm, TABLE);                                              \
   buzzvm_pushs(vm, buzzvm_string_register(vm, #FNAME, 1));             \
   buzzvm_pushcc(vm, buzzvm_function_register(vm, buzzmath_ ## FNAME)); \
   buzzvm_tput(vm);

#define constant_register(TABLE, FNAME, VALUE)                          \
   buzzvm_push(vm, (TABLE));                                            \
   buzzvm_pushs(vm, buzzvm_string_register(vm, (FNAME), 1));            \
   buzzvm_pushf(vm, (VALUE));                                           \
   buzzvm_tput(vm);

int buzzmath_register(buzzvm_t vm) {
   /* Make "math" table */
   buzzobj_t t = buzzheap_newobj(vm->heap, BUZZTYPE_TABLE);
   /* Register methods */
   function_register(t, abs);
   function_register(t, log);
   function_register(t, log2);
   function_register(t, log10);
   function_register(t, sqrt);
   function_register(t, sin);
   function_register(t, cos);
   function_register(t, tan);
   function_register(t, asin);
   function_register(t, acos);
   function_register(t, atan);
   function_register(t, min);
   function_register(t, max);
   /* Register constants */
   constant_register(t, "pi", 3.14159265358979323846);
   /* Register "math" table */
   buzzvm_pushs(vm, buzzvm_string_register(vm, "math", 1));
   buzzvm_push(vm, t);
   buzzvm_gstore(vm);
   return vm->state;
}

/****************************************/
/****************************************/

int buzzmath_abs(buzzvm_t vm) {
   buzzvm_lnum_assert(vm, 1);
   /* Get argument */
   buzzvm_lload(vm, 1);
   buzzobj_t o = buzzvm_stack_at(vm, 1);
   if(o->o.type == BUZZTYPE_FLOAT) {
      buzzvm_pushf(vm, fabsf(o->f.value));
   }
   else if(o->o.type == BUZZTYPE_INT) {
      buzzvm_pushi(vm, abs(o->i.value));
   }
   else {
      vm->state = BUZZVM_STATE_ERROR;
      vm->error = BUZZVM_ERROR_TYPE;
      return vm->state;
   }
   /* Return result */
   return buzzvm_ret1(vm);
}

/****************************************/
/****************************************/

int buzzmath_log(buzzvm_t vm) {
   buzzvm_lnum_assert(vm, 1);
   /* Get argument */
   float arg;
   buzzvm_lload(vm, 1);
   buzzobj_t o = buzzvm_stack_at(vm, 1);
   if(o->o.type == BUZZTYPE_FLOAT)    arg = o->f.value;
   else if(o->o.type == BUZZTYPE_INT) arg = o->i.value;
   else {
      vm->state = BUZZVM_STATE_ERROR;
      vm->error = BUZZVM_ERROR_TYPE;
      return vm->state;
   }
   /* Push result */
   buzzvm_pushf(vm, logf(arg));
   /* Return result */
   return buzzvm_ret1(vm);
}

/****************************************/
/****************************************/

int buzzmath_log2(buzzvm_t vm) {
   buzzvm_lnum_assert(vm, 1);
   /* Get argument */
   float arg;
   buzzvm_lload(vm, 1);
   buzzobj_t o = buzzvm_stack_at(vm, 1);
   if(o->o.type == BUZZTYPE_FLOAT)    arg = o->f.value;
   else if(o->o.type == BUZZTYPE_INT) arg = o->i.value;
   else {
      vm->state = BUZZVM_STATE_ERROR;
      vm->error = BUZZVM_ERROR_TYPE;
      return vm->state;
   }
   /* Push result */
   buzzvm_pushf(vm, log2f(arg));
   /* Return result */
   return buzzvm_ret1(vm);
}

/****************************************/
/****************************************/

int buzzmath_log10(buzzvm_t vm) {
   buzzvm_lnum_assert(vm, 1);
   /* Get argument */
   float arg;
   buzzvm_lload(vm, 1);
   buzzobj_t o = buzzvm_stack_at(vm, 1);
   if(o->o.type == BUZZTYPE_FLOAT)    arg = o->f.value;
   else if(o->o.type == BUZZTYPE_INT) arg = o->i.value;
   else {
      vm->state = BUZZVM_STATE_ERROR;
      vm->error = BUZZVM_ERROR_TYPE;
      return vm->state;
   }
   /* Push result */
   buzzvm_pushf(vm, log10f(arg));
   /* Return result */
   return buzzvm_ret1(vm);
}

/****************************************/
/****************************************/

int buzzmath_sqrt(buzzvm_t vm) {
   buzzvm_lnum_assert(vm, 1);
   /* Get argument */
   float arg;
   buzzvm_lload(vm, 1);
   buzzobj_t o = buzzvm_stack_at(vm, 1);
   if(o->o.type == BUZZTYPE_FLOAT)    arg = o->f.value;
   else if(o->o.type == BUZZTYPE_INT) arg = o->i.value;
   else {
      vm->state = BUZZVM_STATE_ERROR;
      vm->error = BUZZVM_ERROR_TYPE;
      return vm->state;
   }
   /* Push result */
   buzzvm_pushf(vm, sqrtf(arg));
   /* Return result */
   return buzzvm_ret1(vm);
}

/****************************************/
/****************************************/

int buzzmath_sin(buzzvm_t vm) {
   buzzvm_lnum_assert(vm, 1);
   /* Get argument */
   float arg;
   buzzvm_lload(vm, 1);
   buzzobj_t o = buzzvm_stack_at(vm, 1);
   if(o->o.type == BUZZTYPE_FLOAT)    arg = o->f.value;
   else if(o->o.type == BUZZTYPE_INT) arg = o->i.value;
   else {
      vm->state = BUZZVM_STATE_ERROR;
      vm->error = BUZZVM_ERROR_TYPE;
      return vm->state;
   }
   /* Push result */
   buzzvm_pushf(vm, sinf(arg));
   /* Return result */
   return buzzvm_ret1(vm);
}

/****************************************/
/****************************************/

int buzzmath_cos(buzzvm_t vm) {
   buzzvm_lnum_assert(vm, 1);
   /* Get argument */
   float arg;
   buzzvm_lload(vm, 1);
   buzzobj_t o = buzzvm_stack_at(vm, 1);
   if(o->o.type == BUZZTYPE_FLOAT)    arg = o->f.value;
   else if(o->o.type == BUZZTYPE_INT) arg = o->i.value;
   else {
      vm->state = BUZZVM_STATE_ERROR;
      vm->error = BUZZVM_ERROR_TYPE;
      return vm->state;
   }
   /* Push result */
   buzzvm_pushf(vm, cosf(arg));
   /* Return result */
   return buzzvm_ret1(vm);
}

/****************************************/
/****************************************/

int buzzmath_tan(buzzvm_t vm) {
   buzzvm_lnum_assert(vm, 1);
   /* Get argument */
   float arg;
   buzzvm_lload(vm, 1);
   buzzobj_t o = buzzvm_stack_at(vm, 1);
   if(o->o.type == BUZZTYPE_FLOAT)    arg = o->f.value;
   else if(o->o.type == BUZZTYPE_INT) arg = o->i.value;
   else {
      vm->state = BUZZVM_STATE_ERROR;
      vm->error = BUZZVM_ERROR_TYPE;
      return vm->state;
   }
   /* Push result */
   buzzvm_pushf(vm, tanf(arg));
   /* Return result */
   return buzzvm_ret1(vm);
}

/****************************************/
/****************************************/

int buzzmath_asin(buzzvm_t vm) {
   buzzvm_lnum_assert(vm, 1);
   /* Get argument */
   float arg;
   buzzvm_lload(vm, 1);
   buzzobj_t o = buzzvm_stack_at(vm, 1);
   if(o->o.type == BUZZTYPE_FLOAT)    arg = o->f.value;
   else if(o->o.type == BUZZTYPE_INT) arg = o->i.value;
   else {
      vm->state = BUZZVM_STATE_ERROR;
      vm->error = BUZZVM_ERROR_TYPE;
      return vm->state;
   }
   /* Push result */
   buzzvm_pushf(vm, asinf(arg));
   /* Return result */
   return buzzvm_ret1(vm);
}

/****************************************/
/****************************************/

int buzzmath_acos(buzzvm_t vm) {
   buzzvm_lnum_assert(vm, 1);
   /* Get argument */
   float arg;
   buzzvm_lload(vm, 1);
   buzzobj_t o = buzzvm_stack_at(vm, 1);
   if(o->o.type == BUZZTYPE_FLOAT)    arg = o->f.value;
   else if(o->o.type == BUZZTYPE_INT) arg = o->i.value;
   else {
      vm->state = BUZZVM_STATE_ERROR;
      vm->error = BUZZVM_ERROR_TYPE;
      return vm->state;
   }
   /* Push result */
   buzzvm_pushf(vm, acosf(arg));
   /* Return result */
   return buzzvm_ret1(vm);
}

/****************************************/
/****************************************/

int buzzmath_atan(buzzvm_t vm) {
   buzzvm_lnum_assert(vm, 2);
   /* Get first argument */
   float y;
   buzzvm_lload(vm, 1);
   buzzobj_t o = buzzvm_stack_at(vm, 1);
   if(o->o.type == BUZZTYPE_FLOAT)    y = o->f.value;
   else if(o->o.type == BUZZTYPE_INT) y = o->i.value;
   else {
      vm->state = BUZZVM_STATE_ERROR;
      vm->error = BUZZVM_ERROR_TYPE;
      return vm->state;
   }
   /* Get second argument */
   float x;
   buzzvm_lload(vm, 2);
   o = buzzvm_stack_at(vm, 1);
   if(o->o.type == BUZZTYPE_FLOAT)    x = o->f.value;
   else if(o->o.type == BUZZTYPE_INT) x = o->i.value;
   else {
      vm->state = BUZZVM_STATE_ERROR;
      vm->error = BUZZVM_ERROR_TYPE;
      return vm->state;
   }
   /* Push result */
   buzzvm_pushf(vm, atan2f(y, x));
   /* Return result */
   return buzzvm_ret1(vm);
}

/****************************************/
/****************************************/

int buzzmath_min(buzzvm_t vm) {
   buzzvm_lnum_assert(vm, 2);
   /* Get arguments */
   buzzvm_lload(vm, 1);
   buzzobj_t a = buzzvm_stack_at(vm, 1);
   buzzvm_lload(vm, 2);
   buzzobj_t b = buzzvm_stack_at(vm, 1);
   /* Compare them and return the smaller one */
   if(buzzobj_cmp(a, b) <= 0)
      buzzvm_push(vm, a);
   else
      buzzvm_push(vm, b);
   return buzzvm_ret1(vm);
}

/****************************************/
/****************************************/

int buzzmath_max(buzzvm_t vm) {
   buzzvm_lnum_assert(vm, 2);
   /* Get arguments */
   buzzvm_lload(vm, 1);
   buzzobj_t a = buzzvm_stack_at(vm, 1);
   buzzvm_lload(vm, 2);
   buzzobj_t b = buzzvm_stack_at(vm, 1);
   /* Compare them and return the bigger one */
   if(buzzobj_cmp(a, b) >= 0)
      buzzvm_push(vm, a);
   else
      buzzvm_push(vm, b);
   return buzzvm_ret1(vm);
}

/****************************************/
/****************************************/

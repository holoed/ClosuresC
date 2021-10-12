#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct closure {
   void* fn;
   struct BoxedValue** env;
};

enum Tag { Bool, Int, Double, Char, String, Closure };
union Value { int b; int v_1; double v_2; char v_3; char* v_4; struct closure* fn; };
struct BoxedValue {
    enum Tag tag;
    union Value value;
};

struct BoxedValue* eqInt;
struct BoxedValue* numInt;
struct BoxedValue* numDouble;
struct BoxedValue* fromInteger;
struct BoxedValue* __add;
struct BoxedValue* __sub;
struct BoxedValue* __mul;
struct BoxedValue* __eqeq;

struct closure* mkClosure(void* f) {
   struct closure * c = (struct closure *)malloc(sizeof(struct closure));
   c->fn = f;
   c->env = NULL;
   return c;
}

struct closure* setEnv(struct closure* c, int i, struct BoxedValue* v) {
   if (c->env != NULL && c->env[0] != NULL) {
      int size = sizeof(c->env) / sizeof(struct BoxedValue*);
      struct BoxedValue** args = (struct BoxedValue**)malloc((size + 1) * sizeof(struct BoxedValue*));
      memcpy(args, c->env, sizeof(c->env));
      args[size] = v;
      c->env = args;
      return c;
   }
   else {
      struct BoxedValue** args = (struct BoxedValue**)malloc(sizeof(struct BoxedValue*));
      args[0] = v;
      c->env = args;
      return c;
   }
}

struct BoxedValue* getEnv(struct BoxedValue* env[], int i) {
   return env[i];
}

struct BoxedValue* mkBoxedValue(enum Tag tag, union Value value) {
   struct BoxedValue * v = (struct BoxedValue *)malloc(sizeof(struct BoxedValue));
   v->tag = tag;
   v->value = value;
   return v;
}

struct BoxedValue* applyClosure(struct BoxedValue* fn, struct BoxedValue* x) {
   struct closure * c = (struct closure *)fn->value.fn;
   return ((struct BoxedValue* (*)(struct BoxedValue**, struct BoxedValue*))c->fn)(c->env, x);
}

struct BoxedValue* mkInt(int x) {
   union Value v;
   v.v_1 = x;
   return mkBoxedValue(Int, v);
}

struct BoxedValue* mkDouble(double x) {
   union Value v;
   v.v_2 = x;
   return mkBoxedValue(Double, v);
}

struct BoxedValue* mkString(char* x) {
   union Value v;
   v.v_4 = x;
   return mkBoxedValue(String, v);
}

struct BoxedValue* mkBool(int b) {
   union Value v;
   v.b = b;
   return mkBoxedValue(Bool, v);
}

struct BoxedValue* mkFn(void* x) {
   union Value v;
   v.fn = x;
   return mkBoxedValue(Closure, v);
}

struct BoxedValue* fromIntegerInt(struct BoxedValue* x) {
   return x;
}

struct BoxedValue* __plus(struct BoxedValue* x, struct BoxedValue* y){
   return mkInt(x->value.v_1 + y->value.v_1);
}

struct BoxedValue* __minus(struct BoxedValue* x, struct BoxedValue* y){
   return mkInt(x->value.v_1 - y->value.v_1);
}

struct BoxedValue* __star(struct BoxedValue* x, struct BoxedValue* y){
   return mkInt(x->value.v_1 * y->value.v_1);
}

struct BoxedValue* __equals(struct BoxedValue* x, struct BoxedValue* y){
   return mkBool(x->value.v_1 == y->value.v_1);
}

struct BoxedValue* fromIntegerDouble(struct BoxedValue* x) {
   return mkDouble(x->value.v_1);
}

struct BoxedValue* eqIntGet(char* s) {
   if (s == "==") return mkFn(&__equals);
}

struct BoxedValue* numIntGet(char* s) {
   if (s == "fromInteger") return mkFn(&fromIntegerInt);
   if (s == "+") return mkFn(&__plus);
   if (s == "-") return mkFn(&__minus);
   if (s == "*") return mkFn(&__star);
}

struct BoxedValue* numDoubleGet(char* s) {
   if (s == "fromInteger") return mkFn(&fromIntegerDouble);
}

struct BoxedValue* fromInt_part2(struct BoxedValue* env[], struct BoxedValue* x) {
   void* fn = getEnv(env, 0)->value.fn;
   void* fn2 = (((struct BoxedValue* (*)(char*))fn)("fromInteger"))->value.fn;
   return ((struct BoxedValue* (*)(struct BoxedValue *))fn2)(x);
}

struct BoxedValue* fromInt_part1(struct BoxedValue* env[], struct BoxedValue* inst) {
   return mkFn(setEnv(mkClosure(&fromInt_part2), 0, inst));
}

struct BoxedValue* __add_part3(struct BoxedValue* env[], struct BoxedValue* y) {
   void* fn = getEnv(env, 0)->value.fn;
   void* fn2 = (((struct BoxedValue* (*)(char*))fn)("+"))->value.fn;
   struct BoxedValue* x = getEnv(env, 1);
   return ((struct BoxedValue* (*)(struct BoxedValue*, struct BoxedValue*))fn2)(x, y);
}

struct BoxedValue* __add_part2(struct BoxedValue* env[], struct BoxedValue* x) {
   return mkFn(setEnv(setEnv(mkClosure(&__add_part3), 0, getEnv(env, 0)), 1, x));
}

struct BoxedValue* __add_part1(struct BoxedValue* env[], struct BoxedValue* inst) {
   return mkFn(setEnv(mkClosure(&__add_part2), 0, inst));
}

struct BoxedValue* __sub_part3(struct BoxedValue* env[], struct BoxedValue* y) {
   void* fn = getEnv(env, 0)->value.fn;
   void* fn2 = (((struct BoxedValue* (*)(char*))fn)("-"))->value.fn;
   struct BoxedValue* x = getEnv(env, 1);
   return ((struct BoxedValue* (*)(struct BoxedValue*, struct BoxedValue*))fn2)(x, y);
}

struct BoxedValue* __sub_part2(struct BoxedValue* env[], struct BoxedValue* x) {
   return mkFn(setEnv(setEnv(mkClosure(&__sub_part3), 0, getEnv(env, 0)), 1, x));
}

struct BoxedValue* __sub_part1(struct BoxedValue* env[], struct BoxedValue* inst) {
   return mkFn(setEnv(mkClosure(&__sub_part2), 0, inst));
}

struct BoxedValue* __mul_part3(struct BoxedValue* env[], struct BoxedValue* y) {
   void* fn = getEnv(env, 0)->value.fn;
   void* fn2 = (((struct BoxedValue* (*)(char*))fn)("*"))->value.fn;
   struct BoxedValue* x = getEnv(env, 1);
   return ((struct BoxedValue* (*)(struct BoxedValue*, struct BoxedValue*))fn2)(x, y);
}

struct BoxedValue* __mul_part2(struct BoxedValue* env[], struct BoxedValue* x) {
   return mkFn(setEnv(setEnv(mkClosure(&__mul_part3), 0, getEnv(env, 0)), 1, x));
}

struct BoxedValue* __mul_part1(struct BoxedValue* env[], struct BoxedValue* inst) {
   return mkFn(setEnv(mkClosure(&__mul_part2), 0, inst));
}

struct BoxedValue* __eqeq_part3(struct BoxedValue* env[], struct BoxedValue* y) {
   void* fn = getEnv(env, 0)->value.fn;
   void* fn2 = (((struct BoxedValue* (*)(char*))fn)("=="))->value.fn;
   struct BoxedValue* x = getEnv(env, 1);
   return ((struct BoxedValue* (*)(struct BoxedValue*, struct BoxedValue*))fn2)(x, y);
}

struct BoxedValue* __eqeq_part2(struct BoxedValue* env[], struct BoxedValue* x) {
   return mkFn(setEnv(setEnv(mkClosure(&__eqeq_part3), 0, getEnv(env, 0)), 1, x));
}

struct BoxedValue* __eqeq_part1(struct BoxedValue* env[], struct BoxedValue* inst) {
   return mkFn(setEnv(mkClosure(&__eqeq_part2), 0, inst));
}

void init() {
   eqInt = mkFn(&eqIntGet);
   numInt = mkFn(&numIntGet);
   numDouble = mkFn(&numDoubleGet);
   fromInteger = mkFn(mkClosure(&fromInt_part1));
   __add = mkFn(mkClosure(&__add_part1));
   __sub = mkFn(mkClosure(&__sub_part1));
   __mul = mkFn(mkClosure(&__mul_part1));
   __eqeq = mkFn(mkClosure(&__eqeq_part1));
}
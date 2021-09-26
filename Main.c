#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct closure {
   void* fn;
   struct BoxedValue** env;
};

enum Tag { Int, Double, Char, String, Closure };
union Value { int v_1; double v_2; char v_3; char* v_4; struct closure* fn; };
struct BoxedValue {
    enum Tag tag;
    union Value value;
};

struct BoxedValue* numInt;
struct BoxedValue* numDouble;

struct closure* mkClosure(void* f) {
   struct closure * c = (struct closure *)malloc(sizeof(struct closure));
   c->fn = f;
   return c;
}

struct closure* setEnv(struct closure* c, int i, struct BoxedValue* v) {
   static struct BoxedValue* args[1]; 
   args[0] = v;
   c->env = args;
   return c;
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

struct BoxedValue* applyClosure(struct closure * c, struct BoxedValue* arg) {
   return ((struct BoxedValue* (*)(struct BoxedValue**, struct BoxedValue*))c->fn)(c->env, arg);
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

struct BoxedValue* mkFn(void* x) {
   union Value v;
   v.fn = x;
   return mkBoxedValue(Closure, v);
}

struct BoxedValue* add(struct BoxedValue* env[], struct BoxedValue* y) {
   return mkInt(getEnv(env, 0)->value.v_1 + y->value.v_1);
}

struct BoxedValue* concat(struct BoxedValue* env[], struct BoxedValue* y) {
   char* s1 = getEnv(env, 0)->value.v_4;
   char* s2 = y->value.v_4;
   int size = strlen(s1) + strlen(s2) + 1;
   char* d = malloc(sizeof(char) * size); 
   strcat (strcpy(d, s1), s2);
   d[size - 1] = '\0';
   return mkString(d);
}

struct BoxedValue* fromIntegerInt(struct BoxedValue* x) {
   return x;
}

struct BoxedValue* fromIntegerDouble(struct BoxedValue* x) {
   return mkDouble(x->value.v_1);
}

struct BoxedValue* numIntGet(char* s) {
   return mkFn(&fromIntegerInt);
}

struct BoxedValue* numDoubleGet(char* s) {
   return mkFn(&fromIntegerDouble);
}

struct BoxedValue* fromInt(struct BoxedValue* env[], struct BoxedValue* y) {
   void* fn = getEnv(env, 0)->value.fn;
   void* fn2 = (((struct BoxedValue* (*)(char*))fn)("fromInteger"))->value.fn;
   return ((struct BoxedValue* (*)(struct BoxedValue *))fn2)(y);
}

struct closure * fromInteger(struct BoxedValue* inst) {
   return setEnv(mkClosure(&fromInt), 0, inst);
}

void fromIntegerExample1() {
   struct closure * c0 = fromInteger(numInt);
   struct BoxedValue* ret0 = applyClosure(c0, mkInt(4));
   printf("%d\n", ret0->value.v_1);
}

void fromIntegerExample2() {
   struct closure * c0 = fromInteger(numDouble);
   struct BoxedValue* ret0 = applyClosure(c0, mkInt(4));
   printf("%f\n", ret0->value.v_2);
}


void init() {
   numInt = mkFn(&numIntGet);
   numDouble = mkFn(&numDoubleGet);
}

int main() {
   init();
   fromIntegerExample1();
   fromIntegerExample2();

   struct closure * c1 = setEnv(mkClosure(&add), 0, mkInt(3));
   struct BoxedValue* ret1 = applyClosure(c1, mkInt(2));
   printf("%d\n", ret1->value.v_1);

   struct closure * c2 = setEnv(mkClosure(&concat), 0, mkString("Hello "));
   struct BoxedValue* ret2 = applyClosure(c2, mkString("World"));
   char* s = ret2->value.v_4;
   printf("%s\n", s);
   return 0;
}
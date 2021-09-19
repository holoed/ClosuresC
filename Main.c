#include <stdio.h>

enum Tag {Int, Double, Char, String };
union Value { int v_1; double v_2; char v_3; char* v_4; };
struct BoxedValue {
    enum Tag tag;
    union Value value;
};

struct closure {
   void* fn;
   struct BoxedValue** env;
};

struct closure* mkClosure(void* f, struct BoxedValue** arg) {
   struct closure * c = (struct closure *)malloc(sizeof(struct closure));
   c->env = arg;
   c->fn = f;
   return c;
}

struct BoxedValue* mkBoxedValue(enum Tag tag, union Value value) {
   struct BoxedValue * v = (struct BoxedValue *)malloc(sizeof(struct BoxedValue));
   v->tag = tag;
   v->value = value;
   return v;
}

struct BoxedValue* applyClosure(struct closure * c, struct BoxedValue* arg) {
   return ((struct BoxedValue* (*)(struct BoxedValue*, struct BoxedValue*))c->fn)(c->env, arg);
}

struct BoxedValue* mkInt(int x) {
   union Value v;
   v.v_1 = x;
   return mkBoxedValue(Int, v);
}

struct BoxedValue* add(struct BoxedValue* env[], struct BoxedValue* y) {
   return mkInt(env[0]->value.v_1 + y->value.v_1);
}

struct BoxedValue** singleton(struct BoxedValue* arg) {
   static struct BoxedValue* args[1]; 
   args[0] = arg;
   return args;  
}

int main() {
   struct closure * c = mkClosure(&add, singleton(mkInt(3)));
   struct BoxedValue* ret = applyClosure(c, mkInt(2));
   printf("result is %d\n", ret->value.v_1);
}
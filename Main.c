#include <stdio.h>

enum Tag {Int, Float, Char};
union Value { int v_1; float v_2; char v_3; };
struct BoxedValue {
    enum Tag tag;
    union Value value;
};

struct closure {
   void* fn;
   struct BoxedValue* env;
};

struct closure* mkClosure(void* f, struct BoxedValue* arg) {
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

struct BoxedValue* add(struct BoxedValue* x, struct BoxedValue* y) {
   return mkInt(x->value.v_1 + y->value.v_1);
}

int main() {
   struct closure * c = mkClosure(&add, mkInt(3));
   struct BoxedValue* ret = applyClosure(c, mkInt(2));
   printf("result is %d\n", ret->value.v_1);
}
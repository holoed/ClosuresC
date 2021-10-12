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

struct closure* mkClosure(void* f);

struct closure* setEnv(struct closure* c, int i, struct BoxedValue* v);

struct BoxedValue* getEnv(struct BoxedValue* env[], int i);

struct BoxedValue* applyClosure(struct BoxedValue* fn, struct BoxedValue* x);

struct BoxedValue* mkInt(int x);

struct BoxedValue* mkDouble(double x);

struct BoxedValue* mkString(char* x);

struct BoxedValue* mkBool(int b);

struct BoxedValue* mkFn(void* x);

void init();
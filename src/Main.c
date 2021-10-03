#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "JuniorLib.h"

// Primitive Examples

void fromIntegerExample1() {
   struct BoxedValue* anf_0 = applyClosure(fromInteger, numInt);
   struct BoxedValue* anf_1 = mkInt(4);
   struct BoxedValue* anf_2 = applyClosure(anf_0, anf_1);
   printf("fromInteger 4 : Int --> %d\n", anf_2->value.v_1);
}

void fromIntegerExample2() {
   struct BoxedValue* anf_0 = applyClosure(fromInteger, numDouble);
   struct BoxedValue* anf_1 = mkInt(4);
   struct BoxedValue* anf_2 = applyClosure(anf_0, anf_1);
   printf("fromInteger 4 : Double --> %f\n", anf_2->value.v_2);
}

void plusExample() {
   struct BoxedValue* anf_2 = applyClosure(__add, numInt);
   struct BoxedValue* anf_0 = applyClosure(fromInteger, numInt);
   struct BoxedValue* anf_1 = mkInt(1);
   struct BoxedValue* anf_3 = applyClosure(anf_0, anf_1);
   struct BoxedValue* anf_6 = applyClosure(anf_2, anf_3);
   struct BoxedValue* anf_4 = applyClosure(fromInteger, numInt);
   struct BoxedValue* anf_5 = mkInt(2);
   struct BoxedValue* anf_7 = applyClosure(anf_4, anf_5);
   struct BoxedValue* anf_8 = applyClosure(anf_6, anf_7);
   printf("1 + 2 --> %d\n", anf_8->value.v_1);
}

void mulExample() {
   struct BoxedValue* anf_2 = applyClosure(__mul, numInt);
   struct BoxedValue* anf_0 = applyClosure(fromInteger, numInt);
   struct BoxedValue* anf_1 = mkInt(3);
   struct BoxedValue* anf_3 = applyClosure(anf_0, anf_1);
   struct BoxedValue* anf_6 = applyClosure(anf_2, anf_3);
   struct BoxedValue* anf_4 = applyClosure(fromInteger, numInt);
   struct BoxedValue* anf_5 = mkInt(2);
   struct BoxedValue* anf_7 = applyClosure(anf_4, anf_5);
   struct BoxedValue* anf_8 = applyClosure(anf_6, anf_7);
   printf("2 * 3 --> %d\n", anf_8->value.v_1);
}

void eqeqExample() {
   struct BoxedValue* anf_2 = applyClosure(__eqeq, eqInt);
   struct BoxedValue* anf_0 = applyClosure(fromInteger, numInt);
   struct BoxedValue* anf_1 = mkInt(2);
   struct BoxedValue* anf_3 = applyClosure(anf_0, anf_1);
   struct BoxedValue* anf_6 = applyClosure(anf_2, anf_3);
   struct BoxedValue* anf_4 = applyClosure(fromInteger, numInt);
   struct BoxedValue* anf_5 = mkInt(3);
   struct BoxedValue* anf_7 = applyClosure(anf_4, anf_5);
   struct BoxedValue* anf_8 = applyClosure(anf_6, anf_7);
   printf("2 == 3 --> %s\n", (anf_8->value.v_1) ? "True" : "False");
}

void subExample() {
   struct BoxedValue* anf_2 = applyClosure(__sub, numInt);
   struct BoxedValue* anf_0 = applyClosure(fromInteger, numInt);
   struct BoxedValue* anf_1 = mkInt(11);
   struct BoxedValue* anf_3 = applyClosure(anf_0, anf_1);
   struct BoxedValue* anf_6 = applyClosure(anf_2, anf_3);
   struct BoxedValue* anf_4 = applyClosure(fromInteger, numInt);
   struct BoxedValue* anf_5 = mkInt(14);
   struct BoxedValue* anf_7 = applyClosure(anf_4, anf_5);
   struct BoxedValue* anf_8 = applyClosure(anf_6, anf_7);
   printf("11 - 14 --> %d\n", anf_8->value.v_1);
}

void ifExample(bool b) {
    struct BoxedValue* anf_4 = mkBool(b);
    if (anf_4->value.b) {
        struct BoxedValue* anf_0 = applyClosure(fromInteger, numInt);
        struct BoxedValue* anf_1 = mkInt(5);
        printf("if True then 5 else 6 --> %d\n", applyClosure(anf_0, anf_1)->value.v_1);
    } else {
        struct BoxedValue* anf_2 = applyClosure(fromInteger, numInt);
        struct BoxedValue* anf_3 = mkInt(6);
        printf("if False then 5 else 6 --> %d\n", applyClosure(anf_2, anf_3)->value.v_1);
    }
}

// Example: Calling a function 

struct BoxedValue* _f1(struct BoxedValue* _env[], struct BoxedValue* x) {
    struct BoxedValue* anf_0 = applyClosure(__add, getEnv(_env, 0));
    struct BoxedValue* anf_3 = applyClosure(anf_0, x);
    struct BoxedValue* anf_1 = applyClosure(fromInteger, getEnv(_env, 0));
    struct BoxedValue* anf_2 = mkInt(1);
    struct BoxedValue* anf_4 = applyClosure(anf_1, anf_2);
    return applyClosure(anf_3, anf_4);
}

struct BoxedValue* _f0(struct BoxedValue* env[], struct BoxedValue* inst) {
   return mkFn(setEnv(mkClosure(&_f1), 0, inst));
}


void callFunctionExample() {
    struct BoxedValue* f = mkFn(mkClosure(&_f0));
    struct BoxedValue* anf_7 = applyClosure(f, numInt);
    struct BoxedValue* anf_5 = applyClosure(fromInteger, numInt);
    struct BoxedValue* anf_6 = mkInt(7);
    struct BoxedValue* anf_8 = applyClosure(anf_5, anf_6);
    printf("f 7 --> %d\n", applyClosure(anf_7, anf_8)->value.v_1);
}

int main() {
   init();
   fromIntegerExample1();
   fromIntegerExample2();
   plusExample(); 
   subExample();
   mulExample();
   eqeqExample();
   ifExample(true);
   ifExample(false);
   callFunctionExample();
   return 0;
}
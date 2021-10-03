#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "JuniorLib.h"

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

int main() {
   init();
   fromIntegerExample1();
   fromIntegerExample2();
   plusExample();
   subExample();
   mulExample();
   eqeqExample();
   return 0;
}
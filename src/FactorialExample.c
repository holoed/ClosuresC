#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "JuniorLib.h"

#define eqT14 0
#define numT14 1

struct BoxedValue* fac();

struct BoxedValue* _g2(struct BoxedValue* _env[], struct BoxedValue* n) {
    struct BoxedValue* anf_0 = applyClosure(__eqeq, getEnv(_env, eqT14));
    struct BoxedValue* anf_3 = applyClosure(anf_0, n);
    struct BoxedValue* anf_1 = applyClosure(fromInteger, getEnv(_env, numT14));
    struct BoxedValue* anf_2 = mkInt(0);
    struct BoxedValue* anf_4 = applyClosure(anf_1, anf_2);
    struct BoxedValue* anf_18 = applyClosure(anf_3, anf_4);
    if (anf_18->value.b) {
        struct BoxedValue* anf_5 = applyClosure(fromInteger, getEnv(_env, numT14));
        struct BoxedValue* anf_6 = mkInt(1);
        return applyClosure(anf_5, anf_6);
    } else {
        struct BoxedValue* anf_7 = applyClosure(__mul, getEnv(_env, numT14));
        struct BoxedValue* anf_16 = applyClosure(anf_7, n);
        struct BoxedValue* anf_8 = applyClosure(fac(), getEnv(_env, eqT14));
        struct BoxedValue* anf_14 = applyClosure(anf_8, getEnv(_env, numT14));
        struct BoxedValue* anf_9 = applyClosure(__sub, getEnv(_env, numT14));
        struct BoxedValue* anf_12 = applyClosure(anf_9, n);
        struct BoxedValue* anf_10 = applyClosure(fromInteger, getEnv(_env, numT14));
        struct BoxedValue* anf_11 = mkInt(1);
        struct BoxedValue* anf_13 = applyClosure(anf_10, anf_11);
        struct BoxedValue* anf_15 = applyClosure(anf_12, anf_13);
        struct BoxedValue* anf_17 = applyClosure(anf_14, anf_15);
        return applyClosure(anf_16, anf_17);
    }
}

struct BoxedValue* _g1(struct BoxedValue* _env[], struct BoxedValue* inst) {
    struct closure * c = setEnv(mkClosure(&_g2), eqT14, getEnv(_env, eqT14));
    return mkFn(setEnv(c, numT14, inst));
}

struct BoxedValue* _g0(struct BoxedValue* _env[], struct BoxedValue* inst) {
    return mkFn(setEnv(mkClosure(&_g1), eqT14, inst));
}

struct BoxedValue* fac() {
    return mkFn(mkClosure(&_g0));
}

struct BoxedValue* factorialExample() {
    struct BoxedValue* anf_19 = applyClosure(fac(), eqInt);
    struct BoxedValue* anf_22 = applyClosure(anf_19, numInt);
    struct BoxedValue* anf_20 = applyClosure(fromInteger, numInt);
    struct BoxedValue* anf_21 = mkInt(5);
    struct BoxedValue* anf_23 = applyClosure(anf_20, anf_21);
    return applyClosure(anf_22, anf_23);
}


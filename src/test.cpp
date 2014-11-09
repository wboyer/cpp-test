#include "test.h"

int Test::get_i () {
    return i;
}

int TestSub::get_i () {
    return i * 1000;
}

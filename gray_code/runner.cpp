// Author: Victor Migrin (v-v-m12@mail.ru)

#include <combinatorial_object.h>
#include "gray_code.h"

int main() {
    CombinatorialObject *calculator = new GrayCode();
    calculator->interact();
    delete calculator;
    return 0;
}

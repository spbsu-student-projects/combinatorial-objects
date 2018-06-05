// Author: Victor Migrin (v-v-m12@mail.ru)

#include <combinatorial_object.h>
#include "factoradic.h"

int main() {
    CombinatorialObject *calculator = new Factoradic();
    calculator->interact();
    delete calculator;
    return 0;
}

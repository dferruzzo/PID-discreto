#include <iostream>
#include <cassert>
#include "../src/utils/helpers.h"

void testAdd() {
    assert(add(2, 3) == 5);
    assert(add(-1, 1) == 0);
    assert(add(-1, -1) == -2);
}

void testSubtract() {
    assert(subtract(5, 3) == 2);
    assert(subtract(0, 1) == -1);
    assert(subtract(-1, -1) == 0);
}

int main() {
    testAdd();
    testSubtract();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
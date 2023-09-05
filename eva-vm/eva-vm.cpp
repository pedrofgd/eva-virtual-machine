/**
 * Eva VM executable
 */

#include <iostream>

#include "src/Logger.h"
#include "src/vm/EvaVM.h"

int main(int argc, char const *argv[]) {
    EvaVM vm;

    vm.exec(R"(

        42

    )");

    std::cout << "All done!\n";

    return 0;
}

/**
 * Eva VM executable
 */

#include <iostream>

#include "src/Logger.h"
#include "src/vm/EvaVM.h"

int main(int argc, char const *argv[]) {
  EvaVM vm;

  auto result = vm.exec(R"(

    // (+ "hello" " world")
    (* 2 (+ 10 2))

    )");

  log(result);

  std::cout << "All done!\n";

  return 0;
}

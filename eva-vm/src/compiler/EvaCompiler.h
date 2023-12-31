#ifndef EvaCompiler_h
#define EvaCompiler_h

#include "../Logger.h"
#include "../bytecode/OpCode.h"
#include "../parser/EvaParser.h"
#include "../vm/EvaValue.h"

// Allocates new constant in the pool
#define ALLOC_CONST(tester, converter, allocator, value) \
  do {                                                   \
    for (int i = 0; i < co->constants.size(); i++) {     \
      if (!tester(co->constants[i])) {                   \
        continue;                                        \
      }                                                  \
      if (converter(co->constants[i]) == value) {        \
        return i;                                        \
      }                                                  \
    }                                                    \
    co->constants.push_back(allocator(value));           \
  } while (false)

// Generic binary operator: (+ 1 2) OP_CONST, OP_CONST, OP_ADD
#define GEN_BINARY_OP(op) \
  do {                    \
    gen(exp.list[1]);     \
    gen(exp.list[2]);     \
    emit(op);             \
  } while (false)

/*
 * Compiler class, emits bytecode, records contant pool, vars etc.
 */
class EvaCompiler {
 public:
  EvaCompiler() {}

  /*
   * Main compile API.
   */
  CodeObject* compile(const Exp& exp) {
    // Alocate new code object:
    co = AS_CODE(ALLOC_CODE("main"));

    // Generate recursively from top-level:
    gen(exp);

    // Explicit VM-stop marker.
    emit(OP_HALT);

    return co;
  }

  /*
   * Main compile loop.
   */
  void gen(const Exp& exp) {
    switch (exp.type) {
      case ExpType::NUMBER:
        emit(OP_CONST);
        emit(numericConstIdx(exp.number));
        break;

      case ExpType::STRING:
        emit(OP_CONST);
        emit(stringConstIdx(exp.string));
        break;

      case ExpType::SYMBOL:
        DIE << "ExpType::SYMBOL: unimplemented.";
        break;

      case ExpType::LIST:
        auto tag = exp.list[0];

        if (tag.type == ExpType::SYMBOL) {
          auto op = tag.string;

          // -------------------------------
          // Binary math operators:

          if (op == "+") {
            GEN_BINARY_OP(OP_ADD);
          }

          else if (op == "-") {
            GEN_BINARY_OP(OP_SUB);
          }

          else if (op == "*") {
            GEN_BINARY_OP(OP_MUL);
          }

          else if (op == "/") {
            GEN_BINARY_OP(OP_DIV);
          }
        }
        break;
    }
  }

 private:
  /*
   * Allocates a numeric constant.
   */
  size_t numericConstIdx(double value) {
    ALLOC_CONST(IS_NUMBER, AS_NUMBER, NUMBER, value);
    return co->constants.size() - 1;
  }

  /**
   * Allocates a string constant
   */
  size_t stringConstIdx(const std::string& value) {
    ALLOC_CONST(IS_STRING, AS_CPPSTRING, ALLOC_STRING, value);
    return co->constants.size() - 1;
  }

  /*
   * Emits data to the bytecode.
   */
  void emit(uint8_t code) { co->code.push_back(code); }

  /*
   * Compiling code object.
   */
  CodeObject* co;
};

#endif

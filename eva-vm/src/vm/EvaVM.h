/**
  * Eva Virtual Machine
  */

#ifndef EvaVM_h
#define EvaVM_h

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <string>

#include "../Logger.h"
#include "../bytecode/OpCode.h"
#include "EvaValue.h"

/**
 * Reads the current byte in the bytecode
 * and advances the ip pointer.
 */
#define READ_BYTE() *ip++

/**
 * Get a constant from the pool.
 */
#define GET_CONST() constants[READ_BYTE()]

/**
 * Stack top (stack overflow after exceeding).
 */
#define STACK_LIMIT 512

/**
 * Binary operation.
 */
#define BINARY_OP(op) \
    do { \
        auto op2 = AS_NUMBER(pop()); \
        auto op1 = AS_NUMBER(pop()); \
        push(NUMBER(op1 op op2)); \
    } while (false)

/**
* Eva Virtual Machine
*/
class EvaVM {
 public:
     EvaVM() {}

     /**
      * Pushes a value to the top of the stack.
      */
     void push(const EvaValue& value) {
         if ((size_t)(sp - stack.begin()) == STACK_LIMIT) {
            DIE << "push(): Stack overflow.";
         }

         *sp = value;
         sp++;
     }

     /**
      * Pops a value from the stack.
      */
     EvaValue pop() {
         if (sp == stack.begin()) {
             DIE << "pop(): Empty stack.";
         }

         --sp;
         return *sp;
     }

     /**
      * Executes a program.
      */
     EvaValue exec(const std::string &program) {
         // 1. Parse the program into AST
         // auto ast = parser->parse(program)

         // 2. Compile program to Eva bytecode
         // code = compiler->compile(ast)
         
         constants.push_back(ALLOC_STRING("Hello, "));
         constants.push_back(ALLOC_STRING("world!"));

         code = {OP_CONST, 0, OP_CONST, 1, OP_ADD, OP_HALT};

         // Set instruction pointer to the beginning:
         ip = &code[0];

         // Init the stack.
         sp = &stack[0];

         return eval();
     }

     /**
      * Main eval loop.
      */
     EvaValue eval() {
         for (;;) {
             auto opcode = READ_BYTE();
             switch (opcode) {
                 case OP_HALT:
                     return pop();

                 // -------------------------
                 // Constants:

                 case OP_CONST:
                     push(GET_CONST());
                     break;

                 // -------------------------
                 // Math ops:

                 case OP_ADD: {
                     auto op2 = pop();
                     auto op1 = pop();

                     // Numeric addition:
                     if (IS_NUMBER(op1) && IS_NUMBER(op2)) {
                         auto v1 = AS_NUMBER(op1);
                         auto v2 = AS_NUMBER(op2);
                         push(NUMBER(v1 + v2));
                     }

                     // String concatenation:
                     else if (IS_STRING(op1) && IS_STRING(op2)) {
                         auto s1 = AS_CPPSTRING(op1);
                         auto s2 = AS_CPPSTRING(op2);
                         push(ALLOC_STRING(s1 + s2));
                     }
                     break;
                 }

                 case OP_SUB: {
                     BINARY_OP(-);
                     break;
                 }
                 
                 case OP_MUL: {
                     BINARY_OP(*);
                     break;
                 }

                 case OP_DIV: {
                     BINARY_OP(/);
                     break;
                 }

                 default:
                     // TODO: i've tried use int(opcode) cause the value
                     // wasn't being printed at the console (just empty)
                     DIE << "Unknown opcode: " << std::hex << int(opcode);
             }
         }
     }


     /**
      * Instruction pointer (aka Program counter).
      */
     uint8_t* ip;

     /**
      * Stack pointer.
      */
     EvaValue* sp;

     /*
      * Operands stack.
      */
     std::array<EvaValue, STACK_LIMIT> stack;

     /**
      * Constant pool.
      */
     std::vector<EvaValue> constants;

     /**
      * Bytecode.
      */
     std::vector<uint8_t> code;
};

#endif

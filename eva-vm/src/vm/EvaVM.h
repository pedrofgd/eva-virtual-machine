/**
  * Eva Virtual Machine
  */

#ifndef EvaVM_h
#define EvaVM_h

#include <iostream>
#include <string>
#include <vector>
#include <array>

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
         
         constants.push_back(NUMBER(100));

         code = {OP_CONST, 0, OP_HALT};

         // Set instruction pointer to the beginning:
         ip = &code[0];

         // Set instruction pointer to the beginning:
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
                 case OP_CONST:
                     push(GET_CONST());
                     break;
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

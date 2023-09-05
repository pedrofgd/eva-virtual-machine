/**
 * Eva Virtual Machine
 */

#ifndef EvaVM_h
#define EvaVM_h

#include <iostream>
#include <string>
#include <vector>

#include "../Logger.h"
#include "../bytecode/OpCode.h"

/**
 * Reads the current byte in the bytecode
 * and advances the ip pointer
 */
#define READ_BYTE() *ip++

/**
 * Eva Virtual Machine
 */
class EvaVM {
    public:
        EvaVM() {}

        /**
         * Executes a program.
         */
        void exec(const std::string &program) {
            // 1. Parse the program into AST
            // auto ast = parser->parse(program)

            // 2. Compile program to Eva bytecode
            // code = compiler->compile(ast)
            
            code = {OP_HALT};
            
            // Set instruction pointer to the beginning:
            ip = &code[0];

            return eval();
        }

        /**
         * Main eval loop.
         */
        void eval() {
            for (;;) {
                auto opcode = READ_BYTE();
                log(opcode);
                switch (opcode) {
                    case OP_HALT:
                        return;
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
         * Bytecode.
         */
        std::vector<uint8_t> code;
};

#endif

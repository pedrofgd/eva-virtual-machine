/**
 * Instruction set architecture (ISA) for Eva VM.
 */

#ifndef OpCode_h
#define OpCode_h

/**
 * Stops the program.
 */
#define OP_HALT 0x00

/**
 * Pushes a const onto the stack.
 */
#define OP_CONST 0x01

/**
 * Add instruction.
 */
#define OP_ADD 0x02

/**
 * Subtraction instruction.
 */
#define OP_SUB 0x03

/**
 * Multiplication instruction.
 */
#define OP_MUL 0x04

/**
 * Division instruction
 */
#define OP_DIV 0x05

#endif

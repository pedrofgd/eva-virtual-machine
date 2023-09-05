/**
 * Logger and error reporter.
 */

#ifndef Logger_h
#define Logger_h

#include <iostream>
#include <sstream>

class ErrorLogMessage : public std::basic_ostringstream<char> {
    public:
        ~ErrorLogMessage() {
            std::cerr << "Fatal error: " << str().c_str() << "\n";
            exit(EXIT_FAILURE);
        }
};

#define DIE ErrorLogMessage()

// TODO: currently can't display hex value in iTerm2 (it's just empty)
#define log(value) std::cout << #value << " = " << (value) << "\n";

#endif

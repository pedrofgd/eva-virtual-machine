/**
 * Eva value
 */

enum class EvaValueType {
    NUMBER,
};

struct EvaValue {
    EvaValueType type;
    union {
        double number;
    };
};

// ---------------------------------------
// Constructors:

#define NUMBER(value) ((EvaValue){EvaValueType::NUMBER, .number = value})

// ---------------------------------------
// Accessors:

#define AS_NUMBER(evaValue) ((double)(evaValue).number)

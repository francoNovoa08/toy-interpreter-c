#ifndef ERRORS_H
#define ERRORS_H

typedef enum {
  SUCCESS = 0,
  PARSE_ERR_MEMORY_ALLOCATION, // Unable to build node from token
  PARSE_ERR_EXPECTED_NUMBER, // Cannot chain operators or start with non-number
  PARSE_ERR_EXPECTED_OPERATOR,         // Cannot chain operands together
  PARSE_ERR_SUBEXPRESSION_FAILED,      // Unable to parse multiplicative.
  PARSE_ERR_MISSING_BRACE,             // Missing left or right parenthesis
  PARSE_ERR_INVALID_ASSIGNMENT_TARGET, // Cannot assign to literal/expression
  EVALUATE_ERR_ZERO_DIVISION,          // Expression attempts to divide by zero.
  EVALUATE_ERR_UNKNOWN_NODE,           // Invalid AST Node
  EVALUATE_ERR_UNDEFINED_VARIABLE,     // A variable that doesn't exist is being
                                       // accessed
  EVALUATE_ERR_MEMORY_ALLOCATION // Unable to build variable name from ndoe
} ErrorCode;

const char *get_parser_error_message(ErrorCode code);

#endif // ERRORS_H
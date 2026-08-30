#include "utils/errors.h"

const char *get_error_message(ErrorCode code) {
  switch (code) {
  case SUCCESS:
    return "Success\n";
  case PARSE_ERR_MEMORY_ALLOCATION:
    return "System Error: Unable to allocate memory for AST node.\n";
  case PARSE_ERR_EXPECTED_NUMBER:
    return "Syntax Error: Expected a number, but got an operator or invalid "
           "token.\n";
  case PARSE_ERR_EXPECTED_OPERATOR:
    return "Syntax Error: Expected an operator (+, -, *, /) between numbers.\n";
  case PARSE_ERR_SUBEXPRESSION_FAILED:
    return "Syntax Error: Failed to parse sub-expression.\n";
  case PARSE_ERR_MISSING_BRACE:
    return "Syntax Error: Missing an opening or closing brace.\n";
  case PARSE_ERR_INVALID_ASSIGNMENT_TARGET:
    return "Syntax Error: Cannot assign target\n";
  case EVALUATE_ERR_ZERO_DIVISION:
    return "Syntax Error: Cannot divide by zero.\n";
  case EVALUATE_ERR_UNKNOWN_NODE:
    return "Syntax Error: Unknown node.\n";
  case PARSE_ERR_MISSING_CURLY_BRACE:
    return "Syntax Error: Expected a curly brace, { or }\n";
  case EVALUATE_ERR_UNDEFINED_VARIABLE:
    return "Syntax Error: Variable not defined\n";
  case EVALUATE_ERR_MEMORY_ALLOCATION:
    return "System Error: Unable to allocate memory for evaluation.\n";
  default:
    return "Unknown Error.\n";
  }
}
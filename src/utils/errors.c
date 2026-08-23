#include "utils/errors.h"

const char *get_parser_error_message(ErrorCode code) {
  switch (code) {
  case SUCCESS:
    return "Success";
  case PARSE_ERR_MEMORY_ALLOCATION:
    return "System Error: Unable to allocate memory for AST node.";
  case PARSE_ERR_EXPECTED_NUMBER:
    return "Syntax Error: Expected a number, but got an operator or invalid "
           "token.";
  case PARSE_ERR_EXPECTED_OPERATOR:
    return "Syntax Error: Expected an operator (+, -, *, /) between numbers.";
  case PARSE_ERR_SUBEXPRESSION_FAILED:
    return "Syntax Error: Failed to parse sub-expression.";
  case PARSE_ERR_MISSING_BRACE:
    return "Syntax Error: Missing an opening or closing brace.";
  case EVALUATE_ERR_ZERO_DIVISION:
    return "Syntax Error: Cannot divide by zero.";
  case EVALUATE_ERR_UNKNOWN_NODE:
    return "Syntax Error: Unknown node.";
  default:
    return "Unknown error.";
  }
}
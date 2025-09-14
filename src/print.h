/*

     🖨️PRINT✅
  Print and enjoy!

*/

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>

enum print_arg_type {
  PRINT_ARG__BOOL,
  PRINT_ARG__INT8,
  PRINT_ARG__UINT8,
  PRINT_ARG__INT16,
  PRINT_ARG__UINT16,
  PRINT_ARG__INT32,
  PRINT_ARG__UINT32,
  PRINT_ARG__INT64,
  PRINT_ARG__UINT64,
  PRINT_ARG__FLOAT,
  PRINT_ARG__DOUBLE,
  PRINT_ARG__CHAR_P,
  PRINT_ARG__VOID_P,
};

struct print_arg {
  const char flag;
  const int type;
  const void* value;
};

/*
  Format specifier using generic selector to use with printf-like functions.
*/

#ifndef print_custom_format_selector
#define print__format_selector(v)                                 \
  bool:       &(struct print_arg) { 0, PRINT_ARG__BOOL,   &(v) }, \
  int8_t:     &(struct print_arg) { 0, PRINT_ARG__INT8,   &(v) }, \
  uint8_t:    &(struct print_arg) { 0, PRINT_ARG__UINT8,  &(v) }, \
  int16_t:    &(struct print_arg) { 0, PRINT_ARG__INT16,  &(v) }, \
  uint16_t:   &(struct print_arg) { 0, PRINT_ARG__UINT16, &(v) }, \
  int32_t:    &(struct print_arg) { 0, PRINT_ARG__INT32,  &(v) }, \
  uint32_t:   &(struct print_arg) { 0, PRINT_ARG__UINT32, &(v) }, \
  int64_t:    &(struct print_arg) { 0, PRINT_ARG__INT64,  &(v) }, \
  uint64_t:   &(struct print_arg) { 0, PRINT_ARG__UINT64, &(v) }, \
  float:      &(struct print_arg) { 0, PRINT_ARG__FLOAT,  &(v) }, \
  double:     &(struct print_arg) { 0, PRINT_ARG__DOUBLE, &(v) }, \
  char*:      &(struct print_arg) { 0, PRINT_ARG__CHAR_P, &(v) }, \
  void*:      &(struct print_arg) { 0, PRINT_ARG__VOID_P, &(v) }
#else
#define print__format_selector(v)                                 \
  bool:       &(struct print_arg) { 0, PRINT_ARG__BOOL,   &(v) }, \
  int8_t:     &(struct print_arg) { 0, PRINT_ARG__INT8,   &(v) }, \
  uint8_t:    &(struct print_arg) { 0, PRINT_ARG__UINT8,  &(v) }, \
  int16_t:    &(struct print_arg) { 0, PRINT_ARG__INT16,  &(v) }, \
  uint16_t:   &(struct print_arg) { 0, PRINT_ARG__UINT16, &(v) }, \
  int32_t:    &(struct print_arg) { 0, PRINT_ARG__INT32,  &(v) }, \
  uint32_t:   &(struct print_arg) { 0, PRINT_ARG__UINT32, &(v) }, \
  int64_t:    &(struct print_arg) { 0, PRINT_ARG__INT64,  &(v) }, \
  uint64_t:   &(struct print_arg) { 0, PRINT_ARG__UINT64, &(v) }, \
  float:      &(struct print_arg) { 0, PRINT_ARG__FLOAT,  &(v) }, \
  double:     &(struct print_arg) { 0, PRINT_ARG__DOUBLE, &(v) }, \
  char*:      &(struct print_arg) { 0, PRINT_ARG__CHAR_P, &(v) }, \
  void*:      &(struct print_arg) { 0, PRINT_ARG__VOID_P, &(v) }, \
  default:    print_custom_format_selector(v)
#endif

#define f(v) \
  _Generic((v), print__format_selector(v))

void print__executor (
    void* stream,
    ...
)
{
  va_list args;
  va_start(args);

  struct print_arg* arg = va_arg(args, struct print_arg*);

  while (arg != nullptr) {

    if (arg->flag != 0) {
      fprintf(stream, "%s", (const char*) arg);

    } else {
      switch (arg->type) {
      case PRINT_ARG__BOOL:
        fprintf(stream, "%s", *((bool*) arg->value) ? "true" : "false");
        break;
      case PRINT_ARG__INT8:
        fprintf(stream, "%c", *((int8_t*) arg->value));
        break;
      case PRINT_ARG__UINT8:
        fprintf(stream, "%hhu", *((uint8_t*) arg->value));
        break;
      case PRINT_ARG__INT16:
        fprintf(stream, "%hd", *((int16_t*) arg->value));
        break;
      case PRINT_ARG__UINT16:
        fprintf(stream, "%hu", *((uint16_t*) arg->value));
        break;
      case PRINT_ARG__INT32:
        fprintf(stream, "%d", *((int32_t*) arg->value));
        break;
      case PRINT_ARG__UINT32:
        fprintf(stream, "%u", *((uint32_t*) arg->value));
        break;
      case PRINT_ARG__INT64:
        fprintf(stream, "%ld", *((int64_t*) arg->value));
        break;
      case PRINT_ARG__UINT64:
        fprintf(stream, "%lu", *((uint64_t*) arg->value));
        break;
      case PRINT_ARG__FLOAT:
        fprintf(stream, "%f", *((float*) arg->value));
        break;
      case PRINT_ARG__DOUBLE:
        fprintf(stream, "%f", *((double*) arg->value));
        break;
      case PRINT_ARG__CHAR_P:
        fprintf(stream, "%s", *((char**) arg->value));
        break;
      case PRINT_ARG__VOID_P:
        fprintf(stream, "%p", *((void**) arg->value));
        break;
      default:
#ifdef  print_custom_format_executor
        print_custom_format_executor(stream, (void*) arg);
#endif
        break;
      }
    }
  
    arg = va_arg(args, struct print_arg*); 
  }

  va_end(args);
}

#define print(...) \
  print__executor(stderr, __VA_OPT__(__VA_ARGS__,) "\n", nullptr)

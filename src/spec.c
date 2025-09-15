struct example1 {
  int a;
  float b;
};

struct example2 {
  char* c;
  bool d;
};

#include "print.h"

void print_struct_example1 (
    void* stream,
    struct example1* value
)
{
  printl("{ a: ", f(value->a), ", b: ", f(value->b), " }");
}

void print_struct_example2 (
    void* stream,
    struct example2* value
)
{
  printl("{ c: ", f(value->c), ", d: ", f(value->d), " }");
}

#undef  print_custom
#define print_custom(value)                                 \
  struct example1: print_arg(value, print_struct_example1), \
  struct example2: print_arg(value, print_struct_example2)

int main (
    int argc,
    char** argv
)
{
  int number = 0;
  print("my number is: ", f(number), ", but others would have said: ", f((int) { 42 }));

  struct example1 e1 = { 8, 1.1 };
  struct example2 e2 = { "zzz", true };
  print("example1: ", f(e1), ", example2: ", f(e2));

  return 0;
}

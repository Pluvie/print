#include "print_custom_types.h"

spec ( print_custom_types ) {

  when("the user defines custom print types") {
    #undef  print_custom
    #define print_custom(value)                                 \
      struct example1: print_arg(value, print_struct_example1), \
      struct example2: print_arg(value, print_struct_example2)

    must("print the formatted arguments using the custom functions");
      char output[1024] = { 0 };
      struct example1 e1 = { 8, 1.1 };
      struct example2 e2 = { "zzz", true };
      sprint(output, sizeof(output),
        "example1: ", f(e1), ", example2: ", f(e2));

    verify(strcmp(output,
      "example1: { a: 8, b: 1.100000 }, example2: { c: \"zzz\", d: true }") == 0);

    success();
  }; end();
}

#include "print_custom_types.h"

spec ( print_stream ) {

  argument(void* stream);

  precondition("a valid stream");
    #define stream_precondition \
      char output[1024] = { 0 }; \
      stream = fmemopen(output, sizeof(output), "w");

  precondition("a nullptr terminated list of variadic args");
    #define varargs_precondition \
      nullptr

  when("the variadic args are the default print types") {
    must("print the formatted arguments on the given stream");
      apply(stream_precondition);
      int number = 0;
      print_stream(stream, "my number is: ", f(number), apply(varargs_precondition));

    verify(strcmp(output, "my number is: 0"));

    success();
      fclose(stream);
  }; end();

  when("the variadic args are the custom defined print types") {
    #undef  print_custom
    #define print_custom(value)                                 \
      struct example1: print_arg(value, print_struct_example1), \
      struct example2: print_arg(value, print_struct_example2)

    must("print the formatted arguments on the given stream");
      apply(stream_precondition);
      struct example1 e1 = { 8, 1.1 };
      struct example2 e2 = { "zzz", true };
      print_stream(stream, "example1: ", f(e1), ", example2: ", f(e2), apply(varargs_precondition));

    verify(strcmp(output, "example1: { a: 8, b: 1.1 }, example2: { c: \"zzz\", d: true }"));

    success();
      fclose(stream);
  }; end();

  #undef stream_precondition
  #undef varargs_precondition
}

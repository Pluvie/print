spec ( print_variadic ) {

  argument(void* output);
  argument(int length);

  precondition("a nullptr terminated list of variadic args");
    #define varargs_precondition \
      nullptr

  when("printing on a stream") {
    #define stream_condition \
      char buffer[1024] = { 0 }; \
      output = fmemopen(buffer, sizeof(buffer), "w"); \
      length = -1;

    must("print the formatted arguments on the given stream");
      apply(stream_condition);
      int number = 0;
      print_variadic(output, -1,
        "my number is: ", f(number), apply(varargs_precondition));

    verify(strcmp(buffer, "my number is: 0") == 0);

    success();
      fclose(output);

    #undef stream_condition
  }; end();

  when("printing on a string") {
    #define string_condition \
      char buffer[1024] = { 0 }; \
      output = (void*) buffer; \
      length = sizeof(buffer);

    must("print the formatted arguments on the given string");
      apply(string_condition);

      int number = 0;
      print_variadic(output, length,
        "my number is: ", f(number), apply(varargs_precondition));

    verify(strcmp(output, "my number is: 0") == 0);

    success();

    #undef string_condition
  }; end();

  #undef varargs_precondition
}

struct example1 {
  int a;
  float b;
};

struct example2 {
  char* c;
  bool d;
};


int print_struct_example1 (
    void* output,
    int length,
    struct example1* value
)
{
  return print_variadic(output, length,
    "{ a: ", f(value->a), ", b: ", f(value->b), " }",
    nullptr);
}

int print_struct_example2 (
    void* output,
    int length,
    struct example2* value
)
{
  return print_variadic(output, length,
    "{ c: ", f(value->c), ", d: ", f(value->d), " }",
    nullptr);
}

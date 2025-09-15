struct example1 {
  int a;
  float b;
};

struct example2 {
  char* c;
  bool d;
};


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

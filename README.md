<div align="center">
  <h1>🖨️Print✅</h1>
  <h3>Enjoy your data!</h3>
</div>

## Introduction

🖨️Print✅ is a single-header C library to help you enjoy printing your data again. It
supports only C23 compatible compilers, but should work for every platform out there
that these compilers can target.

## Usage

Include the `print.h` file in your sources. Then start doing things like:

```c
int answer = 42;
float probability = 99.9;
print("answer? it is: ", f(number), " with ", f(probability), "% probability!");

// Shall print: "answer? it is: 42 with 99.9% probability!"
```

For printing and going to a new line: same as above but instead of `print` use `printl`.

It can also print on strings, using the same syntax with the `sprint` macro:

```c
char buffer[1024] = { 0 };
char* message = "hold my coffee"
sprint(buffer, sizeof(buffer), "this message must be stored: ", f(message));

// Buffer contains: "this message must be stored: hold my coffee"
```

## Customization

Let's say you have some structs in your program.

```c
struct example1 {
  int a;
  float b;
};

struct example2 {
  char* c;
  bool d;
};
```

You can define a custom print function for each of your types. These functions may
reutilize the `print_variadic` function of the library to maintain the same syntax.

```c
#include "print.h"

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
```

And then redefine the `print_custom` macro -- which by default does nothing -- to
dispatch the correct custom print function depending on the value type.

```c
#undef  print_custom
#define print_custom(value)                                 \
  struct example1: print_arg(value, print_struct_example1), \
  struct example2: print_arg(value, print_struct_example2)
```

Finally, you will be able to do:

```c
struct example1 e1 = { 8, 1.1 };
struct example2 e2 = { "zzz", true };
print("example1: ", f(e1), ", example2: ", f(e2));
// Shall print: "example1: { a: 8, b: 1.10000 }, example2: { c: "zzz", d: true }"
```

#include "print.h"
#include "print.c"
#include "spec.h"
#include "spec/print_variadic.c"
#include "spec/print_custom_types.c"

int main (
    int argc,
    char** argv
)
{
  spec_add( print_variadic );
  spec_add( print_custom_types );

  specs_run();

  if (specs_passed)
    return EXIT_SUCCESS;
  else
    return EXIT_FAILURE;
}

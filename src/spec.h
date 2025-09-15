#include <stdlib.h>
#include <string.h>

/*
  Defines a function specification.
*/
#define spec(function) \
  void spec__ ## function (void)

/*
  Registers a function specification.
*/
#define spec_add(function) \
  added_specs[added_specs_count] = spec__ ## function; \
  added_spec_names[added_specs_count] = #function; \
  added_specs_count++;

/*
  Focuses a function specification.
*/
#define spec_focus(function) \
  focused_specs[focused_specs_count] = spec__ ## function; \
  focused_spec_names[focused_specs_count] = #function; \
  focused_specs_count++;

/*
  Global variable that stores the final result of all specs.
*/
bool specs_passed = true;

/*
  Global variable that stores the original value of stderr.
  All specs by default suppresses any printout.
*/
void* sstream = nullptr;

/*
  Global variable that stores registered specs to be run.
*/
int added_specs_count = 0;
void (*added_specs[8192])(void) = { 0 };
char* added_spec_names[8192] = { 0 };

/*
  Global variable that stores focused specs to be run.
*/
int focused_specs_count = 0;
void (*focused_specs[16])(void) = { 0 };
char* focused_spec_names[16] = { 0 };



/*
  Defines a function specification argument.
*/
#define argument(...) \
  __VA_OPT__(__VA_ARGS__;)

/*
  Defines a function specification precondition.
*/
#define precondition(cond) \
  spec_print("given " cond);

/*
  Applies a function specification precondition.
*/
#define apply(...) \
  __VA_OPT__(__VA_ARGS__)

/*
  Defines a function specification codepath.
*/
#define when(cond) \
  spec_print("when " cond); \
  spec_indentation++;

/*
  Defines a function specification condition that must be verified.
*/
#define must(cond) \
  spec_print("must " cond " "); \
  spec_print_verification_enabled = true;

/*
  Verifies a condition.
*/
#define verify(cond) \
  if (!(cond)) { spec_failed(#cond, __FILE__, __LINE__ ); } else { spec_verified(); }

/*
  Defines a function specification codepath success.
*/
#define success() \
  spec_print_verification_enabled = false;

/*
  Ends a specification codepath.
*/
#define end() \
  spec_indentation--;

/*
  Holds the current indentation level.
*/
int spec_indentation = 0;

/*
  Global variable that enables/disables the printing of spec verifications.
*/
bool spec_print_verification_enabled = false;



/*
  Prints a spec text with indentation.
*/
void spec_print (
    const char* text
)
{
  fprintf(sstream, "\n");

  for (int i = 0; i < spec_indentation; i++)
    fprintf(sstream, "  ");
    
  fprintf(sstream, "%s", text);
}

/*
  Prints a failed spec condition.
*/
void spec_failed (
    const char* text,
    const char* file,
    int line
)
{
  specs_passed = false;
  fprintf(sstream, PRINT_COLOR_RED);
  fprintf(sstream, "█");
  fprintf(sstream, PRINT_COLOR_NONE);
  fprintf(sstream, "\n");
  for (int i = 0; i < spec_indentation; i++)
    fprintf(sstream, "  ");
  fprintf(sstream, PRINT_COLOR_RED);
  fprintf(sstream, "%s (%s:%i) ", text, file, line);
  fprintf(sstream, PRINT_COLOR_NONE);
}

/*
  Prints a verified spec condition.
*/
void spec_verified (
    void
)
{
  if (spec_print_verification_enabled) {
    fprintf(sstream, PRINT_COLOR_GREEN);
    fprintf(sstream, "█");
    fprintf(sstream, PRINT_COLOR_NONE);
  }
}

/* Runs the registered -- or focused -- specs. */
void specs_run (
    void
)
{
  sstream = fdopen(fileno(stderr), "w");

  if (focused_specs[0] == NULL) {
    stderr = fopen("/dev/null", "w");
    for (int i = 0; i < added_specs_count; i++) {
      spec_indentation = 0;
      fprintf(sstream, PRINT_COLOR_MAGENTA);
      fprintf(sstream, "\n%s", added_spec_names[i]);
      fprintf(sstream, PRINT_COLOR_NONE);
      fflush(sstream);
      spec_indentation = 1;
      added_specs[i]();
    }
  } else {
    for (int i = 0; i < focused_specs_count; i++) {
      spec_indentation = 0;
      fprintf(sstream, PRINT_COLOR_MAGENTA);
      fprintf(sstream, "\n%s", focused_spec_names[i]);
      fprintf(sstream, PRINT_COLOR_NONE);
      fflush(sstream);
      focused_specs[i]();
    }
  }

  if (specs_passed) {
    fprintf(sstream, "\n");
    fprintf(sstream, "\n");
    fprintf(sstream, PRINT_COLOR_GREEN);
    if (focused_specs[0] == NULL)
      fprintf(sstream, "Completed %i specs.\n", added_specs_count);
    else
      fprintf(sstream, "Completed %i focused spec(s).\n", focused_specs_count);
    fprintf(sstream, "All specs passed successfully.");
    fprintf(sstream, "\n");
    fprintf(sstream, PRINT_COLOR_NONE);
  } else {
    fprintf(sstream, "\n");
    fprintf(sstream, "\n");
    fprintf(sstream, PRINT_COLOR_RED);
    fprintf(sstream, "Some specs did not pass. Check for errors above.");
    fprintf(sstream, "\n");
    fprintf(sstream, PRINT_COLOR_NONE);
  }

  fclose(sstream);
  if (focused_specs[0] == NULL)
    fclose(stderr);
}

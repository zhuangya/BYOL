#include <stdio.h>
#include <stdlib.h>

/* If we are compiling on Windows compile there functions */
#ifdef _WIN32
#include <string.h>

static char buffer[2048];

/* Fake readline function */
char* readline (char* prompt) {
  fputs(prompt, stdout);
  fgets(buffer, 2048, stdin);
  char* cpy = malloc(strlen(buffer) + 1);
  strcpy(cpy, buffer);
  cpy[strlen(cpy) - 1] = '\0';
  return cpy;
}

/* fake add_history function */
void add_history(char* unused) {}

#else
  #include <editline/readline.h>
  #ifdef __linux__
    #include <editline/history.h>
  #endif
#endif

int main (int argc, char** argv) {

  /* Print Version and Exit Information */
  puts("YaLang Version 0.0.0.0.1");
  puts("There is no spoon");
  puts("Press Ctrl + c to Exit\n");

  /* In a never ending loop */
  while (1) {


    /* Output our prompt and get input */
    char* input = readline("YaLang> ");

    /* Add input to history */
    add_history(input);

    /* Echo input back to user */
    printf("May the force be with you: %s\n", input);

    /* Free retrieved input */
    free(input);
  }
  return 0;
}

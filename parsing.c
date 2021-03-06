#include <stdio.h>
#include <stdlib.h>
#include "deps/mpc/mpc.h"

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


  mpc_parser_t* Number = mpc_new("number");
  mpc_parser_t* Operator = mpc_new("operator");
  mpc_parser_t* Expr = mpc_new("expr");
  mpc_parser_t* Lispy = mpc_new("lispy");
  mpc_parser_t* Abba = mpc_new("abba");
  mpc_parser_t* Abab = mpc_new("abab");

  mpca_lang(MPCA_LANG_DEFAULT,
    "\
      abba: /[ab]+/; \
      abab: /(?:ab)a?/; \
      number: /-?[0-9]+/ ; \
      operator: '+' | '-' | '*' | '/'; \
      expr: <number> | '(' <operator> <expr>+ ')' ; \
      lispy: /^/ <abba> <operator> <expr>+ /$/ ; \
    ",
    Abba, Abab, Number, Operator, Expr, Lispy);


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

    mpc_result_t r;
    if (mpc_parse("<stdin>", input, Lispy, &r)) {
      /* On Success Print the AST */
      mpc_ast_print(r.output);
      mpc_ast_delete(r.output);
    } else {
      /* Otherwise Print the Error */
      mpc_err_print(r.error);
      mpc_err_delete(r.error);
    }

    /* Free retrieved input */
    free(input);
  }

  mpc_cleanup(4, Number, Operator, Expr, Lispy);
  return 0;
}

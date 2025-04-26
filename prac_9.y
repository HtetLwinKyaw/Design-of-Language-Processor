%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(const char *s);
%}

%token i t e a b

%%

S : i E t S S_prime
  | a
  ;

S_prime : e S
        | /* epsilon */
        ;

E : b
  ;

%%

int main() {
    if (yyparse() == 0) {
        printf("Valid string\n");
    } else {
        printf("Invalid string\n");
    }
    return 0;
}

int yylex() {
    int c = getchar();
    switch (c) {
        case 'i': return i;
        case 't': return t;
        case 'e': return e;
        case 'a': return a;
        case 'b': return b;
        case '\n': return 0; // End of input
        case ' ':
        case '\t':
        case '\r':
            return yylex(); // Skip whitespace
        default:
            return c; // Return character as token for error reporting if not recognized
    }
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
%{
#include <stdio.h>

int yywrap() { return 1; }  // Add this function to prevent linker error
%}

%%

charusat      printf("university");
.|\n          printf("%s", yytext);

%%

int main() {
    yylex();  // Start lexical analysis
    return 0;
}

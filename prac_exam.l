%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
%}

%%

[a-zA-Z]+(tion|ment|ness|ity|er|or)                                  { printf("%s ----- Noun\n", yytext); }
"he"|"she"|"it"|"they"|"we"|"you"|"I"                                { printf("%s ----- Pronoun\n", yytext); }

[a-zA-Z]+(ing|ed|en|ify|ize|lk|s)                                    { printf("%s ----- Verb\n", yytext); }
"am"|"is"|"are"|"was"|"were"|"be"|"been"|"being"|"have"|"has"|"had"  { printf("%s ----- Verb\n", yytext); }

[a-zA-Z]+ive                                                         { printf("%s ----- Adjective\n", yytext); }
[a-zA-Z]+ly                                                          { printf("%s ----- Adverb\n", yytext); }

"in"|"on"|"at"|"by"|"with"|"about"|"against"                         { printf("%s ----- Preposition\n", yytext); }
"and"|"but"|"or"|"nor"|"for"|"yet"|"so"                              { printf("%s ----- Conjunction\n", yytext); }

[a-zA-Z]+!                                 { printf("%s ----- Interjection\n", yytext); }

[.,!?"]+                                   { /* Ignore punctuation */ }
"a"|"an"|"the"
[a-zA-Z]+                                  { printf("%s ----- Noun\n", yytext); }
[ \t\n]+ ;                                 /* Ignore spaces and newlines */

%%

int main() {
    printf("Enter a paragraph:\n");
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}

%{
#include <stdio.h>
#include <ctype.h>

int char_count = 0, word_count = 0, line_count = 0;
int space_count = 0, tab_count = 0, special_char_count = 0;
extern FILE *yyin;  // Declare yyin for file input

int yywrap() { return 1; }  // Function to prevent linker error
%}

%%

// Count new lines
\n            { line_count++; char_count++; }  

// Count spaces
[ ]+          { space_count += yyleng; char_count += yyleng; }

// Count tabs
\t+           { tab_count += yyleng; char_count += yyleng; }

// Count words (letters, numbers, and underscores)
[a-zA-Z0-9_]+ { word_count++; char_count += yyleng; }

// Count special characters (excluding spaces, tabs, and newlines)
[^a-zA-Z0-9_ \t\n] { special_char_count++; char_count++; }

// Catch all characters
.             { char_count++; }

%%

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    yyin = file;
    yylex();
    fclose(file);

    printf("Total Characters: %d\n", char_count);
    printf("Total Words: %d\n", word_count);
    printf("Total Lines: %d\n", line_count);
    printf("Total Whitespace: %d\n", space_count);
    printf("Total Tabs: %d\n", tab_count);
    printf("Total Special Characters: %d\n", special_char_count);

    return 0;
}

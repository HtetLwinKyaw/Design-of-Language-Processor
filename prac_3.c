#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAX_IDENTIFIERS 100

// Define keywords
const char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if",
    "int", "long", "register", "return", "short", "signed", "sizeof", "static",
    "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
};

#define NUM_KEYWORDS (sizeof(keywords) / sizeof(keywords[0]))

// Symbol table
char symbol_table[MAX_IDENTIFIERS][50];
int symbol_count = 0;

int is_keyword(const char *word) {
    for (int i = 0; i < NUM_KEYWORDS; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void add_to_symbol_table(const char *identifier) {
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbol_table[i], identifier) == 0) {
            return;
        }
    }
    strcpy(symbol_table[symbol_count++], identifier);
}

void tokenize(FILE *file) {
    char buffer[50];
    int buffer_index = 0;
    char c;

    while ((c = fgetc(file)) != EOF) {
        // Skip white spaces
        if (isspace(c)) continue;

        // Check for preprocessor directives
        if (c == '#') {
            buffer_index = 0;
            buffer[buffer_index++] = c;
            while ((c = fgetc(file)) != EOF && !isspace(c)) {
                buffer[buffer_index++] = c;
            }
            buffer[buffer_index] = '\0';
            printf("Preprocessor: %s\n", buffer);
            while (c != EOF && c != '\n') c = fgetc(file);  // Skip to end of line
            continue;
        }

        // Check for comments
        if (c == '/' && (c = fgetc(file)) == '/') {
            while ((c = fgetc(file)) != '\n' && c != EOF);
            continue;
        }
        if (c == '/' && (c = fgetc(file)) == '*') {
            while (!((c = fgetc(file)) == '*' && (c = fgetc(file)) == '/')) {
                if (c == EOF) break;
            }
            continue;
        }

        // Check for punctuation
        if (ispunct(c) && c != '_' && c != '"' && c != '\'') {
            printf("Punctuation: %c\n", c);
            continue;
        }

        // Check for operators
        if (strchr("=+-*/%", c)) {
            printf("Operator: %c\n", c);
            continue;
        }

        // Check for string literals
        if (c == '"') {
            buffer_index = 0;
            buffer[buffer_index++] = c;
            while ((c = fgetc(file)) != '"') {
                if (c == '\\') buffer[buffer_index++] = c;  // Handle escape characters
                buffer[buffer_index++] = c;
            }
            buffer[buffer_index++] = '"';
            buffer[buffer_index] = '\0';
            printf("String: %s\n", buffer);
            continue;
        }

        // Check for identifiers and keywords
        if (isalpha(c) || c == '_') {
            buffer_index = 0;
            buffer[buffer_index++] = c;
            while (isalnum((c = fgetc(file))) || c == '_') {
                buffer[buffer_index++] = c;
            }
            buffer[buffer_index] = '\0';

            if (is_keyword(buffer)) {
                printf("Keyword: %s\n", buffer);
            } else {
                printf("Identifier: %s\n", buffer);
                add_to_symbol_table(buffer);
            }
            ungetc(c, file);
            continue;
        }

        // Check for constants
        if (isdigit(c)) {
            buffer_index = 0;
            buffer[buffer_index++] = c;
            while (isdigit((c = fgetc(file)))) {
                buffer[buffer_index++] = c;
            }
            buffer[buffer_index] = '\0';
            printf("Constant: %s\n", buffer);
            ungetc(c, file);
            continue;
        }
    }
}

void display_symbol_table() {
    printf("\nSYMBOL TABLE ENTRIES\n");
    for (int i = 0; i < symbol_count; i++) {
        printf("%d) %s\n", i + 1, symbol_table[i]);
    }
}

int main() {
    FILE *file = fopen("testcase_3_1.c", "r");
    if (!file) {
        printf("Error opening file\n");
        return 1;
    }

    printf("TOKENS\n");
    tokenize(file);

    display_symbol_table();

    fclose(file);
    return 0;
}

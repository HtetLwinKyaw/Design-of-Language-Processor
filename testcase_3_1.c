#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_KEYWORDS 32
#define MAX_IDENTIFIERS 100
#define MAX_CONSTANTS 100
#define MAX_STRINGS 100
#define MAX_OPERATORS 100
#define MAX_PUNCTUATION 100

// C keywords
const char *keywords[MAX_KEYWORDS] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do", "double",
    "else", "enum", "extern", "float", "for", "goto", "if", "int", "long",
    "register", "return", "short", "signed", "sizeof", "static", "struct", "switch",
    "typedef", "union", "unsigned", "void", "volatile", "while"
};

// Define symbol table arrays
char identifiers[MAX_IDENTIFIERS][256];
char constants[MAX_CONSTANTS][256];
char strings[MAX_STRINGS][256];
char operators[MAX_OPERATORS][256];
char punctuation[MAX_PUNCTUATION][256];
char keywordsFound[MAX_KEYWORDS][256];

int idIndex = 0, constIndex = 0, strIndex = 0, opIndex = 0, puncIndex = 0, kwIndex = 0;

// Check if a word is a keyword
int isKeyword(const char *word) {
    for (int i = 0; i < MAX_KEYWORDS; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Check if a word is a valid identifier
int isIdentifier(const char *word) {
    if (!isalpha(word[0]) && word[0] != '_') {
        return 0;
    }
    for (int i = 1; word[i] != '\0'; i++) {
        if (!isalnum(word[i]) && word[i] != '_') {
            return 0;
        }
    }
    return 1;
}

// Check if the word is a constant (integer or floating-point)
int isConstant(const char *word) {
    int hasDot = 0;
    for (int i = 0; word[i] != '\0'; i++) {
        if (isdigit(word[i]) == 0) {
            if (word[i] == '.' && !hasDot) {
                hasDot = 1;
            } else {
                return 0;
            }
        }
    }
    return 1;
}

// Check if the word is a valid string literal
int isStringLiteral(const char *word) {
    return word[0] == '"' && word[strlen(word) - 1] == '"';
}

// Check if the character is an operator
int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=' || ch == '<' || ch == '>' || ch == '%' || ch == '&' || ch == '|' || ch == '^');
}

// Check if the character is a punctuation mark
int isPunctuation(char ch) {
    return (ch == ',' || ch == ';' || ch == '(' || ch == ')' || ch == '{' || ch == '}' || ch == '[' || ch == ']' || ch == '.');
}

// Function to skip comments and white spaces
void skipCommentsAndWhitespace(FILE *file) {
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (isspace(ch)) continue;
        if (ch == '/' && (ch = fgetc(file)) == '/') {
            while (ch != '\n' && ch != EOF) ch = fgetc(file); // Skip till newline
            continue;
        }
        if (ch == '/' && (ch = fgetc(file)) == '*') {
            while ((ch = fgetc(file)) != EOF) {
                if (ch == '*' && (ch = fgetc(file)) == '/') break; // End of comment
            }
            continue;
        }
        ungetc(ch, file);
        break;
    }
}

int main() {
    FILE *file = fopen("testcase_3_1.c", "r");
    if (file == NULL) {
        printf("Error: Could not open file\n");
        return 1;
    }

    char word[256];
    int tokenCount = 0;

    // Tokenize and classify words
    while (fscanf(file, "%255s", word) == 1) {
        skipCommentsAndWhitespace(file);
        tokenCount++;

        if (isKeyword(word)) {
            if (kwIndex < MAX_KEYWORDS) {
                strcpy(keywordsFound[kwIndex++], word);
            }
        } else if (isIdentifier(word)) {
            if (idIndex < MAX_IDENTIFIERS) {
                strcpy(identifiers[idIndex++], word);
            }
        } else if (isConstant(word)) {
            if (constIndex < MAX_CONSTANTS) {
                strcpy(constants[constIndex++], word);
            }
        } else if (isStringLiteral(word)) {
            if (strIndex < MAX_STRINGS) {
                strcpy(strings[strIndex++], word);
            }
        } else if (isOperator(word[0])) {
            if (opIndex < MAX_OPERATORS) {
                strcpy(operators[opIndex++], word);
            }
        } else if (isPunctuation(word[0])) {
            if (puncIndex < MAX_PUNCTUATION) {
                strcpy(punctuation[puncIndex++], word);
            }
        }
    }

    fclose(file);

    // Print the token counts
    printf("Total Tokens: %d\n", tokenCount);

    // Print keywords
    printf("Keywords (%d):\n", kwIndex);
    for (int i = 0; i < kwIndex; i++) {
        printf("%s\n", keywordsFound[i]);
    }

    // Print identifiers
    printf("Identifiers (%d):\n", idIndex);
    for (int i = 0; i < idIndex; i++) {
        printf("%s\n", identifiers[i]);
    }

    // Print constants
    printf("Constants (%d):\n", constIndex);
    for (int i = 0; i < constIndex; i++) {
        printf("%s\n", constants[i]);
    }

    // Print string literals
    printf("String Literals (%d):\n", strIndex);
    for (int i = 0; i < strIndex; i++) {
        printf("%s\n", strings[i]);
    }

    // Print operators
    printf("Operators (%d):\n", opIndex);
    for (int i = 0; i < opIndex; i++) {
        printf("%s\n", operators[i]);
    }

    // Print punctuation
    printf("Punctuation (%d):\n", puncIndex);
    for (int i = 0; i < puncIndex; i++) {
        printf("%s\n", punctuation[i]);
    }

    return 0;
}

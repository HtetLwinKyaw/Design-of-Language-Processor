#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool validString(const char *str) {
    int len = strlen(str);

    // last 2 B
    if (len < 2 || str[len - 1] != 'b' || str[len - 2] != 'b') {
        return false;
    }

    // 0 to n-2 is a or not
    for (int i = 0; i < len - 2; i++) {
        if (str[i] != 'a') {
            return false;
        }
    }

    return true;
}

int main() {
    char input[20];

    printf("Enter a string: ");
    scanf("%s", input);

    if (validString(input)) {
        printf("The string is valid.\n");
    } else {
        printf("The string is invalid.\n");
    }

    return 0;
}

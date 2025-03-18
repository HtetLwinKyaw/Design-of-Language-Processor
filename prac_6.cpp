#include <iostream>
#include <string>

using namespace std;

int i = 0;         // Index for parsing the input string
string input;      // Input string to be validated

// Function Prototypes
bool S();
bool L();
bool LPrime();

// Function to skip spaces
void skipSpaces() {
    while (i < input.length() && input[i] == ' ') {
        i++;
    }
}

// S → ( L ) | a
bool S() {
    skipSpaces();
    if (i < input.length() && input[i] == 'a') {
        i++; // Consume 'a'
        return true;
    } else if (i < input.length() && input[i] == '(') {
        i++; // Consume '('
        skipSpaces();
        if (L()) {
            skipSpaces();
            if (i < input.length() && input[i] == ')') {
                i++; // Consume ')'
                return true;
            }
        }
    }
    return false;
}

// L → S L'
bool L() {
    if (S()) {
        skipSpaces();
        return LPrime();
    }
    return false;
}

// L' → , S L' | ε
bool LPrime() {
    skipSpaces();
    if (i < input.length() && input[i] == ',') {
        i++; // Consume ','
        skipSpaces();
        if (S()) {
            return LPrime();
        } else {
            return false;
        }
    }
    return true; // Epsilon (ε) transition
}

// Function to validate the input string
void validate(string str) {
    input = str;
    i = 0; // Reset index

    if (S() && i == input.length()) {
        cout << "Valid string" << endl;
    } else {
        cout << "Invalid string" << endl;
    }
}

// Main function to test the parser
int main() {
    string user_input;
    cout << "Enter a string to validate: ";
    getline(cin, user_input);  // Read full input including spaces

    validate(user_input);
    return 0;
}

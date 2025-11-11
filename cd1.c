// lexical analyzeer code with c program as input

#include <stdio.h>
#include <ctype.h>
#include <string.h>

void fn(char c[]) {
    int i, pos = 0;
    char lex[100];

    while (c[pos]) {
        char ch = c[pos];

        if (isspace(ch)) {
            pos++;
            continue;
        }

        i = 0;

        // Identifiers
        if (isalpha(ch)) {
            while (isalnum(c[pos])) {
                lex[i++] = c[pos++];
            }
            lex[i] = '\0';
            printf("IDENTIFIER: %s\n", lex);
        }

        // Numbers
        else if (isdigit(ch)) {
            while (isdigit(c[pos])) {
                lex[i++] = c[pos++];
            }
            lex[i] = '\0';
            printf("NUMBER: %s\n", lex);
        }

        // Operators
        else {
            if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' ||
                ch == '=' || ch == '<' || ch == '>' || ch == '!') {
                printf("OPERATOR: %c\n", ch);
            }

            // Punctuation
            else if (ch == '(' || ch == ')' || ch == '{' || ch == '}' ||
                     ch == ';' || ch == ',') {
                printf("PUNCTUATION: %c\n", ch);
            }

            // Unknown
            else {
                printf("UNKNOWN: %c\n", ch);
            }

            pos++;
        }
    }
}

int main() {
    char exp[200];

    printf("Enter C code snippet (empty line to finish):\n");

    while (fgets(exp, sizeof(exp), stdin)) {
        if (strcmp(exp, "\n") == 0)
            break;
        fn(exp);
    }

    return 0;
}

// OUTPUT:

// input of c program:

// int main()
// {
//     int total = count * rate;
//     if (total > 100)
//     {
//         return total;
//     }
// }

// IDENTIFIER: int
// IDENTIFIER: main
// PUNCTUATION: (
// PUNCTUATION: )
// PUNCTUATION: {
// IDENTIFIER: int
// IDENTIFIER: total
// OPERATOR: =
// IDENTIFIER: count
// OPERATOR: *
// IDENTIFIER: rate
// PUNCTUATION: ;
// IDENTIFIER: if
// PUNCTUATION: (
// IDENTIFIER: total
// OPERATOR: >
// NUMBER: 100
// PUNCTUATION: )
// PUNCTUATION: {
// IDENTIFIER: return
// IDENTIFIER: total
// PUNCTUATION: ;
// PUNCTUATION: }
// PUNCTUATION: }
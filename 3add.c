//3 address code

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100

int main() {
    char exp[MAX];
    char lhs;
    char rhs[MAX];
    char tokens[50][10];
    char code[50][50];
    int tokenCount = 0, codeCount = 0;
    int tcount = 1;

    printf("Enter expression (like a=b+c*d): ");
    scanf("%s", exp);

    lhs = exp[0];
    strcpy(rhs, exp + 2); // RHS after '='

    // Tokenize RHS into single characters
    for (int i = 0; i < strlen(rhs); i++) {
        char temp[10];
        temp[0] = rhs[i];
        temp[1] = '\0';
        strcpy(tokens[tokenCount++], temp);
    }

    // Handle * and /
    for (int i = 0; i < tokenCount; i++) {
        if (tokens[i][0] == '*' || tokens[i][0] == '/') {
            char tempVar[10];
            sprintf(tempVar, "t%d", tcount++);
            sprintf(code[codeCount++], "%s = %s %c %s", tempVar, tokens[i - 1], tokens[i][0], tokens[i + 1]);

            // Replace tokens i-1, i, i+1 with tempVar
            strcpy(tokens[i - 1], tempVar);
            for (int j = i; j < tokenCount - 2; j++)
                strcpy(tokens[j], tokens[j + 2]);
            tokenCount -= 2;
            i = -1; // restart
        }
    }

    // Handle + and -
    for (int i = 0; i < tokenCount; i++) {
        if (tokens[i][0] == '+' || tokens[i][0] == '-') {
            char tempVar[10];
            sprintf(tempVar, "t%d", tcount++);
            sprintf(code[codeCount++], "%s = %s %c %s", tempVar, tokens[i - 1], tokens[i][0], tokens[i + 1]);

            strcpy(tokens[i - 1], tempVar);
            for (int j = i; j < tokenCount - 2; j++)
                strcpy(tokens[j], tokens[j + 2]);
            tokenCount -= 2;
            i = -1; // restart
        }
    }

    // Final assignment
    sprintf(code[codeCount++], "%c = %s", lhs, tokens[0]);

    // Output TAC
    printf("\nThree Address Code:\n");
    for (int i = 0; i < codeCount; i++)
        printf("%s\n", code[i]);

    return 0;
}

// output:

// Enter expression (like a=b+c*d): a=b*c+d

// Three Address Code:
// t1 = b * c
// t2 = t1 + d
// a = t2

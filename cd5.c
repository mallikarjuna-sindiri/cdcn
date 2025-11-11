//Write a c-program to implement SLR Parser.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 50
// Grammar used:
// 1. E → E + T
// 2. E → T
// 3. T → T * F
// 4. T → F
// 5. F → (E)
// 6. F → i
//
// Input symbols: i + * ( ) $
// Start symbol: E
// Productions for reductions
char *production[] = {
" ",
// index starts at 1
"E->E+T", // 1
"E->T", // 2
"T->T*F", // 3
"T->F", // 4
"F->(E)", // 5
"F->i" // 6
};
// Parser stack
int stack[MAX];
int top = 0;
// Parsing table lookup function
const char *parsingTable[12][9] = {
{"S5", "", "", "S4", "", "", "1", "2", "3"},
{"", "S6", "", "", "", "Acc", "", "", ""},
{"", "R2", "S7", "", "R2", "R2", "", "", ""},
{"", "R4", "R4", "", "R4", "R4", "", "", ""},
{"S5", "", "", "S4", "", "", "8", "2", "3"},
{"", "R6", "R6", "", "R6", "R6", "", "", ""},
{"S5", "", "", "S4", "", "", "", "9", "3"},
{"S5", "", "", "S4", "", "", "", "", "10"},
{"", "S6", "", "", "S11", "", "", "", ""},
{"", "R1", "S7", "", "R1", "R1", "", "", ""},
{"", "R3", "R3", "", "R3", "R3", "", "", ""},
{"", "R5", "R5", "", "R5", "R5", "", "", ""}
};
// Function to get column index for terminal/nonterminal
int getSymbolIndex(char symbol) {
switch (symbol) {
case 'i': return 0;
case '+': return 1;
case '*': return 2;
case '(': return 3;
case ')': return 4;
case '$': return 5;
case 'E': return 6;
case 'T': return 7;
case 'F': return 8;
default: return -1;
}
}
int main() {
char input[50];
char symbol;
int i = 0;
printf("Grammar:\n");
for (int k = 1; k <= 6; k++)
printf("%d. %s\n", k, production[k]);
printf("\nEnter input string (end with $): ");
scanf("%s", input);
stack[top] = 0; // Initial state
printf("\nStack\t\tInput\t\tAction\n");
printf("------------------------------------------------\n");
while (1) {
int state = stack[top];
symbol = input[i];
int col = getSymbolIndex(symbol);
if (col == -1) {
printf("Error: Invalid symbol %c\n", symbol);
exit(1);
}
const char *action = parsingTable[state][col];
// Print current stack and input
for (int k = 0; k <= top; k++) printf("%d ", stack[k]);
printf("\t\t%s\t\t", &input[i]);
if (strcmp(action, "") == 0) {
printf("Error: No action found!\n");
exit(1);
} else if (action[0] == 'S') { // SHIFT
printf("Shift %c, go to state %c\n", symbol, action[1]);
top++;
stack[top] = symbol;
top++;
stack[top] = action[1] - '0';
i++;
} else if (action[0] == 'R') { // REDUCE
int prodNo = action[1] - '0';
char *rhs = strchr(production[prodNo], '>') + 1;
int len = strlen(rhs);
// Pop stack for each symbol on RHS
for (int k = 0; k < len * 2; k++)
top--;
char lhs = production[prodNo][0];
state = stack[top];
int lhsCol = getSymbolIndex(lhs);
const char *goTo = parsingTable[state][lhsCol];
printf("Reduce by %s, Go to state %s\n", production[prodNo], goTo);
top++;
stack[top] = lhs;
top++;
stack[top] = atoi(goTo);
} else if (strcmp(action, "Acc") == 0) {
printf("Accept!\nInput string accepted successfully.\n");
break;
} else {
printf("Error: Invalid action!\n");
exit(1);
}
}
return 0;
}
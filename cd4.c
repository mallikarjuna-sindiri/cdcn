//Write a c-program to implement LL(1) / predictive parser.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 10
// Grammar:
// E → T E'
// E' → + T E' | ε
// T → F T'
// T' → * F T' | ε
// F → (E) | id
// Terminals: +, *, (, ), id, $
char stack[50];
int top = -1;
void push(char c) {
stack[++top] = c;
}
char pop() {
if (top == -1)
return '\0';
return stack[top--];
}
char peek() {
if (top == -1)
return '\0';
return stack[top];
}
// Function to display the parsing step
void displayStackAndInput(char *input, int index) {
printf("\nStack: ");
for (int i = 0; i <= top; i++) printf("%c", stack[i]);
printf("\tInput: %s\t", &input[index]);
}
int main() {
char input[50];
int i = 0;
printf("Grammar used:\n");
printf("E -> T E'\n");
printf("E' -> + T E' | ε\n");
printf("T -> F T'\n");
printf("T' -> * F T' | ε\n");
printf("F -> (E) | i\n\n");
printf("Enter the input string (end with $): ");
scanf("%s", input);
push('$');
push('E');
printf("\nParsing Steps:\n");
while (input[i] != '\0') {
displayStackAndInput(input, i);
char topSymbol = peek();
char currentInput = input[i];
if (topSymbol == currentInput) {
printf("Action: Match %c", currentInput);
pop();
i++;
}
else if (topSymbol == 'E') {
printf("Action: E → T E'");
pop();
push('\'');
push('T');
}
else if (topSymbol == '\'') { // Represents E'
if (currentInput == '+') {
printf("Action: E' → + T E'");
pop();
push('\'');
push('T');
push('+');
} else {
printf("Action: E' → ε");
pop();
}
}
else if (topSymbol == 'T') {
printf("Action: T → F T'");
pop();
push('\"');
push('F');
}
else if (topSymbol == '\"') { // Represents T'
if (currentInput == '*') {
printf("Action: T' → * F T'");
pop();
push('\"');
push('F');
push('*');
}Else{:
printf("Action: T' → ε");
pop();
}
}
else if (topSymbol == 'F') {
if (currentInput == 'i') {
printf("Action: F → i");
pop();
push('i');
} else if (currentInput == '(') {
printf("Action: F → (E)");
pop();
push(')');
push('E');
push('(');
} else {
printf("Error: Invalid symbol for F");
exit(0);
}
}
else {
printf("Error: Invalid symbol or mismatch");
exit(0);
}
if (top == -1 && input[i] == '$') {
printf("\n\nString accepted successfully!\n");
return 0;
}
}
if (top == -1 && input[i] == '\0')
printf("\n\nString accepted successfully!\n");
else
printf("\n\nString rejected!\n");
return 0;
}
//Write a c-program to implement first and follow functions.
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 20
int n; // Number of productions
char production[MAX][MAX];
char firstSet[MAX][MAX];
char followSet[MAX][MAX];
char nonTerminals[MAX];
int m = 0; // Number of non-terminals
void findFirst(char, int, int);
void findFollow(char);
int isTerminal(char);
int isNonTerminal(char);
void addToResult(char[], char);
int main() {
int i, j;
char c, ch;
printf("Enter number of productions: ");
scanf("%d", &n);
printf("Enter the productions (e.g., E=TR):\n");
for (i = 0; i < n; i++) {
scanf("%s", production[i]);
nonTerminals[m++] = production[i][0];
}
printf("\n--- FIRST sets ---\n");
for (i = 0; i < n; i++) {
findFirst(production[i][0], 0, 0);
printf("FIRST(%c) = { %s }\n", production[i][0], firstSet[production[i][0] - 'A']);
}
printf("\n--- FOLLOW sets ---\n");
for (i = 0; i < n; i++) {
findFollow(production[i][0]);
printf("FOLLOW(%c) = { %s }\n", production[i][0], followSet[production[i][0] - 'A']);
}
return 0;
}
// Function to find FIRST set of a given non-terminal
void findFirst(char c, int q1, int q2) {
int j;
char subResult[20];
subResult[0] = '\0';
if (!isupper(c)) {
addToResult(firstSet[c - 'A'], c);
return;
}
for (j = 0; j < n; j++) {
if (production[j][0] == c) {
if (production[j][2] == '#')
addToResult(firstSet[c - 'A'], '#');
else if (islower(production[j][2]))
addToResult(firstSet[c - 'A'], production[j][2]);
else
findFirst(production[j][2], q1, q2);
}
}
}
// Function to find FOLLOW set of a non-terminal
void findFollow(char c) {
int i, j, k;
// Add '$' to FOLLOW(start symbol)
if (production[0][0] == c)
addToResult(followSet[c - 'A'], '$');
for (i = 0; i < n; i++) {
for (j = 2; j < strlen(production[i]); j++) {
if (production[i][j] == c) {
if (production[i][j + 1] != '\0') {
if (isupper(production[i][j + 1])) {
strcat(followSet[c - 'A'], firstSet[production[i][j + 1] - 'A']);
} else {
addToResult(followSet[c - 'A'], production[i][j + 1]);
}
}
if (production[i][j + 1] == '\0' && c != production[i][0])
findFollow(production[i][0]);
}
}
}
}
// Helper function to add symbol to result set
void addToResult(char result[], char val) {
int i;
for (i = 0; result[i] != '\0'; i++) {
if (result[i] == val)
return;
}
result[i] = val;
result[i + 1] = '\0';
}
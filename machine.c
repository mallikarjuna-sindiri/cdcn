//machine cde

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char value[10];
    struct Node *left, *right;
};

struct Node* createNode(char *v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->value, v);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void generateCode(struct Node* root) {
    if (root == NULL)
        return;

    generateCode(root->left);
    generateCode(root->right);

    if (!strcmp(root->value, "+") || !strcmp(root->value, "-") ||
        !strcmp(root->value, "*") || !strcmp(root->value, "/")) {
        printf("POP R2\n");
        printf("POP R1\n");
        printf("%s R1, R2\n", root->value);
        printf("PUSH R1\n");
    } else {
        printf("PUSH %s\n", root->value);
    }
}

int main() {
    // Expression: a = b + c * d
    // Construct AST manually
    struct Node* root = createNode("=");
    root->left = createNode("a");

    struct Node* plus = createNode("+");
    root->right = plus;

    plus->left = createNode("b");

    struct Node* mult = createNode("*");
    plus->right = mult;

    mult->left = createNode("c");
    mult->right = createNode("d");

    printf("Generated Machine Code:\n");
    generateCode(root->right);

    printf("POP R1\nSTORE R1, %s\n", root->left->value);

    return 0;
}


// output:
// Generated Machine Code:
// PUSH b
// PUSH c
// PUSH d
// POP R2
// POP R1
// * R1, R2
// PUSH R1
// POP R2
// POP R1
// + R1, R2
// PUSH R1
// POP R1
// STORE R1, a
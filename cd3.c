//first and follow

#include <ctype.h>
#include <stdio.h>
#include <string.h>

int count, n = 0;
char calc_first[20][100];
char calc_follow[20][100];
int m = 0;
char production[20][10];
char f[50], first[50];
int k;
char ck;
int e;

void follow(char c);

void followfirst(char c, int c1, int c2)
{
    int k;
    if (!(isupper(c))) {
        f[m++] = c;
    }
    else {
        int i = 0, j = 1;
        for (i = 0; i < count; i++) {
            if (calc_first[i][0] == c)
                break;
        }
        while (calc_first[i][j] != '!') {
            if (calc_first[i][j] != '#') {
                f[m++] = calc_first[i][j];
            }
            else {
                if (production[c1][c2] == '\0') {
                    follow(production[c1][0]);
                }
                else {
                    followfirst(production[c1][c2], c1, c2 + 1);
                }
            }
            j++;
        }
    }
}
void follow(char c)
{
    int i, j;
    if (production[0][0] == c) {
        f[m++] = '$';
    }
    for (i = 0; i < count; i++) {
        for (j = 2; production[i][j] != '\0'; j++) {
            if (production[i][j] == c) {
                if (production[i][j + 1] != '\0') {
                    followfirst(production[i][j + 1], i, j + 2);
                }
                if (production[i][j + 1] == '\0' && c != production[i][0]) {
                    follow(production[i][0]);
                }
            }
        }
    }
}
void findfirst(char c, int q1, int q2)
{
    int j;
    if (!(isupper(c))) {
        first[n++] = c;
        return;
    }
    for (j = 0; j < count; j++) {
        if (production[j][0] == c) {
            if (production[j][2] == '#') {
                if (production[q1][q2] == '\0') {
                    first[n++] = '#';
                }
                else if (production[q1][q2] != '\0' && (q1 != 0 || q2 != 0)) {
                    findfirst(production[q1][q2], q1, q2 + 1);
                }
                else {
                    first[n++] = '#';
                }
            }
            else if (!isupper(production[j][2])) {
                first[n++] = production[j][2];
            }
            else {
                findfirst(production[j][2], j, 3);
            }
        }
    }
}
int main()
{
    int jm = 0;
    int km = 0;
    int i;
    char c;
    printf("Enter number of productions: ");
    scanf("%d", &count);
    getchar(); 
    char temp_productions[50][10];
    int temp_count = 0;
    for (int idx = 0; idx < count; idx++) {
        char line[100];
        printf("Enter production %d (format: A=xyz): ", idx + 1);
        fgets(line, sizeof(line), stdin);

        int len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }
        char *lhs = strtok(line, "=");
        char *rhs = strtok(NULL, "=");

        if (lhs == NULL || rhs == NULL) {
            printf("Invalid production format! Use A=xyz\n");
            return 1;
        }
        char *part = strtok(rhs, "|");
        while (part != NULL) {
            snprintf(temp_productions[temp_count], sizeof(temp_productions[temp_count]), "%s=%s", lhs, part);
            temp_count++;
            part = strtok(NULL, "|");
        }
    }
    count = temp_count;
    for (int i = 0; i < count; i++) {
        strcpy(production[i], temp_productions[i]);
    }
    for (k = 0; k < count; k++) {
        for (int kay = 0; kay < 100; kay++) {
            calc_first[k][kay] = '!';
        }
    }
    char done[count];
    int ptr = -1;
    int point1 = 0, point2, xxx;
    for (k = 0; k < count; k++) {
        c = production[k][0];
        point2 = 0;
        xxx = 0;
        for (int kay = 0; kay <= ptr; kay++) {
            if (c == done[kay]) {
                xxx = 1;
                break;
            }
        }
        if (xxx == 1)
            continue;
        n = 0; 
        findfirst(c, 0, 0);
        ptr++;

        done[ptr] = c;
        printf("\nFirst(%c) = { ", c);
        calc_first[point1][point2++] = c;
        for (i = 0; i < n; i++) {
            int chk = 0;
            for (int lark = 0; lark < point2; lark++) {
                if (first[i] == calc_first[point1][lark]) {
                    chk = 1;
                    break;
                }
            }
            if (chk == 0) {
                printf("%c, ", first[i]);
                calc_first[point1][point2++] = first[i];
            }
        }
        printf("}\n");
        point1++;
    }
    printf("\n-----------------------------------------------\n\n");
    for (k = 0; k < count; k++) {
        for (int kay = 0; kay < 100; kay++) {
            calc_follow[k][kay] = '!';
        }
    }
    char donee[count];
    ptr = -1;
    point1 = 0;
    int land = 0;
    for (e = 0; e < count; e++) {
        ck = production[e][0];
        point2 = 0;
        xxx = 0;
        for (int kay = 0; kay <= ptr; kay++) {
            if (ck == donee[kay]) {
                xxx = 1;
                break;
            }
        }
        if (xxx == 1)
            continue;
        land++;
        m = 0; 
        follow(ck);
        ptr++;

        donee[ptr] = ck;
        printf("Follow(%c) = { ", ck);
        calc_follow[point1][point2++] = ck;
        for (i = 0; i < m; i++) {
            int chk = 0;
            for (int lark = 0; lark < point2; lark++) {
                if (f[i] == calc_follow[point1][lark]) {
                    chk = 1;
                    break;
                }
            }
            if (chk == 0) {
                printf("%c, ", f[i]);
                calc_follow[point1][point2++] = f[i];
            }
        }
        printf("}\n\n");
        point1++;
    }
    return 0;
}


//output
// Enter number of productions: 3E
// Enter production 1 (format: A=xyz): E=TR
// Enter production 2 (format: A=xyz): R=eTR|#
// Enter production 3 (format: A=xyz): T=i

// First(E) = { i, }

// First(R) = { e, #, }

// First(T) = { i, }

// -----------------------------------------------

// Follow(E) = { $, }

// Follow(R) = { $, }

// Follow(T) = { e, $, }
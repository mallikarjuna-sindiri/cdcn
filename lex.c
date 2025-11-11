//Write a lex program to count the number of vowels and consonants in the string.
%{
int vowels = 0, consonants = 0;
%}
%%
[aeiouAEIOU]
{ vowels++; }
[a-zA-Z]
{ consonants++; }
.|\n
{ /* ignore other characters */ }
%%
int main() {
printf("Enter a string: ");
yylex();
printf("\nNumber of vowels: %d", vowels);
printf("\nNumber of consonants: %d\n", consonants);
return 0;
}
int yywrap() {
return 1;
}
//Write a lex program for line count ,word count and character count.
%{
int lnno=0,wordno=0,charno=0;
%}
word [.* .*\t]
eol [\n]
%%
{word} {wordno++; charno+=yyleng;}
{eol} {charno++;lnno++;wordno++;}
. {charno++;}
%%
main()
{
printf("Enter the String:");
yylex();
printf("Line number= %d\n",lnno);
printf("Word number= %d\n",wordno);
printf("Character number= %d\n",charno);
return 0;
}
//Write a lex program to print “digit” whenever it receives the token from 0-9.
%{
#include<stdio.h>;
%}
%%
[0-9] {printf("Digit ");}
%%
int yywrap(void){}
void main()
{
printf("Enter the String:");
yylex();
}
//Write a lex program print * whenever it receives the token “3cse1”.
%{
#include<stdio.h>;
%}
%%
"3csec" {printf("*");}
%%
int yywrap(void){}
void main()
{
printf("Enter the String:");
yylex();
}
//Write a lex program for keyword recognition.
%{
#include <stdio.h>
#include <string.h>
int keyword_count = 0;
// List of C keywords
char *keywords[] = {
"auto", "break", "case", "char", "const", "continue", "default", "do",
"double", "else", "enum", "extern", "float", "for", "goto", "if",
"int", "long", "register", "return", "short", "signed", "sizeof",
"static", "struct", "switch", "typedef", "union", "unsigned", "void",
"volatile", "while"
};
int isKeyword(char *word) {
for (int i = 0; i < 32; i++) {
if (strcmp(keywords[i], word) == 0)
return 1;
}
return 0;
}
%}
%%
[a-zA-Z_][a-zA-Z0-9_]* {
if (isKeyword(yytext)) {
printf("Keyword: %s\n", yytext);
keyword_count++;
}
}
.|\n
{ /* ignore other characters */ }
%%
int main() {
printf("Enter the C code (Ctrl+D to end input):\n\n");
yylex();
printf("\nTotal number of keywords: %d\n", keyword_count);
return 0;
}
int yywrap() {
return 1;
}

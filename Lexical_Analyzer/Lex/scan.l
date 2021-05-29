%{
#include <stdlib.h>
void yyerror(char *);
/* simple demonstration*/
%}
%%
program | /*This rule is used to identify keywords in the Pascal Code*/
begin |
integer | 
uses | 
var |
writeln | 
for |
then |
else |
if |
to |
do |
end {printf("<keyword = %s > recognized\n",yytext);}

:= | /*This rule is used to identify operators in the Pascal Code*/
"+" |
"-" |
"*" |
"<" |
">" |
">=" |
"<=" |
"=" |
div |
mod {printf("<operator = %s > recognized\n",yytext);}

'[^']*' {printf("<string = %s > recognized\n",yytext);} /*This rule is used to identify string in the Pascal Code*/

[(,);\[\]] {printf("<delimiter = %s > recognized\n",yytext); } /*This rule is used to identify delimiters in the Pascal Code*/

[(][*][^*]*[*][)] {printf("<comment = %s > recognized\n",yytext); } /*This rule is used to identify comments in the Pascal Code*/

[0-9]+ {printf("<number = %s > recognized\n", yytext); } /*This rule is used to identify numbers in the Pascal Code*/

[a-zA-Z]+ {printf("<id = %s > recognized\n",yytext); } /*This rule is used to identify identifiers in the Pascal Code*/

[\t ]+ /*When tab is found in Pascal code then do nothing*/

[.|\n]+ /*When tab is found in Pascal code then do nothing*/
%%
int yywrap(void)
{
	return 1;
} 
int main()
{
	yylex();
	return 0;
}
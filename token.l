%{
    #include <stdlib.h>
    #include <stdbool.h>
    #include <string.h>

    #include "y.tab.h"
    #include "syntax.h"
    
    Lexval lexval;
    int line = 1;

%}

%option noyywrap

spacing		([ \t])+
comment		\-\-[^\n]*
sugar		[;:()\[\],\+\-\*/<=>]
letter		[a-zA-Z]
digit		[0-9]
notzero		[1-9]
sign 		\-|\+
intconst	{sign}?({notzero}{digit}*|0)
realconst	{intconst}\.{digit}+
strconst	\"[^\n\"]*\"
boolconst	true|false
id 		{letter}({letter}|{digit})*

%%

{spacing}		;
{comment}		;
\n 			{ line++; }
integer			{ return(INTEGER); }
real			{ return(REAL); }
string			{ return(STRING); }
boolean			{ return(BOOLEAN); }
create			{ return(CREATE); }
project			{ return(PROJECT); }
select			{ return(SELECT); }
join			{ return(JOIN); }
update			{ return(UPDATE); }
extend			{ return(EXTEND); }
rename			{ return(RENAME); }
and			{ return(AND); }
or			{ return(OR); }
not			{ return(NOT); }
read			{ return(READ); }
write			{ return(WRITE); }
":="			{ return(ASSIGN); }
"="			{ return(EQ); }
"!="			{ return(NE); }
">="			{ return(GE); }
">"                     { return(GT); }
"<"                     { return(LT); }
"<="			{ return(LE); }
"+"                     { return(PLUS); }
"-"                     { return(MINUS); }
"*"                     { return(TIMES); }
"/"                     { return(OBELUS); }
{intconst}		{
                            lexval.ival = atoi(yytext);
                            return(INTCONST);
                        }
{realconst}		{
                            lexval.rval = atof(yytext);
                            return(REALCONST);
                        }
{strconst}		{
                            lexval.sval = strdup(yytext);
                            return(STRCONST);
					
			}
{boolconst}		{
                            lexval.ival = (yytext[0] == 'f' ? false : true);
                            return(BOOLCONST);
                        }
{id}			{
                            lexval.sval = strdup(yytext);
                            return(ID);
                        }
{sugar}			{ return(yytext[0]); }
.			{ return(ERROR); }
%%

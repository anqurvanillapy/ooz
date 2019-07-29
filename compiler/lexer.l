%option noyywrap
%option nounput
%option noinput

%{
#include <stdio.h>

#define YY_DECL int yylex()

#include "parser.yy.h"

%}

%x C_COMMENT

%%

[ \t\r\n]   ;

"(*"            { BEGIN(C_COMMENT); }
<C_COMMENT>"*)" { BEGIN(INITIAL); }
<C_COMMENT>\n   {}
<C_COMMENT>.    {}

"::"        { return T_TYPEOF; }
"->"        { return T_ARROW; }
"="         { return T_ASSIGN; }
"("         { return T_LPAREN; }
")"         { return T_RPAREN; }
"\\"        { return T_LAMBDA; }
";"         { return T_SEMICOLON; }
[A-Za-z][A-Za-z0-9']*   { yylval.strval = yytext; return T_IDENT; }

%%

%option noyywrap
%option nounput
%option noinput
%option yylineno

%{

#include <stdio.h>

#define YY_DECL int yylex()

#include "parser.yy.h"

static void update_yylloc(YYLTYPE *loc, const char *txt);

#define YY_USER_ACTION update_yylloc(&yylloc, yytext);

int last_token;
int paren_depth;

%}

%x C_COMMENT

%%

[ \t\r]     ;

"(*"            { BEGIN(C_COMMENT); }
<C_COMMENT>"*)" { BEGIN(INITIAL); }
<C_COMMENT>\n   {}
<C_COMMENT>.    {}

"\n" {
    // Optional semicolon.
    if (paren_depth == 0 && (last_token == T_IDENT || last_token == T_RPAREN)) {
        last_token = T_SEMICOLON;
        return last_token;
    }
}

"::"        { last_token = T_TYPEOF; return last_token; }
"->"        { last_token = T_ARROW; return last_token; }
"="         { last_token = T_ASSIGN; return last_token; }
"("         { ++paren_depth; last_token = T_LPAREN; return last_token; }
")"         { --paren_depth; last_token = T_RPAREN; return last_token; }
"\\"        { last_token = T_LAMBDA; return last_token; }
";"         { last_token = T_SEMICOLON; return last_token; }

[A-Za-z][A-Za-z0-9']*   {
    last_token = T_IDENT;
    yylval.strval = yytext;
    return last_token;
}

%%

static void
update_yylloc(YYLTYPE *loc, const char *txt) {
    int i;

    loc->first_line = loc->last_line;
    loc->first_column = loc->last_column;

    for (i = 0; txt[i] != '\0'; ++i) {
        if (txt[i] == '\n') {
            ++loc->last_line;
            loc->last_column = 0;
        } else {
            ++loc->last_column;
        }
    }
}

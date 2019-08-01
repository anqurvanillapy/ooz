%{

#include <stdio.h>
#include <stdlib.h>

#include "lib/abstract.h"
#include "lib/codegen.h"

extern FILE *yyin;

void yyerror(const char *s);
int yylex();

%}

%locations
%error-verbose

%union{
    char *strval;
    expr_t *expr;
}

%token<strval> T_IDENT
%token T_MODULE T_WHERE
%token T_TYPEOF T_ARROW T_ASSIGN T_LPAREN T_RPAREN T_LAMBDA T_SEMICOLON

%left T_ARROW

%type<expr> expr lambda_func

%start top

%%

top
    :
    | stmts
    | module
    | module stmts
    ;

stmts
    : stmts stmt
    | stmt
    ;

module
    : T_MODULE T_IDENT T_WHERE
    {
        char *name = lex_substr($2, @2.last_column - @2.first_column);
        abs_set_module(name);
    }
    ;

stmt
    : decl
    | def
    ;

decl
    : T_IDENT T_TYPEOF typexpr T_SEMICOLON
    ;

typexpr
    : T_IDENT
    | T_LPAREN typexpr T_RPAREN
    | typexpr T_ARROW typexpr
    ;

def
    : T_IDENT T_ASSIGN expr T_SEMICOLON
    {
        char *name = lex_substr($1, @1.last_column - @1.first_column);
        abs_def_check_boundfree(name, $3);
        abs_ctx_add(name, $3);
    }
    ;

expr
    : lambda_func
    {
        $$ = $1;
    }
    | T_IDENT
    {
        char *name = lex_substr($1, @1.last_column - @1.first_column);
        expr_t *var = abs_var_new(@1.first_line, @1.last_column, name);
        $$ = var;
    }
    | T_IDENT expr
    {
        char *name = lex_substr($1, @1.last_column - @1.first_column);
        expr_t *var = abs_var_new(@1.first_line, @1.last_column, name);
        var->next = $2;
        $$ = var;
    }
    | T_LPAREN expr T_RPAREN
    {
        $$ = $2;
    }
    | T_LPAREN expr T_RPAREN expr
    {
        expr_t* expr = $2;
        expr->next = $4;
        $$ = expr;
    }
    ;

lambda_func
    : T_LAMBDA T_IDENT T_ARROW expr
    {
        char *name = lex_substr($2, @2.last_column - @2.first_column);
        $$ = abs_lam_new(@4.first_line, @4.last_column, name, $4);
    }
    ;

%%

static const char *filename;

int
main(int argc, const char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: oozc FILE\n");
        exit(1);
    }

    filename = argv[1];
    yyin = fopen(filename, "r");
    if (yyin == NULL) {
        perror("fopen");
        exit(1);
    }

    abs_init(filename);

    yyparse();
    fclose(yyin);

    cg_init(filename);
    cg_writefile();

    return 0;
}

void
yyerror(const char *s) {
    fprintf(stderr, "%s:%d:%d: Parse error: %s\n",
            filename, yylloc.first_line, yylloc.last_column, s);
    exit(1);
}

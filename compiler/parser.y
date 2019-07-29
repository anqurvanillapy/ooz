%{

#include <stdio.h>
#include <stdlib.h>

extern FILE *yyin;

void yyerror(const char *s);
int yylex();

%}

%locations
%error-verbose

%union{
    char *strval;
}

%token<strval> T_IDENT
%token T_MODULE T_WHERE
%token T_TYPEOF T_ARROW T_ASSIGN T_LPAREN T_RPAREN T_LAMBDA T_SEMICOLON

%left T_ARROW

%start top

%%

top :
    | stmts
    | module
    | module stmts
    ;

stmts : stmts stmt
      | stmt
      ;

module : T_MODULE T_IDENT T_WHERE { printf("%s\n", $2); }
       ;

stmt : decl
     | def
     ;

decl : T_IDENT T_TYPEOF typexpr T_SEMICOLON { printf("%s\n", $1); }
     ;

typexpr : T_IDENT
        | T_LPAREN typexpr T_RPAREN
        | typexpr T_ARROW typexpr
        ;

def : T_IDENT T_ASSIGN expr T_SEMICOLON { printf("%s\n", $1); }
    ;

expr : lambda_func
     | T_IDENT
     | T_LPAREN expr T_RPAREN
     | T_LPAREN expr T_RPAREN expr
     ;

lambda_func : T_LAMBDA T_IDENT T_ARROW expr
            ;

%%

const char *filename;

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

    yyparse();
    fclose(yyin);

    return 0;
}

void
yyerror(const char *s) {
    fprintf(stderr, "Parse error: %s:%d:%d: %s\n",
            filename, yylloc.first_line, yylloc.last_column, s);
    exit(1);
}

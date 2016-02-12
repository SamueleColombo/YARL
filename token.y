%{
    #include <stdio.h>
    #include "syntax.h"
    #include "parser.h"
    //#include "tree_print.h"

    #define YYSTYPE PNode
    
    extern char * yytext;
    extern Lexval lexval;
    extern FILE *yyin;
    extern int line;

    PNode root = NULL;
%}

%token INTEGER REAL STRING BOOLEAN 
%token ID ASSIGN
%token CREATE PROJECT SELECT UPDATE EXTEND RENAME JOIN 
%token READ WRITE  
%token AND OR NE GE LE NOT			
%token INTCONST REALCONST STRCONST BOOLCONST 
%token ERROR	
	
%left AND OR
%nonassoc EQ NE GE GT LT LE
%left PLUS MINUS
%left TIMES OBELUS
%right NEG NOT

%%
program 	: stat_list {root = $$ = nonTerminalNode(NT_PROGRAM); $$->child = $1;}
                ;
			
stat_list	: stat ';' stat_list {$$ = $1; $1->brother = $3;}
                | stat ';' {$$ = $1;}
                ;
			
stat		: def_stat {$$ = nonTerminalNode(NT_STAT);  $$->child = $1;}
                | assign_stat {$$ = nonTerminalNode(NT_STAT); $$->child = $1;}
                | read_stat {$$ = nonTerminalNode(NT_STAT); $$->child = $1;}
                | write_stat {$$ = nonTerminalNode(NT_STAT); $$->child = $1;}
                ;
			
def_stat	: CREATE id_list '(' attr_list ')' {$$ = nonTerminalNode(NT_DEF_STAT); $$->child = $2; last($2)->brother = $4;}
                ;
			
id_list		: ID {$$ = idNode();} ',' id_list {$$ = $2; $2->brother = $4;}
                | ID {$$ = idNode();}
                ;
			
attr_list	: attr_decl ',' attr_list {$$ = $1; $1->brother = $3;}
                | attr_decl {$$ = $1;}
                ;

attr_decl	: ID {$$ = idNode();} ':' type {$$ = $2; $2->child = $4;}
                ;

type 		: INTEGER {$$ = keyNode(TP_INTEGER);}
                | REAL {$$ = keyNode(TP_REAL);}
                | STRING {$$ = keyNode(TP_STRING);}
                | BOOLEAN {$$ = keyNode(TP_BOOLEAN);}
                ;

assign_stat	: ID {$$ = idNode();} ASSIGN rel_expr {$$ = nonTerminalNode(NT_ASSIGN_STAT); $$->child = $2; $$->child->brother = $4;}
                ;

rel_expr	: project_expr {$$ = nonTerminalNode(NT_REL_EXPR); $$->child = $1;}
                | select_expr {$$ = nonTerminalNode(NT_REL_EXPR); $$->child = $1;}
                | join_expr {$$ = nonTerminalNode(NT_REL_EXPR); $$->child = $1;}
                | update_expr {$$ = nonTerminalNode(NT_REL_EXPR); $$->child = $1;}
                | extend_expr {$$ = nonTerminalNode(NT_REL_EXPR); $$->child = $1;}
                | rename_expr {$$ = nonTerminalNode(NT_REL_EXPR); $$->child = $1;}
                | '(' rel_expr ')' {$$ = $2;}
                | ID { $$ = nonTerminalNode(NT_REL_EXPR); $$->child = idNode();}
                ;
			
project_expr    : PROJECT '[' id_list ']' rel_expr {$$ = nonTerminalNode(NT_PROJECT_EXPR); $$->child = $3; last($3)->brother = $5;}
                ;

select_expr	: SELECT '[' expr ']' rel_expr {$$ = nonTerminalNode(NT_SELECT_EXPR); $$->child = $3; $3->brother = $5;}
                ;
			
join_expr	: JOIN '[' expr ']' rel_expr rel_expr {$$ = nonTerminalNode(NT_JOIN_EXPR); $$->child = $3; /*$$->brother = nonTerminalNode(NT_JOIN_PARAM); $$->brother->child = $5; $$->brother->brother = $6;*/ $3->brother = $5; $5->brother = $6; }
                ;
			
update_expr	: UPDATE '[' ID { $$ = idNode(); } ASSIGN expr ']' rel_expr { $$ = nonTerminalNode(NT_UPDATE_EXPR); $$->child = $4; $$->child->brother = $6; $6->brother = $8;}
                ;
			
extend_expr     : EXTEND '[' ID { $$ = idNode(); } ':' type ASSIGN expr ']' rel_expr { $$ = nonTerminalNode(NT_EXTEND_EXPR); $$->child = $4; $$->child->brother = $6; $$->child->brother->brother = $8; $8->brother = $10; }
                ;
			
rename_expr :   RENAME '[' id_list ']' rel_expr {$$ = nonTerminalNode(NT_RENAME_EXPR); $$->child = $3; last($3)->brother = $5;}
                ;
			
expr 		: expr bool_op bool_term	{$$ = $2; $2->child = $1; $2->child->brother = $3;/*$2->child = $3; $2->brother = $1;*/}
                | bool_term {$$ = $1;}
                ;

bool_op		: AND {$$ = operationNode(AND);}
                | OR {$$ = operationNode(OR);}
                ;
			
bool_term 	: comp_term comp_op comp_term {$$ = $2; $2->child = $1; /*$2->brother = $3;*/$2->child->brother = $3;}
                | comp_term {$$ = $1;}
                ;
			
comp_op		: EQ {$$ = operationNode(EQ);}
                | NE {$$ = operationNode(NE);}
                | GT {$$ = operationNode(GT);}
                | GE {$$ = operationNode(GE);}
                | LT {$$ = operationNode(LT);}
                | LE {$$ = operationNode(LE);}
                ;

comp_term	: comp_term low_bin_op low_term {$$ = $2; $2->child = $1; $2->child->brother = $3;/*$2->child = $3;  $2->brother = $1;*/}
                | low_term {$$ = $1;}
                ;

low_bin_op	: PLUS {$$ = operationNode(PLUS);}
                | MINUS {$$ = operationNode(MINUS);}
                ;

low_term	: low_term high_bin_op factor {$$ = $2;  $2->child = $1; $2->child->brother = $3;/*$2->brother = $1; $2->child = $3;*/}
                | factor {$$ = $1;}
                ;

high_bin_op	: TIMES {$$ = operationNode(TIMES);}
                | OBELUS {$$ = operationNode(OBELUS);}
                ;

factor		: unary_op factor {$$ = $1; $1->child = $2; }
                | '(' expr ')' {$$ = $2; }
                | ID { $$ = idNode(); } {$$ = $2; }
                | simple_const { $$ = $1; }
                ;

simple_const	: INTCONST { $$ = intconstNode(); }
                | STRCONST { $$ = strconstNode(); }
                | REALCONST { $$ = realconstNode(); }
                | BOOLCONST { $$ = boolconstNode(); }
                ;

unary_op	: MINUS %prec NEG {$$ = operationNode(NEG); }
                | NOT 	{$$ = operationNode(NOT); }
                ;


read_stat 	: READ specifier ID {$$ = idNode();} { $$ = nonTerminalNode(NT_READ_STAT); $$->child = $2; $$->child->brother = $4; }
                ;

specifier	: '[' expr ']'	{$$ = nonTerminalNode(NT_SPECIFIER); $$->child = $2; }
                | /* epsilon */ {$$ = nonTerminalNode(NT_SPECIFIER);} 
                ;

write_stat 	: WRITE specifier rel_expr { $$ = nonTerminalNode(NT_WRITE_STAT); $$->child = $2; $$->child->brother = $3; }
                ;
%%

main()
{
    // Intro
    printf("Type something followed by Return. Type 'q' or 'Q' to end.\n");
    printf("\n");
    // Start the parser
    return(yyparse());
}

yyerror(s)
char *s;
{
    printf("yacc error: %s\n", s);
}

yywrap()
{
    return(0);
}


/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "syntax.h"
#include "y.tab.h"

char * tabtypes[] ={
    "NONTERMINAL",
    "ID",
    "INTEGER",
    "REAL",
    "STRING",
    "BOOLEAN",
    "OPERATION",
    "INTCONST",
    "REALCONST",
    "STRINGCONST",
    "BOOLCONST"
};

char * tabnonterm[] ={
    "PROGRAM",
    "STAT",
    "DEF_STAT",
    "ASSIGN_STAT",
    "PROJECT_EXPR",
    "SELECT_EXPR",
    "JOIN_EXPR",
    "UPDATE_EXPR",
    "EXTEND_EXPR",
    "RENAME_EXPR",
    "READ_STAT",
    "SPECIFIER",
    "WRITE_STAT",
    "REL_EXPR"
};

void treeprint(PNode root, int indent) 
{
    int i;
    PNode p;

    for (i = 0; i < indent; i++)
        printf("    ");
    printf("%s", (root->type == TP_NONTERMINAL ? tabnonterm[root->value.ival] : tabtypes[root->type]));
    if (root->type == TP_ID || root->type == TP_STRCONST)
        printf(" (%s)", root->value.sval);
    else if (root->type == TP_INTCONST)
        printf(" (%d)", root->value.ival);
    else if (root->type == TP_REALCONST)
        printf(" (%f)", root->value.rval);
    else if (root->type == TP_BOOLCONST)
        printf(" (%s)", (root->value.bval == true ? "true" : "false"));
    else if (root->type == TP_OPERATION)
        if (root->value.ival < 255)
            printf(" (%c)", (char) root->value.ival);
        else {
            switch (root->value.ival) {
                case AND: printf(" (and)");
                    break;
                case OR: printf(" (or)");
                    break;
                case EQ: printf(" (=) ");
                    break;
                case NE: printf(" (!=)");
                    break;
                case GE: printf(" (>=)");
                    break;
                case LE: printf(" (<=)");
                    break;
                case NOT: printf(" (not)");
                    break;
                case MINUS: printf(" (-)");
                    break;
                case LT: printf(" (<) ");
                    break;
                case GT: printf(" (>) ");
                    break;
                case PLUS: printf(" (+) ");
                    break;
                case TIMES: printf(" (*) ");
                    break;
                case OBELUS: printf(" (/) ");
                    break;
                case NEG: printf(" (NEG) ");
                    break;
                default: printf(" (EEEEEEEERRRRRRRRRRRROOORRE)");
                    break;
            }
        }
    printf("\n");

    for(p = root->child; p != NULL; p = p->brother) 
    {
        treeprint(p, indent + 1);
    }
}

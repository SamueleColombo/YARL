/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   syntax.h
 * Author: Samuele Colombo
 *
 * Created on 12 febbraio 2016, 10.29
 */

#ifndef SYNTAX_H
#define SYNTAX_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

    typedef union {
        int ival;
        char *sval;
        float rval;
        bool bval;
    } Lexval;

    typedef enum {
        TP_NONTERMINAL,
        TP_ID,
        TP_INTEGER,
        TP_REAL,
        TP_STRING,
        TP_BOOLEAN,
        TP_OPERATION,
        TP_INTCONST,
        TP_REALCONST,
        TP_STRCONST,
        TP_BOOLCONST
    } TypeNode;

    typedef enum {
        NT_PROGRAM,
        NT_STAT,
        NT_DEF_STAT,
        NT_ASSIGN_STAT,
        NT_PROJECT_EXPR,
        NT_SELECT_EXPR,
        NT_JOIN_EXPR,
        NT_UPDATE_EXPR,
        NT_EXTEND_EXPR,
        NT_RENAME_EXPR,
        NT_READ_STAT,
        NT_SPECIFIER,
        NT_WRITE_STAT,
        NT_REL_EXPR
    } NonTerminal;

    struct s_table;

    typedef struct snode {
        TypeNode type;
        int expr_type;
        Lexval value;
        int line;
        struct snode *child, *brother;
        struct s_table * currentTable;
        int attr_rel_expr; //indica dove andare a prendere attributo se da prima (1) o seconda (2) rel_expr
    } Node;

    typedef Node * PNode;

    PNode parse();


#ifdef __cplusplus
}
#endif

#endif /* SYNTAX_H */


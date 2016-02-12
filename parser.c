/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "parser.h"

extern int line;
extern Lexval lexval;

PNode newNode(TypeNode tnode) {
    PNode p = malloc(sizeof (Node));
    p->type = tnode;
    p->line = line;
    p->child = p->brother = NULL;
    return (p);
}

PNode nonTerminalNode(NonTerminal nt) {
    PNode p = newNode(TP_NONTERMINAL);
    p->value.ival = nt;
    return (p);
}

PNode keyNode(TypeNode keyword) {
    return newNode(keyword);
}

PNode idNode() {
    PNode p = newNode(TP_ID);
    p->value.sval = lexval.sval;
    return p;
}

PNode operationNode(int code) {
    PNode p = newNode(TP_OPERATION);
    p->value.ival = code;
    return p;
}

PNode last(PNode p) {
    PNode last = p;
    while (last->brother != NULL) {
        last = last->brother;
    }
    return last;
}

PNode intconstNode() {
    PNode p = newNode(TP_INTCONST);
    p->value.ival = lexval.ival;
    return p;
}

PNode realconstNode() {
    PNode p = newNode(TP_REALCONST);
    p->value.rval = lexval.rval;
    return p;
}

PNode strconstNode() {
    PNode p = newNode(TP_STRCONST);
    p->value.sval = lexval.sval;
    return p;
}

PNode boolconstNode() {
    PNode p = newNode(TP_BOOLCONST);
    p->value.bval = lexval.bval;
    return p;
}
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   parser.h
 * Author: Samuele Colombo
 *
 * Created on 12 febbraio 2016, 10.26
 */

#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>
#include "syntax.h"

#ifdef __cplusplus
extern "C" {
#endif

PNode newNode(TypeNode tnode);
PNode nonTerminalNode(NonTerminal nt);
PNode keyNode(TypeNode keyword);
PNode idNode();
PNode operationNode(int code);
PNode last(PNode p);
PNode intconstNode();
PNode strconstNode();
PNode realconstNode();
PNode boolconstNode();


#ifdef __cplusplus
}
#endif

#endif /* PARSER_H */


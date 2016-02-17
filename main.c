/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Samuele Colombo
 *
 * Created on 12 febbraio 2016, 10.47
 */

#include <stdio.h>
#include <stdlib.h>

#include "syntax.h"
#include "semantic.h"
#include "dtable/d_cell.h"
#include "interpreter.h"

/*
 * 
 */
int main(int argc, char ** argv) 
{
    FILE * file = fopen("prog", "r");
    
    PNode node = parse(file);
    treeprint(node, 0);
    semantic(node);
    interpreter(node);
    
    return (EXIT_SUCCESS);
}


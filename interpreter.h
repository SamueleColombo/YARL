/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   interpreter.h
 * Author: Samuele Colombo
 *
 * Created on 15 febbraio 2016, 19.50
 */

#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <stdio.h>
#include <stdlib.h>

#include "darray/d_array.h"
#include "dtable/d_table.h"
#include "dtable/d_cell.h"

#ifdef __cplusplus
extern "C" {
#endif

    void interpreter(PNode node);
    void interpreter_def_stat(PNode def_stat);
    void interpreter_assign_stat(PNode assign_stat);
    void interpreter_read_stat(PNode read_stat);
    void interpreter_write_stat(PNode write_stat);



#ifdef __cplusplus
}
#endif

#endif /* INTERPRETER_H */


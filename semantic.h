/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   semantic.h
 * Author: Samuele Colombo
 *
 * Created on 12 febbraio 2016, 11.06
 */

#ifndef SEMANTIC_H
#define SEMANTIC_H

#include <stdlib.h>
#include <stdbool.h>

#include "syntax.h"
#include "darray/d_array.h"
#include "dtable/d_cell.h"
#include "dtable/d_table.h"

#ifdef __cplusplus
extern "C" {
#endif
   
    void semantic(PNode node);
    void semantic_def_stat(PNode def_stat);
    void semantic_assign_stat(PNode assign_stat);
    d_table * semantic_rel_expr(PNode rel_expr);
    d_table * semantic_project(PNode project_expr);
    d_table * semantic_select(PNode select_expr);
    d_table * semantic_join(PNode join_expr);
    d_table * semantic_update(PNode update_expr);
    d_table * semantic_extend(PNode extend_expr);
    d_table * semantic_rename(PNode rename_expr);
    d_type semantic_expr(PNode expr, d_table * table_one, d_table * table_two);
    void semantic_read_stat(PNode read_stat);
    void semantic_write_stat(PNode write_stat);
    
    PNode next_rel_expr(PNode rel_expr);


#ifdef __cplusplus
}
#endif

#endif /* SEMANTIC_H */


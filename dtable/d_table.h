/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   d_table.h
 * Author: Samuele Colombo
 *
 * Created on 11 febbraio 2016, 18.55
 */

#ifndef D_TABLE_H
#define D_TABLE_H

#include <stdlib.h>
#include "d_cell.h"
#include "../darray/d_array.h"

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct d_table
    {
        char * name;
        
        size_t rows;
        size_t cols;
        size_t row_size;
        size_t col_size;
        
        d_array * columns;
        d_cell ** table;
        
    }
    d_table;

    d_table * d_table_new(char * name);
    d_table * d_table_new_sized(char * name, size_t initial_row_size, size_t initial_col_size);
    void d_table_free(d_table * table);
    
    
    d_table * d_table_exist(d_array * array, char * name);

#ifdef __cplusplus
}
#endif

#endif /* D_TABLE_H */


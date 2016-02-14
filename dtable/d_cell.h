/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   d_cell.h
 * Author: Samuele Colombo
 *
 * Created on 11 febbraio 2016, 18.58
 */

#ifndef D_CELL_H
#define D_CELL_H

#include <stdbool.h>
#include "../syntax.h"

#ifdef __cplusplus
extern "C" {
#endif

    typedef enum d_type
    {
        D_INTEGER = TP_INTEGER,
        D_FLOAT = TP_REAL,
        D_STRING = TP_STRING,
        D_BOOLEAN = TP_BOOLEAN
    } 
    d_type;
    
    typedef struct d_cell
    {
        union
        {
            int ival;
            float rval;
            char * sval;
            bool bval;
        } value;
        
        d_type type;
        bool is_empty;
    }
    d_cell;


#ifdef __cplusplus
}
#endif

#endif /* D_CELL_H */


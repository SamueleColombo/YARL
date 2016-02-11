/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   d_array.h
 * Author: Samuele Colombo
 *
 * Created on 11 febbraio 2016, 16.02
 */

#ifndef D_ARRAY_H
#define D_ARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

    
    typedef struct d_array
    {
        size_t length;
        size_t element_size;
        size_t array_size;
        
        void * array;
    }
    d_array;
    
    d_array * d_array_new(size_t element_size);
    d_array * d_array_new_sized(size_t element_size, size_t initial_size);
    void d_array_free(d_array * array);
    bool d_array_realloc(d_array * array);
    bool d_array_push(d_array * array, void * data);
    bool d_array_remove(d_array * array, int index);
    bool d_array_set(d_array * array, void * data, int index);
    void * d_array_get(d_array * array, int index);


#ifdef __cplusplus
}
#endif

#endif /* D_ARRAY_H */


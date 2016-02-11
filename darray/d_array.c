/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "d_array.h"

/**
 * 
 * @param element_size
 * @return 
 */
d_array * d_array_new(size_t element_size)
{
    return d_array_new_sized(element_size, 10);
}

/**
 * 
 * @param element_size
 * @param initial_size
 * @return 
 */
d_array * d_array_new_sized(size_t element_size, size_t initial_size)
{
    d_array * array;
    
    array = (d_array *) malloc(sizeof(d_array));
    
    array->element_size = element_size;
    array->array_size = initial_size;
    array->length = 0;
    
    return array;
}

/**
 * 
 * @param array
 */
void d_array_free(d_array * array)
{
    free(array->array);
    free(array);
}

/**
 * 
 * @param array
 * @return 
 */
bool d_array_realloc(d_array * array)
{
    void * data;
    
    data = realloc(array->array, array->element_size * array->array_size * 2);
    
    if(data)
    {
        array->array_size++;
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * 
 * @param array
 * @param data
 * @return 
 */
bool d_array_push(d_array * array, void * data)
{
    int offset;
    
    if(array->length + 1 > array->array_size)
    {
        d_array_realloc(array);
    }
    
    offset = array->element_size * array->length;
    memcpy(array->array + offset, data, array->element_size);
    array->length++;
    
    return true;
}

bool d_array_remove(d_array * array, int index)
{
    int replacement, offset;
    
    if(index < 0 || index > array->length) return false;
    
    if(array->length <= 0) return true;
    
    if(index == array->length - 1)
    {
        array->length--;
        return true;
    }
    
    offset = array->element_size * index;
    replacement = array->element_size * (index + 1);
    memmove(array->array + offset, array->array + replacement, offset - replacement);
    
    return true;  
}

/**
 * 
 * @param array
 * @param data
 * @param index
 * @return 
 */
bool d_array_set(d_array * array, void * data, int index)
{
    int offset;
    
    if(index < 0) return false;
    
    if(index > array->array_size)
    {
        d_array_realloc(array);
        return d_array_set(array, data, index);
    }
    
    offset = array->element_size * index;
    memcpy(array->array + offset, data, array->element_size);
    
    return true;
}

/**
 * 
 * @param array
 * @param index
 * @return 
 */
void * d_array_get(d_array * array, int index)
{
    int offset;
    
    if(index < 0 || index > array->length) return NULL;
    offset = array->element_size * index;
    return array->array + offset;
}




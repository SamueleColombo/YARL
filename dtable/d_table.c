/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "d_table.h"

/**
 * 
 * @param name
 * @return 
 */
d_table * d_table_new(char * name)
{
    return d_table_new_sized(name, 10, 10); 
}

/**
 * 
 * @param name
 * @param initial_row_size
 * @param initial_col_size
 * @return 
 */
d_table * d_table_new_sized(char * name, size_t initial_row_size, size_t initial_col_size)
{
    int r;
    d_table * table;
    
    table = (d_table *) malloc(sizeof(d_table));
    
    table->name = name;
    table->rows = 0;
    table->rows = 0;
    table->row_size = initial_row_size;
    table->col_size = initial_col_size;
    
    // Initialize columns array
    table->columns = d_array_new_sized(sizeof(d_cell), table->col_size);
    
    // Initialize data multi-array
    table->table = (d_cell **) malloc(sizeof(d_cell *) * table->row_size);
    
    for(r = 0; r < table->row_size; r++)
    {
        table->table[r] = (d_cell *) malloc(sizeof(d_cell) * table->col_size);
    }
    
    return table;
}

/**
 * 
 * @param table
 */
void d_table_free(d_table * table)
{
    int r;
    
    for(r = 0; r < table->row_size; r++)
    {
        free(table->table[r]);
    }
    
    d_array_free(table->columns);
    free(table->table);
    free(table);
}

/**
 * 
 * @param table
 * @return 
 */
bool d_table_realloc_rows(d_table * table)
{
    void * data;
    
    data = realloc(table->table, sizeof(d_cell *) * table->row_size * 2);
    
    if(!data) return false;
   
    table->row_size *= 2;
    free(data);
    
    return true;

}

/**
 * 
 * @param table
 * @return 
 */
bool d_table_realloc_columns(d_table * table)
{
    int r;
    void * data;
    
    if(d_array_realloc(table->columns) == false) return false;
    
    for(r = 0; r < table->row_size; r++)
    {
        data = realloc(table->table[r], sizeof(d_cell) * table->col_size * 2);
        
        if(!data) return false;
    }
    
    table->col_size *= 2;
    free(data);
    
    return true;   
}

/**
 * 
 * @param table
 * @param name
 * @return 
 */
int d_table_get_index_column(d_table * table, char * name)
{
    int c;
    
    if(table->columns->length == 0) return -1;
    
    for(c = 0; c < table->columns->length; c++)
    {
        d_cell * column = d_array_get(table->columns, c);
        
        if(column != NULL && strcmp(column->value.sval, name) == 0)
        {
            return c;
        }
        
    }
    
    return -1;
}

/**
 * 
 * @param table
 * @param column
 * @return 
 */
bool d_table_alter(d_table * table, d_cell * column)
{
    int cindex;
    
    cindex = d_table_get_index_column(table, column->value.sval);
    
    if(cindex != -1) return false;
    
    if(table->cols + 1 > table->col_size)
    {
        if(d_table_realloc_columns(table) == false) return false;
    }
    
    d_array_push(table->columns, column);
    
    table->cols = table->columns->length;
    table->col_size = table->columns->capacity;
    
    return true;    
}

/**
 * 
 * @param table
 * @param row
 * @return 
 */
bool d_table_insert(d_table * table, d_array * new_row)
{
    int c;
    
    //if(table->cols != new_row->length || table->cols == 0) return false;
    
    if(table->rows + 1 > table->row_size)
    {
        if(d_table_realloc_rows(table) == false) return false;
    }
    
    for(c = 0; c < new_row->length; c++)
    {
        d_cell * new_cell = d_array_get(new_row, c);
        table->table[table->rows][c] = *new_cell;
    }
    
    return true;
}

/**
 * 
 * @param array
 * @param name
 * @return 
 */
d_table * d_table_exist(d_array * array, char * name)
{
    int i;
    d_table * table;
    
    for(i = 0; i < array->length; i++)
    {
        table = d_array_get(array, i);
        
        if(strcmp(table->name, name) == 0)
        {
            return table;
        }
    }
    
    return NULL;
}

bool d_table_match(d_table * dst, d_table * src)
{
    int i, j;
    
    if(dst->columns->length != src->columns->length) return false;
    
    for(i = 0; i < dst->columns->length; i++)
    {
        d_cell * src_cell = d_array_get(src->columns, i);
        d_cell * dst_cell = d_array_get(dst->columns, i);
        
        if(dst_cell->type != src_cell->type)
        {
            return false;
        }
    }
    
    return true;
}

void d_table_clone_struct(d_table * dst, d_table * src)
{
    int i;
    d_cell * old;
    d_cell new;
    
    for(i = 0; i < src->columns->length; i++)
    {
        old = d_array_get(src->columns, i);
        new = *old;
        d_array_push(dst->columns, &new);  
    }
}



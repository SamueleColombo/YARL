/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "interpreter.h"

extern d_array * symbol_table;

void interpreter(PNode node)
{
    if(node->type == TP_NONTERMINAL)
    {
        switch(node->value.ival)
        {
            case NT_PROGRAM:
                interpreter(node->child);
                break;
                
            case NT_STAT:
                interpreter(node->child);
                if(node->brother != NULL) interpreter(node->brother);
                break;
                
            case NT_DEF_STAT:
                interpreter_def_stat(node->child);
                break;
                
            case NT_ASSIGN_STAT:
                interpreter_assign_stat(node->child);
                break;
                
            case NT_READ_STAT:
                interpreter_read_stat(node->child);
                break;
                
            case NT_WRITE_STAT:
                interpreter_write_stat(node->child);
                break;
                
        }
    }
}

void interpreter_def_stat(PNode def_stat)
{
    
}

void interpreter_assign_stat(PNode assign_stat)
{
    
}

void interpreter_read_stat(PNode read_stat)
{
    FILE * read;
    PNode current;
    char line[1024];
    
    current = read_stat;
    
    /*if(file_exist(current->child->value.sval) == false)
    {
        fprintf(stderr, "Runtime error on line %d", current->line);
        fprintf(stderr, "The file %s file doesn't exist", current->child->value.sval);
        exit(EXIT_FAILURE);
    }*/
    
    read = fopen("data", "r");
    
    while (fgets(line, 1024, read))
    {
        char* tmp = strdup(line);
        int i = get_type(tmp, 1);
        free(tmp);
    }
    
    
}

void interpreter_write_stat(PNode write_stat)
{
    
}
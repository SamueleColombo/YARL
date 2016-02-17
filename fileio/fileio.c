/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "fileio.h"

/**
 * 
 * @param line
 * @param delimiter
 * @param end
 * @param index
 * @return 
 */
const char * get_token(const char * line, const char * delimiter, const char * end, int index)
{
    const char * token;
    
    for(token = strtok(line, delimiter); token && *token; token = strtok(NULL, end))
    {
        if(!--index) return token;
    }
    
    return NULL;
}

/**
 * 
 * @param line
 * @param index
 * @return 
 */
int get_type(const char * line, int index)
{
    const char * head;
    const char * type;
    
    head = get_token(line, ";", ";\n", index);
    type = get_token(head, ":", "", 2);
    
    return type[0] - '0'; 
}

/**
 * 
 * @param filename
 * @return 
 */
bool file_exist(const char * filename)
{
    FILE * file;
    
    if(file = fopen(filename, "r"))
    {
        fclose(file);
        return true;
    }
    
    return false;
}

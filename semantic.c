/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "semantic.h"
#include "y.tab.h"

d_array * symbol_table = NULL;

char * tabtypes2[] ={
    "NONTERMINAL",
    "ID",
    "INTEGER",
    "REAL",
    "STRING",
    "BOOLEAN",
    "OPERATION",
    "INTCONST",
    "REALCONST",
    "STRINGCONST",
    "BOOLCONST"
};

char * tabnonterm2[] ={
    "PROGRAM",
    "STAT",
    "DEF_STAT",
    "ASSIGN_STAT",
    "PROJECT_EXPR",
    "SELECT_EXPR",
    "JOIN_EXPR",
    "UPDATE_EXPR",
    "EXTEND_EXPR",
    "RENAME_EXPR",
    "READ_STAT",
    "SPECIFIER",
    "WRITE_STAT",
    "REL_EXPR"
};

void semantic(PNode node)
{
    if(symbol_table == NULL) symbol_table = d_array_new(sizeof(d_table));
    
    if(node->type == TP_NONTERMINAL)
    {
        switch(node->value.ival)
        {
            case NT_PROGRAM:
                semantic(node->child);
                break;
                
            case NT_STAT:
                semantic(node->child);
                if(node->brother != NULL) semantic(node->brother);
                break;
                
            case NT_DEF_STAT:
                semantic_def_stat(node->child);
                break;
                
            case NT_ASSIGN_STAT:
                semantic_assign_stat(node->child);
                break;
                
            case NT_READ_STAT:
                semantic_read_stat(node->child);
                break;
                
            case NT_WRITE_STAT:
                semantic_write_stat(node->child);
                break;
        }
    }
}

void semantic_def_stat(PNode def_stat)
{
    int i;
    PNode current = def_stat;
    
    d_array * tables = d_array_new(sizeof(d_table));
    d_table * table;
    
    while(current->brother != NULL && current->child == NULL)
    {
        table = d_table_new(current->value.sval);
        
        if(d_table_exist(symbol_table, current->value.sval) != NULL)
        {
            fprintf(stderr, "Semantic error on line %d\n", current->line);
            fprintf(stderr, "[Table: %s] A table with the same name already exists in the symbol table\n", current->value.sval);
            exit(EXIT_FAILURE);
        }
        
        if(d_table_exist(tables, current->value.sval) != NULL)
        {
            fprintf(stderr, "Semantic error on line %d\n", current->line);
            fprintf(stderr, "[Table: %s] A table with the same name already exists in the this line\n", current->value.sval);
            exit(EXIT_FAILURE);
        }
        
        d_array_push(tables, table);
        
        current = current->brother;
        
        //d_table_free(table);
    }
    
    do
    {
        for(i = 0; i < tables->length; i++)
        {
            table = d_array_get(tables, i);
            
            if(d_table_get_index_column(table, current->value.sval) != -1)
            {
                fprintf(stderr, "Semantic error on line %d\n", current->line);
                fprintf(stderr, "[Table: %s][Attribute: %s] An attribute with the same name already exists in this table\n", table->name, current->value.sval);
                exit(EXIT_FAILURE);
            }
           
            d_cell cell = {.value.sval = current->value.sval, .type = current->child->type, .is_empty = true };
            d_table_alter(table, &cell);
              
            //d_table_free(table);
        }
    }
    while((current = current->brother) != NULL);
    
    //d_array_free(tables);
    d_array_merge(symbol_table, tables);
}


void semantic_assign_stat(PNode assign_stat)
{
    PNode current;
    d_table * lhs;
    d_table * rhs;
    
    current = assign_stat;
    
    if((lhs = d_table_exist(symbol_table, current->value.sval)) == NULL)
    {
        fprintf(stderr, "Semantic error on line %d\n", current->line);
        fprintf(stderr, "[Table: %s] Try to assign a table that wasn't decleare previously\n", current->value.sval);
        exit(EXIT_FAILURE);
    }
    
    rhs = semantic_rel_expr(assign_stat->brother->child);
    
    if(d_table_match(lhs, rhs) == false)
    {
        fprintf(stderr, "Semantic error on line %d\n", current->line);
        fprintf(stderr, "[Table: %s] Assigned table and the performed one doesn't match\n", current->value.sval);
        exit(EXIT_FAILURE);
    }
    
    
}

d_table * semantic_rel_expr(PNode rel_expr)
{
    PNode current;
    d_table * result;
    
    current = rel_expr;
    
    if(current->type == TP_ID)
    {
        if((result = d_table_exist(symbol_table, current->value.sval)) == NULL)
        {
            fprintf(stderr, "Semantic error on line %d\n", current->line);
            fprintf(stderr, "[Table: %s] Try to assign a table that wasn't decleare previously\n", current->value.sval);
            exit(EXIT_FAILURE);
        }
        
        return result;
    }
    else
    {
       switch(current->value.ival)
       {
           case NT_PROJECT_EXPR:
                return semantic_project(current->child);
                
            case NT_SELECT_EXPR:
                return semantic_select(current->child);
                
            case NT_JOIN_EXPR:
                return semantic_join(current->child);
                
            case NT_UPDATE_EXPR:
                return semantic_update(current->child);
                
            case NT_EXTEND_EXPR:
                return semantic_extend(current->child);
                
            case NT_RENAME_EXPR:
                return semantic_rename(current->child);
       }
    }
}

/**
 * 
 * @param project_expr
 * @return 
 */
d_table * semantic_project(PNode project_expr)
{
    PNode current;
    PNode next;
    d_table * output;
    d_table * input;
    
    current = project_expr;
    next = next_rel_expr(current);
    
    output = d_table_new(NULL);
    input = semantic_rel_expr(next->child);
    
    while(current != next)
    {
        // Check if the attribute from syntax tree exits on the current table
        if(d_table_get_index_column(input, current->value.sval) == -1)
        {
            fprintf(stderr, "Semantic error on line %d\n", current->line);
            //fprintf(stderr, "[Table: %s][Attribute: %s] \n", current->value.sval);
            exit(EXIT_FAILURE);
        }
        
        // Create temporary cell 
        d_cell cell = {.value.sval = current->value.sval, .type = current->type, .is_empty = true };
        
        // Add the current attribute to the selected table
        if(d_table_alter(output, &cell) == false)
        {
            fprintf(stderr, "Semantic error on line %d\n", current->line);
            //fprintf(stderr, "[Table: %s][Attribute: %s] \n", current->value.sval);
            exit(EXIT_FAILURE);
        }
        
        current = current->brother;
    }
    
    return output;
}

d_table * semantic_select(PNode select_expr)
{
    PNode current;
    PNode next;
    
    d_table * output;
    d_table * input;
    
    current = select_expr;
    next = next_rel_expr(current);
    
    output = d_table_new(NULL);
    input = semantic_rel_expr(next->child);
    
    if(semantic_expr(current, input, NULL) == D_BOOLEAN)
    {
        // Copia la struttura di input in output
        d_table_clone_struct(output, input);
        return output;
    }
    else
    {
        fprintf(stderr, "Semantic error on line %d\n", current->line);
        fprintf(stderr, "The expression is not valid (it should return a boolean value)\n");
        exit(EXIT_FAILURE);
    }
}

d_table * semantic_join(PNode join_expr)
{
    int i, j;
    PNode current;
    PNode next_one, next_two;
    
    d_table * output;
    d_table * input_one;
    d_table * input_two;
    
    current = join_expr;
    next_one = next_rel_expr(current);
    next_two = next_rel_expr(next_one->brother);
    
    output = d_table_new(NULL);
    input_one = semantic_rel_expr(next_one->child);
    input_two = semantic_rel_expr(next_two->child);
    d_table_clone_struct(output, input_one);
    
    if(semantic_expr(current, input_one, input_two) != D_BOOLEAN)
    {
        fprintf(stderr, "Semantic error on line %d\n", current->line);
        fprintf(stderr, "[EXPR-JOIN] The expression is not valid (it should return a boolean value)\n\n");
        exit(EXIT_FAILURE);
    }
    
    for(i = 0; i < input_two->columns->length; i++)
    {
        d_cell * cell = d_array_get(input_two->columns, i);
        
        if(d_table_get_index_column(input_one, cell->value.sval) == 0)
        {
            fprintf(stderr, "Semantic error on line %d\n", current->line);
            fprintf(stderr, "[EXPR-JOIN] [Attribute: %s] The merged table cannot contain duplicate columns\n", cell->value.sval);
            exit(EXIT_FAILURE);
        }
        else
        {
            // Add column
            d_table_alter(output, cell);
        }
    }

    return output;
}

d_table * semantic_update(PNode update_expr)
{
    int c;
    PNode current;
    PNode next;
    
    d_table * input;
    d_table * output;
    d_cell * cell;
    
    current = update_expr;
    next = next_rel_expr(current->brother);
    
    output = d_table_new(NULL);
    input = semantic_rel_expr(next->child);
    
    if((c = d_table_get_index_column(input, current->value.sval)) == -1)
    {
        fprintf(stderr, "Semantic error on line %d\n", current->line);
        fprintf(stderr, "[UDPATE][Attibute %s] The attribute to update doens't exist\n", current->value.sval);
        exit(EXIT_FAILURE);
    }
    
    cell = d_array_get(input->columns, c);
    
     if(semantic_expr(current->brother, input, NULL) != cell->type)
    {
        fprintf(stderr, "Semantic error on line %d\n", current->line);
        fprintf(stderr, "[EXPR-JOIN] The expression is not valid (it should return a boolean value)\n\n");
        exit(EXIT_FAILURE);
    }
    
    d_table_clone_struct(output, input);
    return output;
}

d_table * semantic_extend(PNode extend_expr)
{
    PNode current;
    PNode next;
    
    d_table * input;
    d_table * output;
    
    current = extend_expr;
    next = next_rel_expr(current->brother);
    
    output = d_table_new(NULL);
    input = semantic_rel_expr(next->child);
    
    if(d_table_get_index_column(input, current->value.sval) != -1)
    {
        fprintf(stderr, "Semantic error on line %d\n", current->line);
        fprintf(stderr, "[EXTEND][Attibute %s] The attribute to extend already exists\n", current->value.sval);
        exit(EXIT_FAILURE);
    }
    
    if(semantic_expr(current->brother->brother, input, NULL) != current->brother->type)
    {
        fprintf(stderr, "Semantic error on line %d\n", current->line);
        fprintf(stderr, "[EXTEND][Attibute %s] Cannot assign at extended attribute a value that doesn't match with it\n", current->value.sval);
        exit(EXIT_FAILURE);
    }
    
    d_cell cell = {.value.sval = current->value.sval, .type = current->brother->type, .is_empty = false};
    
    d_table_clone_struct(output, input);
    d_table_alter(output, &cell);
    
    return output;
}

d_table * semantic_rename(PNode rename_expr)
{
    int i, j;
    
    PNode current;
    PNode next;
    
    d_table * input;
    d_table * output;
    
    d_array * rename_attributes;
    
    current = rename_expr;
    next = next_rel_expr(current);
    
    output = d_table_new(NULL);
    input = semantic_rel_expr(next->child);
    
    rename_attributes = d_array_new_sized(sizeof(char *), input->columns->capacity);
    
    while(current != next)
    {
        /**
         * This fragment of code verifies that in the expression of the rename
         * there aren't duplicate attribute.
         */
        for(i = 0; i < rename_attributes->length; i++)
        {
            char * attribute = d_array_get(rename_attributes, i);
            
            if(strcmp(current->value.sval, attribute) == 0)
            {
                fprintf(stderr, "Semantic error on line %d\n", current->line);
                fprintf(stderr, "[Attibute %s] In the rename expr cannot define duplicate attributes\n", attribute);
                exit(EXIT_FAILURE);
            }
        }
        
        // Add the name of the attribute in the list
        d_array_push(rename_attributes, current->value.sval);
        
        current = current->brother;
    }
    
    if(rename_attributes->length > input->columns->length)
    {
        fprintf(stderr, "Semantic error on line %d\n", current->line);
        fprintf(stderr, "[Found: %d > %d] In the rename expr cannot ridefine more attribute that existent ones\n", rename_attributes->length, input->columns->length);
        exit(EXIT_FAILURE);
    }
    
    for(i = 0; i < input->columns->length; i++)
    {
        // Get the old cell
        d_cell * old_cell = d_array_get(input->columns, i);
        
        if(i < rename_attributes->length)
        {
            // Change the cell name with the new one
            old_cell->value.sval = d_array_get(rename_attributes, i);           
        }
        else
        {
            for(j = output->columns->length - 1; j >= 0; j--)
            {
                // Get the old cell
                d_cell * new_cell = d_array_get(output->columns, j);
                
                if(strcmp(new_cell->value.sval, old_cell->value.sval) == 0)
                {
                    fprintf(stderr, "Semantic error on line %d\n", current->line);
                    fprintf(stderr, "[Attribute: %s] This attribute already exist on table and cannot be renamed\n", new_cell->value.sval);
                    exit(EXIT_FAILURE);
                }
            }
        }
        
        // Store the new cell in the output table
        d_table_alter(output, old_cell);
    }

    return output;
}

PNode next_rel_expr(PNode rel_expr)
{
    PNode current;
    
    current = rel_expr;
    while (current->value.ival != NT_REL_EXPR) current = current->brother;
    
    return current;
}

d_type semantic_expr(PNode expr, d_table * table_one, d_table * table_two)
{
    PNode current;
    
    current = expr;
    
    // Check if the expression is a boolean constant
    if(current->type == TP_ID)
    {
        if(table_two == NULL)
        {
            d_cell * cell;
            int id;
            
            // Check if the ID of the attribute exists
            if((id = d_table_get_index_column(table_one, current->value.sval)) == -1)
            {
                 fprintf(stderr, "Semantic error on line %d\n", current->line);
                 fprintf(stderr, "[TP-ID][Attribute %s] This attribute doesn't exist", current->value.sval);
                 exit(EXIT_FAILURE);
            }
            
            cell = d_array_get(table_one->columns, id);
            
            return cell->type;
        }
        else
        {
            d_cell * cell;
            int id1, id2;
            
            // Check if the ID of the attribute exist in only and only one table
            if(((id1 = d_table_get_index_column(table_one, current->value.sval)) == -1) == ((id2 = d_table_get_index_column(table_two, current->value.sval)) == -1))
            {
                fprintf(stderr, "Semantic error on line %d\n", current->line);
                fprintf(stderr, "[JOIN-EXPR][Attribute %s] This attribute belongs at both tables", current->value.sval);
                exit(EXIT_FAILURE);
            }
            
            if(id1 != -1)
            {
                cell = d_array_get(table_one->columns, id1);
                return cell->type;
            }
            else
            {
                cell = d_array_get(table_two->columns, id2);
                return cell->type;
            }
            
        }
    }
    else if(current->type == TP_OPERATION)
    {
        d_type lhs, rhs;
        
        // Semantic expr on the lhs
        lhs = semantic_expr(current->child, table_one, table_two);
        
        if(current->value.ival != NEG && current->value.ival != NOT)
        {
            rhs = semantic_expr(current->child->brother, table_one, table_two);
        }
        
        switch(current->value.ival)
        {
            case AND:
            case OR:
                if(lhs != D_BOOLEAN || rhs != D_BOOLEAN)
                {
                    fprintf(stderr, "Semantic Error on Expr on line %d\n", current->line);
                    fprintf(stderr, "[BOOL-OP] Cannot perform boolean operation on not boolean values\n");
                    exit(EXIT_FAILURE);
                    
                }
                return D_BOOLEAN;
                
            case NE:
            case EQ:
                if(lhs != rhs)
                {
                    fprintf(stderr, "Semantic Error on Expr on line %d\n", current->line);
                    fprintf(stderr, "[COMP-OP] Cannot perform equality operation on values those haven't got the same type\n");
                    exit(EXIT_FAILURE);
                }
                
                return D_BOOLEAN;
                
            case LE:
            case LT:
            case GE:
            case GT:
                if(!(lhs == D_INTEGER || lhs == D_FLOAT) && !(rhs == D_INTEGER || rhs == D_FLOAT))
                {
                    fprintf(stderr, "Semantic Error on Expr on line %d\n", current->line);
                    fprintf(stderr, "[COMP-OP] Cannot perform comparative operations on not numerical values\n");
                    exit(EXIT_FAILURE);
                }
                
                return D_BOOLEAN;
                
            case PLUS:
            case MINUS:
            case TIMES:
                if(!(lhs == D_INTEGER || lhs == D_FLOAT) && !(rhs == D_INTEGER || rhs == D_FLOAT))
                {
                    fprintf(stderr, "Semantic Error on Expr on line %d\n", current->line);
                    fprintf(stderr, "[MATH-OP] Cannot perform mathematical operations on not numerical values\n");
                    exit(EXIT_FAILURE);
                }
                
                return (lhs == D_INTEGER && rhs == D_INTEGER) ? D_INTEGER : D_FLOAT;
                
            case OBELUS:
                if(!(lhs == D_INTEGER || lhs == D_FLOAT) && !(rhs == D_INTEGER || rhs == D_FLOAT))
                {
                    fprintf(stderr, "Semantic Error on Expr on line %d\n", current->line);
                    fprintf(stderr, "[MATH-OP] Cannot divide not numerical values\n");
                    exit(EXIT_FAILURE);
                }
                
                return D_FLOAT;
                
            case NEG:
                if(!(lhs == D_INTEGER || lhs == D_FLOAT))
                {
                    fprintf(stderr, "Semantic Error on Expr on line %d\n", current->line);
                    fprintf(stderr, "[NEG] Cannot perform unary negative on not numerical values\n");
                    exit(EXIT_FAILURE);
                }
                
                return lhs;
                
            case NOT:
                if(lhs != D_BOOLEAN)
                {
                    fprintf(stderr, "Semantic Error on Expr on line %d\n", current->line);
                    fprintf(stderr, "[NOT] Cannot negate not boolean values\n");
                    exit(EXIT_FAILURE);
                }
            default:
                fprintf(stderr, "Semantic Error on Expr on line %d\n", current->line);
                fprintf(stderr, "[EXPR] Undefined behaviour occurs on the expression\n");
                exit(EXIT_FAILURE);
        }
    }
    else if(current->type == TP_INTCONST)
    {
        return D_INTEGER;
    }
    else if(current->type == TP_REALCONST)
    {
        return D_FLOAT;
    }
    else if(current->type == TP_STRCONST)
    {
        return D_STRING;
    }
    else if(current->type == TP_BOOLCONST)
    {
        return D_BOOLEAN;
    }

    fprintf(stderr, "Semantic Error on Expr on line %d\n", current->line);
    fprintf(stderr, "[EXPR] Undefined behaviour occurs on the expression\n");
    exit(EXIT_FAILURE);
}

void semantic_read_stat(PNode read_stat)
{
    PNode current;
    
    d_table * input;
    
    current = read_stat;
    
    if((input = d_table_exist(symbol_table, current->brother->value.sval)) == NULL)
    {
        fprintf(stderr, "Semantic error on line %d\n", current->line);
        fprintf(stderr, "[Table: %s] Try to read a table that wasn't decleare previously\n", current->value.sval);
        exit(EXIT_FAILURE);
    }
    
    if(current->child != NULL && semantic_expr(current->child, input, NULL) != D_STRING)
    {
        fprintf(stderr, "Semantic error on line %d\n", current->line);
        fprintf(stderr, "[Table: %s] This specifier is not a string\n", current->value.sval);
        exit(EXIT_FAILURE);
    }
}

void semantic_write_stat(PNode write_stat)
{
    PNode current;
    PNode next;
    FILE * file;
    d_table * input;
    
    current = write_stat;
    next = next_rel_expr(current->brother);
    
    if(current->child != NULL && semantic_expr(current->child, input, NULL) != D_STRING)
    {
        fprintf(stderr, "Semantic error on line %d\n", current->line);
        fprintf(stderr, "[Table: %s] This specifier is not a string\n", current->value.sval);
        exit(EXIT_FAILURE);
    }
    
    input = semantic_rel_expr(next->child);
    
    
    
    
    
}
        
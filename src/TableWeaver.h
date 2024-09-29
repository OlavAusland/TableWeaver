#pragma once
#include <stdlib.h>
#include <stdio.h>

typedef struct table_t
{
    int cols;
    int rows;

    char** entries;
} table_t;

table_t* create_table(int cols, char* header, char delimiter);

void insert_row(table_t** table, char* header, char delimiter);

void display(table_t* table);

char* get_entry(table_t* table, int row, int col);

void pretty_print(table_t* table, int cellWidth);

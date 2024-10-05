#pragma once
#include <stdlib.h>
#include <stdio.h>

#define MAX_ENTRY_SIZE 4096

typedef struct table_t
{
    int cols;
    int rows;

    char** entries;
} table_t;

table_t* create_table(int cols, char* header, char delimiter);

void insert_row(table_t** table, char* header, char delimiter);

char* get_entry(table_t* table, int row, int col);

void display(table_t* table, int cellWidth);

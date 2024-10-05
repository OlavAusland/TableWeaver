#include "TableWeaver.h"
#include <stdbool.h>
#include <string.h>

table_t* create_table(int cols, char* header, char delimiter)
{
    table_t* table = malloc(sizeof(table_t));
    
    table->entries = malloc(sizeof(char*) * cols);

    for(int i = 0; i < cols; i++)
    {
        table->entries[i] = calloc(MAX_ENTRY_SIZE, sizeof(char));
    }

    table->rows = 1;
    table->cols = cols;

    int index = 0;
    int start = 0;
    int end   = 0;

    while(header[end] != '\0' && end < MAX_ENTRY_SIZE)
    {
        if(header[end] == delimiter)
        {
            memmove(table->entries[index++], header + start, end - start);
            start = ++end;
            continue;
        }

        end++;
    }

    memmove(table->entries[index], header + start, end - start);
    return table;
}

void insert_row(table_t** table, char* header, char delimiter)
{
    char** matrix = (*table)->entries;

    (*table)->rows++;

    (*table)->entries = malloc(sizeof(char*) * (*table)->rows * (*table)->cols);

    memmove((*table)->entries, matrix, sizeof(char*) * ((*table)->rows - 1)* (*table)->cols);

    for(int col = 0; col < (*table)->cols; col++)
    {
        int entry = (((*table)->rows - 1) * (*table)->cols + col);
        (*table)->entries[entry] = calloc(MAX_ENTRY_SIZE, sizeof(char));
    }

    const int baseIndex = ((*table)->rows - 1)* (*table)->cols;

    int index = baseIndex;
    int start = 0;
    int end   = 0;

    while(header[end] != '\0' && index < baseIndex + (*table)->cols)
    {   
        if(header[end] == delimiter)
        {
            memmove((*table)->entries[index++], header + start, end - start);
            start = ++end;
            continue;
        }

        end++;
    }

    memmove((*table)->entries[index], header + start, end - start);
}

char* get_entry(table_t* table, int row, int col)
{
    return table->entries[(row * table->cols) + col];
}

void display(table_t* table, int cellWidth)
{
    if(cellWidth < 1){cellWidth = 1;}

    char** overflownBuffer = malloc(sizeof(char*) * table->cols);

    for(int j = 0; j < table->cols; j++)
    {
        overflownBuffer[j] = calloc(MAX_ENTRY_SIZE, sizeof(char));
    }

    char divider[MAX_ENTRY_SIZE];
    memset(divider, 0, MAX_ENTRY_SIZE);
    memset(divider, '-', cellWidth * table->cols + (table->cols + 1));


    for(int i = 0; i <= cellWidth * (table->cols) + (table->cols + 1); i += cellWidth + 1)
    {
        divider[i] = '+';
    }

    printf("\n%s\n", divider);


    for(int i = 0; i < table->rows; i++)
    {
        bool overflown = true;

        for(int j = 0; j < table->cols; j++)
        {
            overflownBuffer[j] = get_entry(table, i, j);
        }
        
        while(overflown)
        {
            printf("|");

            overflown = false;
            for(int j = 0; j < table->cols; j++)
            {
                char entry[MAX_ENTRY_SIZE];
                memset(entry, ' ', MAX_ENTRY_SIZE);

                int entryLength = strlen(overflownBuffer[j]);

                memcpy(entry, overflownBuffer[j], entryLength);
                memset(overflownBuffer[j], 0, MAX_ENTRY_SIZE);
                
                entry[MAX_ENTRY_SIZE - 1] = 0;

                if(entryLength > cellWidth)
                {
                    overflown = true;
                    printf("%.*s|", cellWidth, entry);
                    memcpy(overflownBuffer[j], entry + cellWidth, entryLength - cellWidth);
                }else
                {
                    printf("%.*s|", cellWidth, entry);
                }

            }

            if(overflown)
            {
                printf("\n");
            }
        }

        printf("\n%s\n", divider);

        if(i == 0)
        {
            for(int i = 0; i <= cellWidth * (table->cols + 2); i += cellWidth + 1)
            {
                divider[i] = '+';
            }
            divider[0] = '|';
            divider[cellWidth * (table->cols) + table->cols] = '|';
        }else if(i == table->rows - 2)
        {
            for(int i = 0; i <= cellWidth * (table->cols) + (table->cols + 1); i += cellWidth + 1)
            {
                divider[i] = '+';
            }
        }
    }
}


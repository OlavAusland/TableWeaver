#include "TableWeaver.h"
#include <stdbool.h>
#include <string.h>

table_t* create_table(int cols, char* header, char delimiter)
{
    table_t* table = malloc(sizeof(table_t));
    
    table->entries = malloc(sizeof(char*) * cols);

    for(int i = 0; i < cols; i++)
    {
        table->entries[i] = calloc(128, sizeof(char));
    }

    table->rows = 1;
    table->cols = cols;

    int index = 0;
    int start = 0;
    int end   = 0;

    while(header[end] != '\0')
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
        (*table)->entries[entry] = calloc(128, sizeof(char));
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

void display(table_t* table)
{
    for(int i = 0; i < table->rows; i++)
    {
        for(int j = 0; j < table->cols; j++)
        {
            int entry = (i * table->cols) + j;
            printf("%s\t\t", table->entries[entry]);
        }
        printf("\n");
    }
}

void pretty_print(table_t* table, int cellWidth)
{
    char** overflownBuffer = malloc(sizeof(char*) * table->cols);

    for(int j = 0; j < table->cols; j++)
    {
        overflownBuffer[j] = calloc(128, sizeof(char));
    }

    char divider[128];
    memset(divider, 0, 128);
    memset(divider, '-', cellWidth * table->cols + (table->cols + 1));


    for(int i = 0; i <= cellWidth * (table->cols + 1); i += cellWidth + 1)
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
                char entry[128];
                memset(entry, ' ', 128);

                int entryLength = strlen(overflownBuffer[j]);

                memcpy(entry, overflownBuffer[j], entryLength);
                memset(overflownBuffer[j], 0, 128);
                
                entry[127] = 0;

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
            for(int i = 0; i <= cellWidth * (table->cols + 1); i += cellWidth + 1)
            {
                divider[i] = '|';
            }
        }else if(i == table->rows - 2)
        {
            for(int i = 0; i <= cellWidth * (table->cols + 1); i += cellWidth + 1)
            {
                divider[i] = '+';
            }
        }
    }
}


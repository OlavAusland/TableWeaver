#include "parser.h"
#include <string.h>

table_t* table_from_csv(char* filePath)
{
    char delimiter = ',';

    FILE* file = fopen(filePath, "r");

    char ch;
    int cols = 1;

    int headerIndex = 0;
    char header[128];
    memset(header, 0, 128);

    while((ch = fgetc(file)) != '\n')
    {
        if(ch == delimiter){cols++;}
        header[headerIndex++] = ch;
    }

    table_t* table = create_table(cols, header, delimiter);

    
    if(file == NULL)
    {
        printf("Failed to open file!");
        return NULL;
    }

    char buffer[128];
    memset(buffer, 0, 128);

    int index = 0;
    while((ch = fgetc(file)) != EOF)
    {
        if(ch == '\n')
        {
            insert_row(&table, buffer, ',');
            memset(buffer, 0, 128);
            index = 0;
            continue;
        }
        printf("%c", ch);
        buffer[index++] = ch;
    }

    fclose(file);


    return table;
}

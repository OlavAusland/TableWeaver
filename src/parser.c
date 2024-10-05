#include "parser.h"
#include "TableWeaver.h"
#include <string.h>

table_t* table_from_csv(char* filePath)
{

    char delimiter = ',';

    FILE* file = fopen(filePath, "r");

    char ch;
    int cols = 1;

    int headerIndex = 0;
    char header[MAX_ENTRY_SIZE];
    memset(header, 0, MAX_ENTRY_SIZE);

    while((ch = fgetc(file)) != '\n' && headerIndex < MAX_ENTRY_SIZE)
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

    char buffer[MAX_ENTRY_SIZE];
    memset(buffer, 0, MAX_ENTRY_SIZE);

    int index = 0;
    while((ch = fgetc(file)) != EOF && index < MAX_ENTRY_SIZE)
    {
        if(ch == '\n')
        {
            insert_row(&table, buffer, ',');
            memset(buffer, 0, MAX_ENTRY_SIZE);
            index = 0;
            continue;
        }
        buffer[index++] = ch;
    }

    fclose(file);


    return table;
}

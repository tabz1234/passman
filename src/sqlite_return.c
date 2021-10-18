#include "sqlite_return.h"

#include <stdlib.h>
#include <string.h>

// Happy debugging !!!

void
delete_sqlite_return(struct sqlite_return* pobj)
{

    for (int i = 0; i < pobj->rows_count_; i++) {
        free(pobj->ppkeys_[i]);
        free(pobj->ppvalues_[i]);
    }
    free(pobj->ppkeys_);
    free(pobj->ppvalues_);

    free(pobj);
}

int
inclusive_strlen(const char* str)
{
    return strlen(str) + 1;
}

int
sql_callback(void* pvoid_ret, int rows, char** ppvalues, char** ppkeys)
{
    struct sqlite_return* pret = (struct sqlite_return*)pvoid_ret;

    pret->rows_count_ = rows;

    pret->ppkeys_ = (char**)malloc(rows * sizeof(char*));

    for (int i = 0; i < rows; i++) {

        int len = inclusive_strlen(ppkeys[i] == 0 ? "NULL" : ppkeys[i]) * sizeof(char);
        pret->ppkeys_[i] = (char*)malloc(len);

        for (int j = 0; j < len; j++) {
            pret->ppkeys_[i][j] = ppkeys[i][j];
        }
    }

    pret->ppvalues_ = (char**)malloc(rows * sizeof(char*));
    for (int i = 0; i < rows; i++) {

        int len = inclusive_strlen(ppvalues[i] == 0 ? "NULL" : ppvalues[i]) * sizeof(char);
        pret->ppvalues_[i] = (char*)malloc(len);

        if (ppvalues[i] == 0) {
            continue;
        }
        for (int j = 0; j < len; j++) {
            pret->ppvalues_[i][j] = ppvalues[i][j];
        }
    }

    return 0;
}

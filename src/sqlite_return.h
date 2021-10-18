#ifndef SQLITE_RETURN_H
#define SQLITE_RETURN_H

#ifdef __cplusplus
extern "C"
{
#endif
    struct sqlite_return
    {
        int rows_count_;
        char** ppkeys_;
        char** ppvalues_;
    };
    void delete_sqlite_return(struct sqlite_return* pobj);
    int sql_callback(void* pvoid_ret, int rows, char** ppvalues, char** ppkeys);
#ifdef __cplusplus
}
#endif

#endif

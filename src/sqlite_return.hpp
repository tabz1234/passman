#ifndef SQLITERETURN_HPP
#define SQLITERETURN_HPP

struct sqlite_return final
{
    int cols_;
    char** ppkeys_;
    char** ppvalues_;

    sqlite_return(int cols_, char** ppvalues, char** ppkeys);

    sqlite_return(const sqlite_return& lval);
    sqlite_return& operator=(const sqlite_return& lval);

    sqlite_return(sqlite_return&& rval) noexcept;
    sqlite_return& operator=(sqlite_return&& rval) noexcept;

    ~sqlite_return();
};

#endif

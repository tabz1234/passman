#ifndef SQLITERETURN_HPP
#define SQLITERETURN_HPP

struct sqlite_return
{

    int rc_ = 0;
    int rows_count_ = 0;
    char** ppkeys_ = nullptr;
    char** ppvalues_ = nullptr;

    sqlite_return(const int rc) noexcept;

    sqlite_return(int rows_count, char** ppvalues, char** ppkeys) noexcept;

    sqlite_return(const sqlite_return& lval) noexcept;
    sqlite_return& operator=(const sqlite_return& lval) noexcept;

    sqlite_return(sqlite_return&& rval) noexcept;
    sqlite_return& operator=(sqlite_return&& rval) noexcept;

    ~sqlite_return();
};

#endif

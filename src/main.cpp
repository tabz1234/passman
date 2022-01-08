#include <iostream>
#include <ranges>

#include "sqlite/DataBase.hpp"

template <typename T, typename FunctorT>
auto operator>>=(T val, FunctorT func) -> std::optional<decltype(func(*val))> {
    if (val.has_value()) {
        return func(val);
    } else {
        return std::optional<T>{};
    }
}

int main() {
    SQLite::DataBase db{"test.db"};

    const auto v = db.execute("CREATE TABLE CREDENTIALS( "
                              "LOGIN TEXT PRIMARY KEY NOT NULL, "
                              "PASSWORD TEXT NOT NULL, "
                              "CREATED INTEGER NOT NULL, "
                              "LAST_ACCESS INTEGER) STRICT;");

    db.execute("INSERT INTO CREDENTIALS "
               "VALUES ('"
               "BLOB_VAL"
               "',"
               "'NULL ))))))))'"
               ","
               "12343"
               ",NULL"
               ");");
    db.execute(""
               "SELECT * from CREDENTIALS"
               ";");

    auto res_ = db.requestData("SELECT * from CREDENTIALS;");

    for (const auto& data : *res_) {
        std::cout << "=======NODE START=======\n";
        for (const auto& key : data.keys_) {
            std::cout << "Key :" << key << '\n';
        }
        for (const auto& val : data.values_) {
            std::cout << "Value :" << val.value_or("NULL VALUE") << '\n';
        }
    }
    db.requestData("SELECT * FROM CREDENTIALS;") >>= [&](auto res) -> std::optional<decltype(res)> {
        std::cout << "\n========CHANGE======\n" << '\n';

        for (const auto& data : res.value()) {
            std::cout << "=======NODE START=======\n";
            for (const auto& key : data.keys_) {
                std::cout << "Key :" << key << '\n';
            }
            for (const auto& val : data.values_) {
                std::cout << "Value :" << val.value_or("NULL VALUE") << '\n';
            }
        }
    };

    return 0;
}

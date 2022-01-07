#include <iostream>
class X {
  public:
    void g() {
        f();
    }
    X() {
        g();
    }

  private:
    virtual void f() = 0;
};
class Y : private X {
  public:
    void f() {
    }
    Y() {
    }
};
#include "sqlite/DataBase.hpp"

int main() {
    SQLite::DataBase db("test.db");

    const auto v = db.execute("CREATE TABLE PASSWORD( "
                              "ID VARCHAR PRIMARY KEY NOT NULL, "
                              "STR VARCHAR NOT NULL, "
                              "CREATED BIGINT NOT NULL, "
                              "LAST_ACCES BIGINT);");

    db.execute("INSERT INTO PASSWORD "
               "VALUES ('"
               "github_ww3"
               "','"
               "pass"
               "',"
               "12343"
               ",122"
               ");");

    const auto res = db.requestData("SELECT * from PASSWORD;");
    std::cout << res.value().front().keys_[3];
    int i = 1;
    i++ + ++i;
    Y x;
}

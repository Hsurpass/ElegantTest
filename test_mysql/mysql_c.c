#include <stdio.h>
#include <mysql/mysql.h>

int main()
{
    const char* host = "localhost";
    const char* user = "test";
    const char* passwd = "1111";
    const char* db = "mysql";
    unsigned int port = 3306;

    MYSQL* handle = NULL;
    handle = mysql_init(NULL);
    if (!handle) {
        puts("mysql init failed!!!");
        return 0;
    }

    if (mysql_real_connect(handle, host, user, passwd, db, port, NULL, 0)) {
        puts("connect database success");
    }
    else {
        puts("connect database failed!!!");
        return 0;
    }

    const char* sql = "select * from user";
    if (!mysql_query(handle, sql)) {
        puts("query failed!!!");
        return 0;
    }
    else {
        puts("query success");
    }

    MYSQL_RES* res = mysql_use_result(handle);

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res))) {
        // printf("%s\n", *row);
    }

    mysql_free_result(res);
    mysql_close(handle);

    return 0;
}
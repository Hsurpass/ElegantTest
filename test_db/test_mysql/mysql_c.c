// sudo apt-get install libmysqlclient-dev
// gcc mysql_c.c -lmysqlclient
#include <stdio.h>
#include <mysql/mysql.h>

int main()
{
    const char* host = "localhost";
    const char* user = "test";
    const char* passwd = "1111";
    const char* db = "test1";
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

    const char* sql = "select * from test1.test_table2";
    if (!mysql_query(handle, sql)) {
        puts("query success");
    }
    else {
        puts("query failed!!!");
        return 0;
    }

    MYSQL_RES* res = mysql_use_result(handle);
    if (res == NULL) {
        puts("mysql_use_result is NULL");
    }
    else {
        puts("mysql_use_result is not NULL");
    }

    MYSQL_ROW row;
    row = mysql_fetch_row(res);
    if (row == NULL) {
        puts("mysql_fetch_row is NULL");
    }
    else {
        puts("mysql_fetch_row is not NULL");
        while (*row != NULL) {
            printf("%s ", (*row++));
        }
        putchar(10);
    }
    // while (()) {
    //     printf("%s\n", (*row));
    // }

    mysql_free_result(res);
    mysql_close(handle);

    return 0;
}
#include <stdio.h>
#include <sqlite3.h>
#include "database.h"

sqlite3* connect_database() {
    sqlite3 *db;
    int rc = sqlite3_open("sample.db", &db);

    if (rc != SQLITE_OK) {
        printf("Cannot open database: %s\n", sqlite3_errmsg(db));
        return NULL;
    }
    return db;
}

void create_tables(sqlite3 *db) {
    const char *sql =
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "username TEXT NOT NULL);";

    char *err_msg = NULL;
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK) {
        printf("Error creating users table: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("Users table created (or already exists).\n");
    }
}

void create_score_table(sqlite3 *db) {
    const char *sql =
        "CREATE TABLE IF NOT EXISTS score ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "userid INTEGER NOT NULL, "
        "score INTEGER NOT NULL, "
        "level INTEGER NOT NULL, "
        "FOREIGN KEY(userid) REFERENCES users(id));";

    char *err_msg = NULL;
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK) {
        printf("Error creating score table: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("Score table created (or already exists).\n");
    }
}
#include <stdio.h>
#include <sqlite3.h>
#include "users.h"

int add_user(sqlite3 *db, const char *username) {
    char *err_msg = NULL;
    char sql[256];
    sprintf(sql, "INSERT INTO users (username) VALUES ('%s');", username);

    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        printf("Error inserting user: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("User added successfully: %s\n", username);
    }

    int last_id = sqlite3_last_insert_rowid(db);

    return last_id;
}

void list_users(sqlite3 *db) {
    const char *sql = "SELECT * FROM users;";
    sqlite3_stmt *stmt;

    printf("Users Table:\n");
    printf("ID\tUsername\n");

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        printf("Failed to fetch data: %s\n", sqlite3_errmsg(db));
        return;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char *username = sqlite3_column_text(stmt, 1);

        printf("%d\t%s\n", id, username);
    }

    sqlite3_finalize(stmt);
}

void find_user_by_id(sqlite3 *db, int id) {
    const char *sql = "SELECT * FROM users WHERE id = ?;";
    sqlite3_stmt *stmt;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        printf("Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }

    sqlite3_bind_int(stmt, 1, id);

    printf("User with ID %d:\n", id);
    printf("ID\tUsername\n");

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char *username = sqlite3_column_text(stmt, 1);

        printf("%d\t%s\n", id, username);
    }

    sqlite3_finalize(stmt);
}

void find_user_by_username(sqlite3 *db, const char *username) {
    const char *sql = "SELECT * FROM users WHERE username = ?;";
    sqlite3_stmt *stmt;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        printf("Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);

    printf("User with Username '%s':\n", username);
    printf("ID\tUsername\n");

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char *username = sqlite3_column_text(stmt, 1);

        printf("%d\t%s\n", id, username);
    }

    sqlite3_finalize(stmt);
}

void update_user(sqlite3 *db, int id, const char *new_username) {
    char *err_msg = NULL;
    char sql[256];
    sprintf(sql, "UPDATE users SET username = '%s' WHERE id = %d;", new_username, id);

    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        printf("Error updating user: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("User with ID %d updated successfully.\n", id);
    }
}

void delete_user(sqlite3 *db, int id) {
    char *err_msg = NULL;
    char sql[256];
    sprintf(sql, "DELETE FROM users WHERE id = %d;", id);

    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        printf("Error deleting user: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("User with ID %d deleted successfully.\n", id);
    }
}
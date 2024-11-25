#include <stdio.h>
#include <sqlite3.h>
#include "scores.h"

void add_score(sqlite3 *db, int userid, int score, int level) {
    char *err_msg = NULL;
    char sql[256];
    sprintf(sql, "INSERT INTO score (userid, score, level) VALUES (%d, %d, %d);", userid, score, level);

    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        printf("Error inserting score: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("Score added successfully for User ID %d.\n", userid);
    }
}

void list_scores(sqlite3 *db) {
    const char *sql = "SELECT * FROM score;";
    sqlite3_stmt *stmt;

    printf("Scores Table:\n");
    printf("ID\tUserID\tScore\tLevel\n");

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        printf("Failed to fetch data from score table: %s\n", sqlite3_errmsg(db));
        return;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        int userid = sqlite3_column_int(stmt, 1);
        int score = sqlite3_column_int(stmt, 2);
        int level = sqlite3_column_int(stmt, 3);

        printf("%d\t%d\t%d\t%d\n", id, userid, score, level);
    }

    sqlite3_finalize(stmt);
}

void find_scores_by_user_id(sqlite3 *db, int userid) {
    const char *sql = "SELECT * FROM score WHERE userid = ?;";
    sqlite3_stmt *stmt;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        printf("Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }

    sqlite3_bind_int(stmt, 1, userid);

    printf("Scores for User ID %d:\n", userid);
    printf("ID\tUserID\tScore\tLevel\n");

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        int userid = sqlite3_column_int(stmt, 1);
        int score = sqlite3_column_int(stmt, 2);
        int level = sqlite3_column_int(stmt, 3);

        printf("%d\t%d\t%d\t%d\n", id, userid, score, level);
    }

    sqlite3_finalize(stmt);
}

void update_score(sqlite3 *db, int id, int new_score, int new_level) {
    char *err_msg = NULL;
    char sql[256];
    sprintf(sql, "UPDATE score SET score = %d, level = %d WHERE id = %d;", new_score, new_level, id);

    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        printf("Error updating score: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("Score with ID %d updated successfully.\n", id);
    }
}

void delete_score(sqlite3 *db, int id) {
    char *err_msg = NULL;
    char sql[256];
    sprintf(sql, "DELETE FROM score WHERE id = %d;", id);

    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        printf("Error deleting score: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("Score with ID %d deleted successfully.\n", id);
    }
}
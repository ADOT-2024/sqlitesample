#ifndef USERS_H
#define USERS_H

#include <sqlite3.h>

int add_user(sqlite3 *db, const char *username);
void list_users(sqlite3 *db);
void find_user_by_id(sqlite3 *db, int id);
void find_user_by_username(sqlite3 *db, const char *username);
void update_user(sqlite3 *db, int id, const char *new_username);
void delete_user(sqlite3 *db, int id);

#endif
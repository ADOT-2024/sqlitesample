#ifndef SCORES_H
#define SCORES_H

#include <sqlite3.h>

void add_score(sqlite3 *db, int userid, int score, int level);
void list_scores(sqlite3 *db);
void find_scores_by_user_id(sqlite3 *db, int userid);
void update_score(sqlite3 *db, int id, int new_score, int new_level);
void delete_score(sqlite3 *db, int id);

#endif
#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>

sqlite3* connect_database();
void create_tables(sqlite3 *db);
void create_score_table(sqlite3 *db);

#endif
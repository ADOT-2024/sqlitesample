#include <stdio.h>
#include <sqlite3.h>
#include "database.h"
#include "users.h"
#include "scores.h"

int main2() {
    sqlite3 *db = connect_database();
    if (!db) return 1;

    // Tabloları oluştur
    create_tables(db);
    create_score_table(db);

    // Kullanıcı ekleme
    add_user(db, "Alice");
    add_user(db, "Bob");

    // Skor ekleme
    add_score(db, 1, 100, 1);
    add_score(db, 2, 200, 2);

    // Kullanıcı ve skorları listeleme
    printf("\nListing all users:\n");
    list_users(db);

    printf("\nListing all scores:\n");
    list_scores(db);

    // Belirli bir kullanıcıyı ID'ye göre bulma
    printf("\nFinding user with ID 1:\n");
    find_user_by_id(db, 1);

    // Kullanıcıyı kullanıcı adına göre bulma
    printf("\nFinding user with Username 'Bob':\n");
    find_user_by_username(db, "Bob");

    // Belirli bir kullanıcıya ait skorları listeleme
    printf("\nFinding scores for User ID 2:\n");
    find_scores_by_user_id(db, 2);

    // Skor güncelleme
    printf("\nUpdating score with ID 1:\n");
    update_score(db, 1, 150, 2);

    // Güncellenmiş skorları listeleme
    printf("\nListing all scores after update:\n");
    list_scores(db);

    // Skor silme
    printf("\nDeleting score with ID 2:\n");
    delete_score(db, 2);

    // Silinmiş skorları listeleme
    printf("\nListing all scores after delete:\n");
    list_scores(db);

    sqlite3_close(db);
    return 0;
}
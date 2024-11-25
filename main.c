#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <sqlite3.h>
#include "database.h"
#include "users.h"
#include "scores.h"

int main() {
    sqlite3 *db = connect_database();
    if (!db) return 1;

    // Tabloları oluştur
    create_tables(db);
    create_score_table(db);

    int dogrusayi = 0;
    int tahminedilensayi = 0;
    int puan = 1;
    int userid;

    char ad[20]="sdfadsfasfadfasdfa";


    printf("\nAdınız: ");
    fgets(ad, sizeof(ad), stdin);

    // Kullanıcı ekleme
    userid = add_user(db, ad);



    for (int j = 1; j < 4;j++){

        srand(time(NULL)); 
        dogrusayi=rand()%100; 
        printf("\n\nRastgele sayi= %d",dogrusayi); 

        printf("\n1-100 arası sayı tahmin edin: ");

        for (int i = 1; i < 6;i++){

            
            scanf("%d", &tahminedilensayi);

            if(tahminedilensayi<dogrusayi){
                printf("\nDaha büyük sayı tahmin edin: ");
            }else if(tahminedilensayi>dogrusayi){
                printf("\nDaha küçük sayı tahmin edin: ");
            }else if(tahminedilensayi==dogrusayi){
                printf("\nDoğru bildiniz. Tebrikler.");

                switch (i)
                {
                    case 1:
                        printf("\n1. Adımda Doğru Bildiniz.");
                        puan = 100;
                        printf("\nAldığınız Puan: %d", puan);
                        break;
                    case 2:
                        printf("\n2. Adımda Doğru Bildiniz.");
                        puan = 80;
                        printf("\nAldığınız Puan: %d", puan);
                        break;
                    case 3:
                        printf("\n3. Adımda Doğru Bildiniz.");
                        puan = 60;
                        printf("\nAldığınız Puan: %d", puan);
                        break;
                    case 4:
                        printf("\n4. Adımda Doğru Bildiniz.");
                        puan = 40;
                        printf("\nAldığınız Puan: %d", puan);
                        break;
                    case 5:
                        printf("\n4. Adımda Doğru Bildiniz.");
                        puan = 20;
                        printf("\nAldığınız Puan: %d", puan);
                        break;
                }

                break;

            }

        }


        add_score(db, userid, puan, j);


    }

    // Kullanıcı ve skorları listeleme
    printf("\nListing all users:\n");
    list_users(db);

    printf("\nListing all scores:\n");
    list_scores(db);


    return 0;

}
/*
@file proje1.c
@description Fonksiyonların definiton işlemleri bu dosyada. Öğrenci ekleme, bilgileri dosyaya kaydetme, dosyadaki verileri okuma, derslerin aritmetik ortalama hesabı gibi fonksiyonlar bu dosyada.
@assignment Proje 1
@date 26/11/2023 - 10/12/2023
@author İclal Horuz iclal.horuz@stu.fsm.edu.tr
*/

#include "proje1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_STRING_BOYUTU 256
#define MAX_BOYUT 10
#define SATIR_BOYUT 5000 

void ogrEkle(){
    unsigned int ogrSayi;

    while(1){
        printf("\nEkleyeceğiniz öğrenci sayısı:\t");

        if(scanf("%u", &ogrSayi) == 1)
            break;

        else{
            printf("Geçersiz karakter!\n");
            while(getchar() != '\n');
        }
    }

    printf("\n-----ÖĞRENCİ EKLE-----\n");
    
    Ogrenci *yeniOgrenci = ogrOlustur(ogrSayi); // öğrenci oluşturma adımı başladı.

	clearScreen();

	for(int i = 0; i < ogrSayi; i++)
		ogrYazdir(yeniOgrenci[i]);

    FILE *ogrenci_dosya = fopen("Öğrenci Bilgileri.txt", "a");

    if (ogrenci_dosya == NULL){
        printf("Dosya oluşturulamadı!");
        return;
    }

    dosyaYazdir(yeniOgrenci, ogrSayi, ogrenci_dosya);

	//Bellekten ayrılma
	
	freeBellek(ogrSayi, yeniOgrenci);

	fclose(ogrenci_dosya); //dosya kapatıldı
}

Ogrenci *ogrOlustur(unsigned int ogrSayi){
    Ogrenci *ogrArray = (Ogrenci *) malloc(sizeof(Ogrenci) * ogrSayi);

    for(int i = 0; i < ogrSayi; i++){
        
        printf("\n~Öğrenci %d\n", i+1);

        ogrArray[i].ogrAdi = (char *) malloc(sizeof(char) * MAX_STRING_BOYUTU);
        printf("\nAdı:\t");
		scanf("%s", ogrArray[i].ogrAdi);
		buyukKucukHarf(ogrArray[i].ogrAdi);

        ogrArray[i].ogrSoyAdi = (char *) malloc(sizeof(char) * MAX_STRING_BOYUTU);
        printf("\nSoyadı:\t");
		scanf("%s", ogrArray[i].ogrSoyAdi);
		buyukKucukHarf(ogrArray[i].ogrSoyAdi);

        ogrArray[i].bolumu = (char *) malloc(sizeof(char) * MAX_STRING_BOYUTU);
        printf("\nBölümü:\t");
		scanf("%s", ogrArray[i].bolumu);
        
        printf("\n*Alınabilecek en fazla ders sayısı 10'dur.\n");

        //alınan ders sayısının doğru girildiğini kontrol eder.
		while(1){
            printf("\nÖğrencinin aldığı ders sayısı:\t");
        
            if (scanf("%u", &ogrArray[i].aldigiDersSayisi) == 1){
            //girilen değer int ise koşul sağlanır.
                
                if(ogrArray[i].aldigiDersSayisi > 10){
                    printf("\n*Alınabilecek en fazla ders sayısı 10'dur.\n");
                    while(getchar() != '\n');
                    continue;
                }

                break;
            }

            else{ //sayı dışı karakter girilirse
                printf("Geçersiz karakter!\n");
                while(getchar() != '\n');
            }
        }
        
        ogrArray[i].aldigiDersler = (Ders *) malloc(sizeof(Ders) * ogrArray[i].aldigiDersSayisi);
        dersEkle(&ogrArray[i]);

		//girilen ders bilgilerindeki puanlara göre ortalama hesaplanacak.
		ogrArray[i].ortalama = ogrOrtalamaHesap(&ogrArray[i]); 
    }

    return ogrArray;
}

void dersEkle(Ogrenci *ogr){
	
	printf("\n-----DERS EKLE-----\n");

	ogr->aldigiDersler  = dersOlustur(ogr->aldigiDersSayisi); //ders oluşturma adımı başladı.
	
}

Ders *dersOlustur(unsigned int dersSayi){
	Ders *dersArray = (Ders *) malloc(sizeof(Ders) * dersSayi);

	for(int i = 0; i < dersSayi; i++){
		
		printf("\n~DERS %d\n", i+1);

		dersArray[i].dersAdi = (char *) malloc(sizeof(char) * MAX_STRING_BOYUTU);

		printf("\nDers Adı:\t");
		scanf("%s", dersArray[i].dersAdi);
		buyukKucukHarf(dersArray[i].dersAdi);

		//kredi ve puan değerlerinin doğru girildiğini kontrol et
		while(1){
			printf("\nKredi:\t");

			if (scanf("%hu", &dersArray[i].kredi) == 1)
				break;

			else{
				printf("Geçersiz karakter!\n");
				while(getchar() != '\n');
			}
		}

		while(1){
			printf("\nÖğrencinin puanı:\t");

			if (scanf("%hu", &dersArray[i].puan) == 1)
				break;

			else{
				printf("Geçersiz karakter!\n");
				while(getchar() != '\n');
			}
		}
	}

	return dersArray;
}

void dosyaYazdir(Ogrenci *yeniOgr, unsigned int ogrSayi, FILE *ogr_dosya){
	for(int i = 0; i < ogrSayi; i++){
		fprintf(ogr_dosya, "%s, ", yeniOgr[i].ogrAdi);
		fprintf(ogr_dosya, "%s, ", yeniOgr[i].ogrSoyAdi);
		fprintf(ogr_dosya, "%s, ", yeniOgr[i].bolumu);
		fprintf(ogr_dosya, "%.2f, ", yeniOgr[i].ortalama);
		fprintf(ogr_dosya, "%d", yeniOgr[i].aldigiDersSayisi);

		for(int j = 0; j < yeniOgr[i].aldigiDersSayisi; j++){
			fprintf(ogr_dosya, ", %s, ", yeniOgr[i].aldigiDersler[j].dersAdi); 
			fprintf(ogr_dosya, "%hu, ", yeniOgr[i].aldigiDersler[j].kredi);
			fprintf(ogr_dosya, "%hu", yeniOgr[i].aldigiDersler[j].puan);
		}
		fprintf(ogr_dosya, "\n");
	}
}

void ogrYazdir(Ogrenci ogrenci){
	printf("\n-----ÖĞRENCİ BİLGİLERİ-----\n");
	printf("Adı: %s\n", ogrenci.ogrAdi);
	printf("Soyadı: %s\n", ogrenci.ogrSoyAdi);
	printf("Bölümü: %s\n", ogrenci.bolumu);
	printf("Ortalama: %.2f\n", ogrenci.ortalama);

	printf("\n~Alınan Dersler~\n");
	
	for (int i = 0; i < ogrenci.aldigiDersSayisi; i++){
		
		printf("\n\t%d.Ders\n", i+1);
		printf("\tAdı: %s", ogrenci.aldigiDersler[i].dersAdi);
		printf("\n\tKredi: %hu\n", ogrenci.aldigiDersler[i].kredi);
		printf("\tPuan: %hu\n", ogrenci.aldigiDersler[i].puan);
	}
}

float ogrOrtalamaHesap(Ogrenci *ogr){
	float katsayi;
	float puanSum = 0;
	float krediSum = 0;

	for(int i = 0; i < ogr->aldigiDersSayisi; i++){
		if(ogr->aldigiDersler[i].puan <= 100 && ogr->aldigiDersler[i].puan >= 90)
			katsayi = 4.00;
		else if(ogr->aldigiDersler[i].puan >= 85)
			katsayi = 3.50;
		else if(ogr->aldigiDersler[i].puan >= 75)
			katsayi = 3.00;
		else if(ogr->aldigiDersler[i].puan >= 65)
			katsayi = 2.50;
		else if(ogr->aldigiDersler[i].puan >= 60)
			katsayi = 2.00;
		else if(ogr->aldigiDersler[i].puan >= 50)
			katsayi = 1.50;
		else if(ogr->aldigiDersler[i].puan >= 45)
			katsayi = 1.00;
		else if(ogr->aldigiDersler[i].puan >= 40)
			katsayi = 0.50;
		else
			katsayi = 0.00;

		puanSum += (katsayi * ogr->aldigiDersler[i].kredi);
		krediSum += ogr->aldigiDersler[i].kredi;
	}
	
	ogr->ortalama = puanSum / krediSum;

	return ogr->ortalama;
}

void dosyaOku(const char *dosyaAdi, Ogrenci **ogrenci, int *ogrSayisi){
	
	FILE *dosya = fopen(dosyaAdi, "r");
	if(dosya == NULL){
		fprintf(stderr, "Dosya açma hatası!");
		return;
	}

	int i = 0;
	char satir[SATIR_BOYUT];
	char *token;

	while(fgets(satir, sizeof(satir), dosya) != NULL){
		if(satir[0] != '\n')
			(*ogrSayisi)++;
	}

	rewind(dosya);

	*ogrenci = (Ogrenci *) malloc(sizeof(Ogrenci) * (*ogrSayisi));

	while(!feof(dosya)){
		fgets(satir, sizeof(satir), dosya); 
		token = strtok(satir, ", ");

		if(i < *ogrSayisi){
			(*ogrenci)[i].ogrAdi = strdup(token);

			token = strtok(NULL, ", ");
			(*ogrenci)[i].ogrSoyAdi = strdup(token);	

			token = strtok(NULL, ", ");
			(*ogrenci)[i].bolumu = strdup(token);
			
			token = strtok(NULL, ", ");
			(*ogrenci)[i].ortalama = atof(token);

			token = strtok(NULL, ", ");
			(*ogrenci)[i].aldigiDersSayisi = atoi(token);

			(*ogrenci)[i].aldigiDersler = (Ders *)malloc(sizeof(Ders) * (*ogrenci)[i].aldigiDersSayisi);
			
			for(int j = 0; j < (*ogrenci)[i].aldigiDersSayisi; j++){

				token = strtok(NULL, ", ");
				(*ogrenci)[i].aldigiDersler[j].dersAdi = strdup(token);

				token = strtok(NULL, ", ");
				(*ogrenci)[i].aldigiDersler[j].kredi = (unsigned short int) strtoul(token, NULL, 10);

				token = strtok(NULL, ", ");
				(*ogrenci)[i].aldigiDersler[j].puan = (unsigned short int) strtoul(token, NULL, 10);
			
			}	

		}

		i++;
	}
	
	fclose(dosya);
}

float dersAritmetikOrt(char *ders, Ogrenci *ogrenciler, int ogrSayi){
	int puanSum = 0;
	int dersiAlanOgr = 0;

	for(int i = 0; i < ogrSayi; i++){
		for(int j = 0; j < ogrenciler[i].aldigiDersSayisi; j++){
			if(strcmp(ders, ogrenciler[i].aldigiDersler[j].dersAdi) == 0){
				puanSum += ogrenciler[i].aldigiDersler[j].puan;
				dersiAlanOgr++;
			}
		}
	}
	
	if(dersiAlanOgr > 0){
		float aritmetikOrt = (float)puanSum / dersiAlanOgr;
		return aritmetikOrt;
	}
	else{
		fprintf(stderr, "Dersi alan öğrenci bulunamadı.\n");
		return 1;
	}
}

float dersStandartSapma(char *ders, Ogrenci *ogrenci, int ogrSayi){
	float dersOrt = dersAritmetikOrt(ders, ogrenci, ogrSayi);

	if(dersOrt < 0){ 
		fprintf(stderr, "Standart sapma için ders aritmetik ortalaması hesaplanamadı.\n");
		return 1;
	}

	int dersiAlanOgr = 0;
	float sapmaSum = 0;

	for(int i = 0; i < ogrSayi; i++){
		for(int j = 0; j < ogrenci[i].aldigiDersSayisi; j++){
			if(strcmp(ders, ogrenci[i].aldigiDersler[j].dersAdi) == 0){
				float sapma = ogrenci[i].aldigiDersler[j].puan - dersOrt;
				sapmaSum += pow(sapma, 2);
				dersiAlanOgr++;
			}

		}
	}

	if (dersiAlanOgr > 0) {
        float standartSapma = sqrt(sapmaSum / dersiAlanOgr);
		printf("\n%s standart sapma: %.2f\n", ders, standartSapma);
        return standartSapma;
    } 
	else {
        fprintf(stderr, "Dersi alan öğrenci bulunamadı.\n");
        return 1; 
	}

}

float dersKovaryans(char *ders1, char *ders2, Ogrenci *ogrenci, int ogrSayi){

	float dersOrt1 = dersAritmetikOrt(ders1, ogrenci, ogrSayi);
    float dersOrt2 = dersAritmetikOrt(ders2, ogrenci, ogrSayi);
    
    if (dersOrt1 < 0 || dersOrt2 < 0) {
        fprintf(stderr, "Kovaryans için ders aritmetik ortalaması hesaplanamadı.\n");
        return 1;
    }

    int dersiAlanOgr = 0;
    float kovaryansSum = 0;

    for (int i = 0; i < ogrSayi; i++) {
        int j1 = -1, j2 = -1; //öğrencinin istenen ders puanlarını bulmak için
        
		for (int j = 0; j < ogrenci[i].aldigiDersSayisi; j++) {
        
			if (strcmp(ders1, ogrenci[i].aldigiDersler[j].dersAdi) == 0) {
                j1 = j;
            }
			else if (strcmp(ders2, ogrenci[i].aldigiDersler[j].dersAdi) == 0) {
                j2 = j;
            }
        }

        // öğrencinin iki dersi aldığı durumda kovaryans hesabı
		if (j1 != -1 && j2 != -1) {
            float sapma1 = ogrenci[i].aldigiDersler[j1].puan - dersOrt1;
            float sapma2 = ogrenci[i].aldigiDersler[j2].puan - dersOrt2;
            kovaryansSum += sapma1 * sapma2;
            dersiAlanOgr++;
        }
    }

    if (dersiAlanOgr > 0) {
        float kovaryans = kovaryansSum / dersiAlanOgr;
		printf("\n%s - %s kovaryans: %.2f\n", ders1, ders2, kovaryans);
        return kovaryans;
    } 
	else {
        fprintf(stderr, "Ders bulunamadı.\n");
        return 1;
	}

}

void ortUstuOgr(char *ders, Ogrenci *ogrenci, int ogrSayi){
	
	float dersOrt = dersAritmetikOrt(ders, ogrenci, ogrSayi);

    if (dersOrt < 0) {
        printf("Ders ortalamasi hesaplanamadi.\n");
        return;
    }

    printf("\n%s ortalama üstü öğrenciler:\n", ders);

    for (int i = 0; i < ogrSayi; i++) {

        for (int j = 0; j < ogrenci[i].aldigiDersSayisi; j++) {

            if (strcmp(ders, ogrenci[i].aldigiDersler[j].dersAdi) == 0) {
                float ogrPuan = ogrenci[i].aldigiDersler[j].puan;
                if (ogrPuan > dersOrt) {
                    printf("%s %s: %hu\n", ogrenci[i].ogrAdi, ogrenci[i].ogrSoyAdi ,ogrenci[i].aldigiDersler[j].puan);
                }
            }
        }
    }
}

void buyukKucukHarf(char *kelime){

	kelime[0] = toupper(kelime[0]);

	for(int i = 1; kelime[i] != '\0'; i++){
		kelime[i] = tolower(kelime[i]);
	}
}

void clearScreen(){
	printf("\033[2J\033[H");
}

void freeBellek(int ogrSayi, Ogrenci *ogrenciler){
	
	for (int i = 0; i < ogrSayi; i++) {

        free(ogrenciler[i].ogrAdi);
        free(ogrenciler[i].ogrSoyAdi);
        free(ogrenciler[i].bolumu);
        free(ogrenciler[i].aldigiDersler);
    }

    free(ogrenciler);
}

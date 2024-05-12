/*
@file main.c
@description Bu dosyada oluşturulan ogrEkle(), dosyaOku(), dersAritmetikOrt(), dersStandartSapma(), dersKovaryans(), ortUstuOgr(), freeBellek() fonksiyonları çağırılıyor.
@assignment Proje 1
@date 26/11/2023 - 10/12/2023
@author İclal Horuz iclal.horuz@stu.fsm.edu.tr
*/

#include "proje1.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

	ogrEkle();
 
	//dosya okuma işlemleri
	if (argc != 2){
		fprintf(stderr, "Kullanım: %s <dosya_adı>\n", argv[0]);
		return 1;
	}

	const char *dosyaAdi = argv[1];

	//bellek tahsisi dosya okunurken gerçekleştirilecek.

	Ogrenci *ogrenciler = NULL;
	int ogrSayisi = 0;

	dosyaOku(dosyaAdi, &ogrenciler, &ogrSayisi);

	if(ogrenciler == NULL){
		printf("\nArray boş\n");
		return 0;
	}

	//ortalama, kovaryans, standart sapma hesabı
	char ders1[20];
	char ders2[20];

	printf("\nAritmetik ortalama, standart sapma, kovaryans hesaplamak için 2 ders girin: \n");
	printf("Ders 1: ");
	scanf("%s", ders1);
	buyukKucukHarf(ders1);

	printf("\nDers 2: ");
	scanf("%s", ders2);
	buyukKucukHarf(ders2);

	clearScreen();

	float ort1 = dersAritmetikOrt(ders1, ogrenciler, ogrSayisi);
	float ort2 = dersAritmetikOrt(ders2, ogrenciler, ogrSayisi);

	printf("\n%s aritmetik ortalama: %.2f\n", ders1, ort1);
	printf("\n%s aritmetik ortalama: %.2f\n", ders2, ort2);

	dersStandartSapma(ders1, ogrenciler, ogrSayisi);
	dersStandartSapma(ders2, ogrenciler, ogrSayisi);

	dersKovaryans(ders1, ders2, ogrenciler, ogrSayisi);
	
	//girilen derslerdeki ortalama üstünde puanı olan öğrencileri listeleme
	ortUstuOgr(ders1, ogrenciler, ogrSayisi);
	ortUstuOgr(ders2, ogrenciler, ogrSayisi);

	//belleği serbest bırakma
	freeBellek(ogrSayisi, ogrenciler);
	
	return 0;
}	

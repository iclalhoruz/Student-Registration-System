/*
@file proje1.h
@description Fonksiyonların decleration işlemleri bu dosyada. Her fonksiyonun ne işlemi yapacağı burada açıklandı.
@assignment Proje 1
@date 26/11/2023 - 10/12/2023
@author İclal Horuz iclal.horuz@stu.fsm.edu.tr
*/

#ifndef PROJE1_H
#define PROJE1_H

#include <stdio.h>

typedef struct{
	char *dersAdi;
	unsigned short int kredi;
	unsigned short int puan;
}Ders;

typedef struct{
	char *ogrAdi;
	char *ogrSoyAdi;
	char *bolumu;
	float ortalama;
	unsigned int aldigiDersSayisi;
	Ders *aldigiDersler;
}Ogrenci;


void ogrEkle();
/*
Öğrenci ekleme ekranı açıldı. 
ogrOlustur() fonksiyonu çağırıldı, öğrenci oluşturma adımı başladı.
ogrYazdir() fonksiyonu ile girilen öğrenci bilgileri ekrana yazdırıldı.
"Öğrenci Bilgileri.txt" isimli dosya açıldı, dosyaYazdir() fonksiyonu ile öğrenci bilgileri dosyaya kaydedildi.
freeBellek() fonksiyonu ile tutulan alan serbest bırakıldı.
*/

Ogrenci *ogrOlustur(unsigned int);
/*
bellekten yer ayrıldı, Ogrenci structının bilgileri girildi
öğrenci structı döndürüldü
ders bilgileri için dersEkle() fonksiyonu çağırıldı
öğrencinin ortalamasını hesaplayacak ogrOrtalamaHesap() fonksiyonu çağırıldı
*/

void dersEkle(Ogrenci *); 
/*
dersOlustur() fonksiyonu çağırılarak ders oluşturma adımı başlatıldı
*/

Ders *dersOlustur(unsigned int); 
/*
bellekten yer ayrıldı ders bilgileri girildi
ders structı döndürüldü
*/

void dosyaYazdir(Ogrenci *, unsigned int, FILE *);
//bilgiler dosyaya yazdırıldı

void ogrYazdir(Ogrenci); 
//Öğrenci bilgilerini ekrana yazdırır

float ogrOrtalamaHesap(Ogrenci *);
//öğrenci ortalama hesap

void dosyaOku(const char *, Ogrenci **, int *); 
//dosyadaki tüm öğrenci bilgilerini okuyup maindeki öğrenciler arryine kopyalıyor

float dersAritmetikOrt(char *, Ogrenci *, int);
//maindeki öğrenciler arrayi

float dersStandartSapma(char *, Ogrenci *, int);
//maindeki öğrenciler arrayi

float dersKovaryans(char *, char *, Ogrenci *, int);
//maindeki öğrenciler arrayi

void ortUstuOgr(char *, Ogrenci *, int);
//kullanıcıdan alınan derslerde ortalamanın üstünde puana sahip öğrencileri listeler

void buyukKucukHarf(char *);
//kelimeleri ilk harfi büyük diğer harfler küçük olacak şekilde yazar

void clearScreen(); 
//ANSI escape kodu ile ekran temizleyen fonksiyon

void freeBellek(int, Ogrenci *);
//tutulan alanları serbest bırakan fonksiyon

#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Sabitler
#define MAX_HESAPLAR 100  // Maksimum hesap sayisi
#define HESAP_NUMARASI_UZUNLUGU 12  // Hesap numarasýnýn uzunluðu

// Hesap yapisinin tanimlanmasi
typedef struct {
    char hesapNumarasi[HESAP_NUMARASI_UZUNLUGU + 1];  // Hesap numarasi (12 haneli, sonuna null karakteri eklenir)
    char ad[50];  // Hesap sahibinin adi
    char soyad[50];  // Hesap sahibinin soyadi
    float bakiye;  // Hesap bakiyesi
} Hesap;

// Hesaplar dizisi ve hesap sayisi
Hesap hesaplar[MAX_HESAPLAR];  // Hesap bilgilerini tutacak dizi
int hesapSayisi = 0;  // Hesap sayisini tutacak degisken

// Fonksiyon prototipleri
void hesapOlustur();
void paraYatir();
void paraCek();
void bakiyeSorgula();
void hesapBilgileriniGoster();
int hesapNumarasiGecerliMi(char *hesapNumarasi);
void hesapVerileriniKaydet();
void hesapVerileriniYukle();
void menuGoster();
void hesapSil();
int hesapNumarasiVarMi(char *hesapNumarasi);

int main() {
    // Baþlangiçta dosyadaki hesaplari yukler
    hesapVerileriniYukle();

    int secim;
    while (1) {
        // Menu gosterilir
        menuGoster();
        printf("Seciminizi yapin: ");
        scanf("%d", &secim);

        // Secime gore islem yapilir
        switch (secim) {
            case 1:
                hesapOlustur();  // Yeni hesap olusturma
                break;
            case 2:
                paraYatir();  // Para yatirma
                break;
            case 3:
                paraCek();  // Para cekme
                break;
            case 4:
                bakiyeSorgula();  // Bakiye sorgulama
                break;
            case 5:
                hesapBilgileriniGoster();  // Hesap bilgilerini gosterme
                break;
            case 6:
                hesapSil();  // Hesap silme
                break;
            case 7:
                hesapVerileriniKaydet();  // Hesap verilerini kaydetme
                printf("Cikis yapiliyor...\n");
                return 0;  // Program sonlandiriliyor
            default:
                printf("Gecersiz secim! Lutfen tekrar deneyin.\n");  // Gecersiz secim
        }
    }

    return 0;
}

// Menu fonksiyonu, kullaniciya secenekleri gosterir
void menuGoster() {
    printf("\nBanka Sistemi\n");
    printf("1. Hesap Ac\n");
    printf("2. Para Yatir\n");
    printf("3. Para Cek\n");
    printf("4. Bakiye Sorgula\n");
    printf("5. Dosyadaki Hesap Bilgilerini Goruntule\n");
    printf("6. Hesap Sil\n");
    printf("7. Cikis\n");
}

// Yeni hesap olusturma fonksiyonu
void hesapOlustur() {
    if (hesapSayisi >= MAX_HESAPLAR) {
        // Hesap sayisi maksimuma ulasmissa yeni hesap olusturulamaz
        printf("Maksimum hesap sayisina ulasildi!\n");
        return;
    }

    Hesap yeniHesap;
    char hesapNumarasi[HESAP_NUMARASI_UZUNLUGU + 1];

    // Hesap numarasinin geçerliligini kontrol etmek için döngü
    while (1) {
        printf("Hesap Numarasi (12 haneli): ");
        scanf("%s", hesapNumarasi);

        if (!hesapNumarasiVarMi(hesapNumarasi)) {  // Hesap numarasi kullanilmiyorsa, yeni hesap numarasi atanir
            strcpy(yeniHesap.hesapNumarasi, hesapNumarasi);
            break;
        } else {
            printf("Bu hesap numarasi zaten kullaniliyor! Lutfen farkli bir hesap numarasi girin.\n");
        }
    }

    // Hesap sahibinin ad ve soyad bilgilerini alir
    printf("Ad: ");
    scanf("%s", yeniHesap.ad);
    printf("Soyad: ");
    scanf("%s", yeniHesap.soyad);
    yeniHesap.bakiye = 0;  // Yeni hesapta baslangic bakiyesi 0 olarak ayarlanir

    hesaplar[hesapSayisi++] = yeniHesap;  // Yeni hesap hesaplar dizisine eklenir
    printf("Hesap Basariyla Olusturuldu.\n");
}

// Para yatirma fonksiyonu
void paraYatir() {
    char hesapNumarasi[HESAP_NUMARASI_UZUNLUGU + 1];
    printf("Para Yatirilacak Hesap Numarasini Girin (12 haneli): ");
    scanf("%s", hesapNumarasi);

    int index = -1;
    for (int i = 0; i < hesapSayisi; i++) {
        // Hesap numarasina gore hesap bulunur
        if (strcmp(hesaplar[i].hesapNumarasi, hesapNumarasi) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Boyle bir hesap bulunamadi.\n");
        return;
    }

    // Yatirilacak tutar alinir
    float tutar;
    printf("Yatirilacak Tutari Giriniz: ");
    scanf("%f", &tutar);

    if (tutar <= 0) {
        printf("Gecersiz tutar! Lutfen pozitif bir deger girin.\n");
        return;
    }

    hesaplar[index].bakiye += tutar;  // Hesap bakiyesi artiriliyor
    printf("Hesaba Basariyla Yatirildi.\n");
}

// Para cekme fonksiyonu
void paraCek() {
    char hesapNumarasi[HESAP_NUMARASI_UZUNLUGU + 1];
    printf("Para Cekilecek Hesap Numarasini Girin (12 haneli): ");
    scanf("%s", hesapNumarasi);

    int index = -1;
    for (int i = 0; i < hesapSayisi; i++) {
        // Hesap numarasina gore hesap bulunur
        if (strcmp(hesaplar[i].hesapNumarasi, hesapNumarasi) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Boyle bir hesap bulunamadi.\n");
        return;
    }

    // Cekilecek tutar alinir
    float tutar;
    printf("Cekilecek Tutari Giriniz: ");
    scanf("%f", &tutar);

    if (tutar <= 0) {
        printf("Gecersiz tutar! Lutfen pozitif bir deger girin.\n");
        return;
    }

    if (hesaplar[index].bakiye < tutar) {
        printf("Yeterli bakiye yok!\n");
        return;
    }

    hesaplar[index].bakiye -= tutar;  // Hesap bakiyesi düsürülür
    printf("Hesaptan Basariyla Para Cekildi.\n");
}

// Bakiye sorgulama fonksiyonu
void bakiyeSorgula() {
    char hesapNumarasi[HESAP_NUMARASI_UZUNLUGU + 1];
    printf("Bakiye sorgulamak icin Hesap Numarasini Girin (12 haneli): ");
    scanf("%s", hesapNumarasi);

    int index = -1;
    for (int i = 0; i < hesapSayisi; i++) {
        // Hesap numarasina göre hesap bulunur
        if (strcmp(hesaplar[i].hesapNumarasi, hesapNumarasi) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Boyle bir hesap bulunamadi.\n");
        return;
    }

    printf("Hesap Bakiyesi: %.2f\n", hesaplar[index].bakiye);  // Hesap bakiyesi ekrana yazdiriliyor
}

// Hesap bilgilerini gosterme fonksiyonu
void hesapBilgileriniGoster() {
    if (hesapSayisi == 0) {
        printf("Hesap bulunmuyor.\n");
        return;
    }

    printf("\nHesap Bilgileri:\n");
    // Tum hesaplar ekrana yazdiriliyor
    for (int i = 0; i < hesapSayisi; i++) {
        printf("Hesap Numarasi: %s\n", hesaplar[i].hesapNumarasi);
        printf("Ad: %s\n", hesaplar[i].ad);
        printf("Soyad: %s\n", hesaplar[i].soyad);
        printf("Bakiye: %.2f\n", hesaplar[i].bakiye);
        printf("-------------------------\n");
    }
}

// Hesap silme fonksiyonu
void hesapSil() {
    char hesapNumarasi[HESAP_NUMARASI_UZUNLUGU + 1];
    printf("Silmek istediginiz Hesap Numarasini Girin (12 haneli): ");
    scanf("%s", hesapNumarasi);

    int index = -1;
    for (int i = 0; i < hesapSayisi; i++) {
        // Hesap numarasina gore hesap bulunur
        if (strcmp(hesaplar[i].hesapNumarasi, hesapNumarasi) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Boyle bir hesap bulunamadi.\n");
        return;
    }

    // Hesap silinir, son hesap bilgileri bu hesaba aktariliyor
    hesaplar[index] = hesaplar[hesapSayisi - 1];
    hesapSayisi--;  // Hesap sayisi bir azaltiliyor

    printf("Hesap Basariyla Silindi.\n");
}

// Hesap numarasinin gecerli olup olmadigini kontrol etme fonksiyonu
int hesapNumarasiGecerliMi(char *hesapNumarasi) {
    if (strlen(hesapNumarasi) != HESAP_NUMARASI_UZUNLUGU) {
        return 0;  // Hesap numarasi 12 haneli degilse gecersiz
    }
    for (int i = 0; i < HESAP_NUMARASI_UZUNLUGU; i++) {
        if (hesapNumarasi[i] < '0' || hesapNumarasi[i] > '9') {
            return 0;  // Hesap numarasi yalnizca rakamlardan olusmali
        }
    }
    return 1;  // Hesap numarasi gecerli
}

// Hesap numarasinin kullanilip kullanilmadiğini kontrol etme fonksiyonu
int hesapNumarasiVarMi(char *hesapNumarasi) {
    for (int i = 0; i < hesapSayisi; i++) {
        if (strcmp(hesaplar[i].hesapNumarasi, hesapNumarasi) == 0) {
            return 1;  // Hesap numarasi zaten mevcut
        }
    }
    return 0;  // Hesap numarasi mevcut degil
}

// Hesap verilerini dosyaya kaydetme fonksiyonu
void hesapVerileriniKaydet() {
    FILE *dosya = fopen("hesaplar.dat", "wb");
    if (dosya == NULL) {
        printf("Dosya olusturulamadý.\n");
        return;
    }
    // Hesap sayisi ve hesap bilgileri dosyaya yaziliyor
    fwrite(&hesapSayisi, sizeof(int), 1, dosya);
    fwrite(hesaplar, sizeof(Hesap), hesapSayisi, dosya);
    fclose(dosya);
}

// Hesap verilerini dosyadan yukleme fonksiyonu
void hesapVerileriniYukle() {
    FILE *dosya = fopen("hesaplar.dat", "rb");
    if (dosya == NULL) {
        return;  // Dosya bulunamazsa islem yapilmaz
    }
    // Hesap sayisi ve hesap bilgileri dosyadan okunur
    fread(&hesapSayisi, sizeof(int), 1, dosya);
    fread(hesaplar, sizeof(Hesap), hesapSayisi, dosya);
    fclose(dosya);
}

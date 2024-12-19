#include <stdio.h>

// Personel bilgilerini tutan yapı
typedef struct {
    int sicilNo;
    char ad[50];
    char soyad[50];
    int satisMiktari;
} Personel;

int main() {
    FILE *yillikDosyasi, *satislarDosyasi; //Programda kullanılacak olan dosyalar için pointerlar oluşturuldu.
    Personel personel[50]; //Her personelin verilerini tutmak için dizi açıldı. En fazla 50 kişi olabileceği için eleman sayısı 50 olarak belirlendi.
    int i, maxSatis=0, personelSayisi=0;

    //Personellerin satış verilerinin olduğu dosya okuma modunda açılır.
    yillikDosyasi = fopen("yillik.dat", "r");

    //Dosyanın açılıp açılmadığını kontrol eder. Eğer açılmamışsa program durdurulur.
    if (yillikDosyasi == NULL) {
        printf("yillik.dat dosyasi acilamadi.\n");
        return 1;
    }

    //Dosyanın sonuna gelene kadar her satırdaki verileri sırasıyla ilgili adrese aktarılır.
    while (!feof(yillikDosyasi)){
        fscanf(yillikDosyasi, "%d %s %s %d", &personel[personelSayisi].sicilNo,personel[personelSayisi].ad, personel[personelSayisi].soyad,&personel[personelSayisi].satisMiktari);
        personelSayisi++;//Her satır için personel sayısı bir artırılır.
        if (personelSayisi > 50) {//Eğer personel sayısı 50'den fazlaysa program durdurulur.
            printf("50'den fazla personel girisi yapilamaz.");
            return 1;
        }

    }

    //Dosyanın görevi bittiği için dosya kapatılır. Böylece bellekte boşuna yer kaplamaz.
    fclose(yillikDosyasi);

    //En yüksek satış miktarını belirlemek için satış değerlerini tutan dizinin her elemanı, maksimum satış değeriyle karşılaştırılır. İşlemin sonunda en yüksek değer maxSatis değişkenine aktarılır.
    for (i = 0; i < personelSayisi; i++) {
        if (personel[i].satisMiktari > maxSatis) {
            maxSatis = personel[i].satisMiktari;
        }
    }

    //Personellerin ne kadar daha fazla satış yapması gerektiğini gösterecek olan dosya (satislarDosyasi) yazma modunda açılır.Dosya önceden yoksa bu adla yeni bir dosya oluşturur.
    satislarDosyasi = fopen("satislar.dat", "w");

    //Dosyanın açılıp açılmadığını kontrol eder. Eğer açılmamışsa program durdurulur.
    if (satislarDosyasi == NULL) {
        printf("satislar.dat dosyasi acilamadi.\n");
        return 1;
    }

    //Her personelin yapması gereken satış miktarı hesaplanır ve sicil no,ad,soyad değerleriyle birlikte dosyaya yazdırılır.
    for (i = 0; i < personelSayisi; i++) {
        int fark = maxSatis - personel[i].satisMiktari;
        fprintf(satislarDosyasi, "%d %s %s %d\n", personel[i].sicilNo,personel[i].ad, personel[i].soyad, fark);
    }

    //Dosyanın görevi bittiği için dosya kapatılır. Böylece bellekte boşuna yer kaplamaz.
    fclose(satislarDosyasi);

    //Personellerin verilerinin yazdırıldığını bildirir.
    printf("satislar.dat dosyasina veriler basariyla yazildi.\n");

    return 0;
}






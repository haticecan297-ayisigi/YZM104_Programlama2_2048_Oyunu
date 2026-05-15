#include "oyunMantigi.hpp"

OyunMantigi::OyunMantigi(){
    srand(static_cast<unsigned>(time(0)));  //Rastgelelik için zamanı başlat
    tahtayiSifirla();
}

void OyunMantigi::tahtayiSifirla(){
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            tahta[i][j].deger = 0;
            tahta[i][j].birlestiMi = false;
        }
    }
    //Başlangıçta 2 adet kutu ekle
    rastgeleKutuEkle();
    rastgeleKutuEkle();
}

void OyunMantigi::rastgeleKutuEkle(){
    std::vector<std::pair<int,int>>bosHucreler;  //Her biri 2 elamanlı sıkıştırılmış vektör oluşturmak için

    //Boş olan kutuları tara ve listele
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            if(tahta[i][j].deger == 0){
                bosHucreler.push_back({i,j});
            }
        }
    }

    //Boş olan yerler rastgele 2 veya 4 ekle
    if(!bosHucreler.empty()){
        int rastgeleIndeks = rand() % bosHucreler.size();
        int satir = bosHucreler[rastgeleIndeks].first;
        int sutun = bosHucreler[rastgeleIndeks].second;
         
        //%90 ihtimalle 2, %10 ile 4
        tahta[satir][sutun].deger = (rand() % 10 == 0) ? 4 : 2;
    }
}

void OyunMantigi::birlestirmeIsaretleriniTemizle() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            tahta[i][j].birlestiMi = false; 
}

void OyunMantigi::solaKaydir() {
    hareketEttiMi = false; 
    birlestirmeIsaretleriniTemizle(); 

    for (int i = 0; i < 4; i++) {
        for (int j = 1; j < 4; j++) { // İlk sütun zaten solda, 1. indisten başlıyoruz
            if (tahta[i][j].deger != 0) {
                int hedefSutun = j;

                // 1. Aşama: Boşlukları doldurarak sola kaydır
                while (hedefSutun > 0 && tahta[i][hedefSutun - 1].deger == 0) {
                    tahta[i][hedefSutun - 1].deger = tahta[i][hedefSutun].deger;
                    tahta[i][hedefSutun].deger = 0;
                    hedefSutun--;
                    hareketEttiMi = true; 
                }

                // 2. Aşama: Birleştirme kontrolü
                if (hedefSutun > 0 && 
                    tahta[i][hedefSutun - 1].deger == tahta[i][hedefSutun].deger && 
                    !tahta[i][hedefSutun - 1].birlestiMi) {
                    
                    tahta[i][hedefSutun - 1].deger *= 2; // Değeri iki katına çıkar
                    tahta[i][hedefSutun - 1].birlestiMi = true; // Aynı hamlede tekrar birleşmesin
                    tahta[i][hedefSutun].deger = 0;
                    hareketEttiMi = true; //
                }
            }
        }
    }
    
    // Eğer bir hareket olduysa yeni bir sayı ekle
    if (hareketEttiMi) {
        rastgeleKutuEkle(); //
    }
}

   // Sağa Kaydırma
    void OyunMantigi::sagaKaydir() {
        hareketEttiMi = false;
        birlestirmeIsaretleriniTemizle();
        for (int i = 0; i < 4; i++) {
            for (int j = 2; j >= 0; j--) { // 3. sütun sabit, 2'den 0'a
                if (tahta[i][j].deger != 0) {
                    int hedefSutun = j;
                    while (hedefSutun < 3 && tahta[i][hedefSutun + 1].deger == 0) {
                        tahta[i][hedefSutun + 1].deger = tahta[i][hedefSutun].deger;
                        tahta[i][hedefSutun].deger = 0;
                        hedefSutun++;
                        hareketEttiMi = true;
                    }
                    if (hedefSutun < 3 && tahta[i][hedefSutun + 1].deger == tahta[i][hedefSutun].deger && !tahta[i][hedefSutun + 1].birlestiMi) {
                        tahta[i][hedefSutun + 1].deger *= 2;
                        tahta[i][hedefSutun + 1].birlestiMi = true;
                        tahta[i][hedefSutun].deger = 0;
                        hareketEttiMi = true;
                    }
                }
            }
        }
        if (hareketEttiMi) {
        rastgeleKutuEkle(); //
    }
    }

    // YUKARI KAYDIRMA: yukarıdan aşağı doğru kontrol eder
    void OyunMantigi::yukariKaydir() {
        hareketEttiMi = false;
        birlestirmeIsaretleriniTemizle();
        for (int j = 0; j < 4; j++) {
            for (int i = 1; i < 4; i++) { // 0. satir sabit, 1'den 3'e
                if (tahta[i][j].deger != 0) {
                    int hedefSatir = i;
                    while (hedefSatir > 0 && tahta[hedefSatir - 1][j].deger == 0) {
                        tahta[hedefSatir - 1][j].deger = tahta[hedefSatir][j].deger;
                        tahta[hedefSatir][j].deger = 0;
                        hedefSatir--;
                        hareketEttiMi = true;
                    }
                    if (hedefSatir > 0 && tahta[hedefSatir - 1][j].deger == tahta[hedefSatir][j].deger && !tahta[hedefSatir - 1][j].birlestiMi) {
                        tahta[hedefSatir - 1][j].deger *= 2;
                        tahta[hedefSatir - 1][j].birlestiMi = true;
                        tahta[hedefSatir][j].deger = 0;
                        hareketEttiMi = true;
                    }
                }
            }
        }
        if (hareketEttiMi) {
        rastgeleKutuEkle(); //
    }
    }

    // ASAGI KAYDIRMA: Alttan yukari dogru kontrol et
    void OyunMantigi::asagiKaydir() {
        hareketEttiMi = false;

        birlestirmeIsaretleriniTemizle();

        for (int j = 0; j < 4; j++) {
            for (int i = 2; i >= 0; i--) { // 3. satir sabit, 2'den 0'a
                if (tahta[i][j].deger != 0) {
                    int hedefSatir = i;
                    while (hedefSatir < 3 && tahta[hedefSatir + 1][j].deger == 0) {
                        tahta[hedefSatir + 1][j].deger = tahta[hedefSatir][j].deger;
                        tahta[hedefSatir][j].deger = 0;
                        hedefSatir++;
                        hareketEttiMi = true;
                    }
                    if (hedefSatir < 3 && tahta[hedefSatir + 1][j].deger == tahta[hedefSatir][j].deger && !tahta[hedefSatir + 1][j].birlestiMi) {
                        tahta[hedefSatir + 1][j].deger *= 2;
                        tahta[hedefSatir + 1][j].birlestiMi = true;
                        tahta[hedefSatir][j].deger = 0;
                        hareketEttiMi = true;
                    }
                }
            }
        }
        if (hareketEttiMi) {
          rastgeleKutuEkle(); //
    }
    }
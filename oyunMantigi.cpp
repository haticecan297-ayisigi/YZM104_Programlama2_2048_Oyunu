#include "oyunMantigi.hpp"

OyunMantigi::OyunMantigi(){
    skor = 0;   //constructor içinde sıfırlıyoruz
    enYuksekSkor = yuksekSkoruYukle();
    yeniSayiEklenecekMi = false;  //Eklemezsem true dönüyor ve başlangıçta 3 sayı oluyor
    srand(static_cast<unsigned>(time(0)));  //Rastgelelik için zamanı başlat
    tahtayiSifirla();

    sesleriYukle();   //Nesne oluştuğunda sesleri yükle
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

        //Başlangıç yerini sabitlemek için
        tahta[satir][sutun].anlikPos = koordinatHesapla(satir, sutun);
        tahta[satir][sutun].hedefPos = tahta[satir][sutun].anlikPos;
        tahta[satir][sutun].hareketliMi = false;
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
    bool birlesmeOlduMu = false;

    for (int i = 0; i < 4; i++) {
        for (int j = 1; j < 4; j++) { // İlk sütun zaten solda, 1. indisten başlıyoruz
            if (tahta[i][j].deger != 0) {
                int hedefSutun = j;
                
                sf::Vector2f baslangicGorselPos = koordinatHesapla(i,j);

                // 1. Aşama: Boşlukları doldurarak sola kaydır
                while (hedefSutun > 0 && tahta[i][hedefSutun - 1].deger == 0) {
                    tahta[i][hedefSutun - 1].deger = tahta[i][hedefSutun].deger;
                    tahta[i][hedefSutun].deger = 0;
                    hedefSutun--;
                    hareketEttiMi = true; 
                }

                // 2. Aşama: Birleştirme kontrolü
               if (hedefSutun > 0 &&
                        tahta[i][hedefSutun - 1].deger == tahta[i][hedefSutun].deger &&   // Bir kerede birden fazla birlesmemesi icin false olmali.
                        !tahta[i][hedefSutun - 1].birlestiMi) {

                        tahta[i][hedefSutun - 1].deger *= 2;
                        skor += tahta[i][hedefSutun - 1].deger;
                        tahta[i][hedefSutun - 1].birlestiMi = true;
                        tahta[i][hedefSutun].deger = 0;
                        hareketEttiMi = true;
                        birlesmeOlduMu = true;
                    }
                    if(hareketEttiMi){
                        tahta[i][hedefSutun].anlikPos = baslangicGorselPos;
                        tahta[i][hedefSutun].hedefPos = koordinatHesapla(i,hedefSutun);
                        tahta[i][hedefSutun].hareketliMi = true;
                    }
            }
        }
    }
    
    // Eğer bir hareket olduysa yeni bir sayı ekle
    if(hareketEttiMi) {
        yeniSayiEklenecekMi = true;
        // Eğer birleşme olduysa birleşme sesini, sadece kayma olduysa kayma sesini çal
        if (sesAcikMi) {
            if (birlesmeOlduMu && birlesmeSesi) {
                birlesmeSesi->play();
            } else if (kaymaSesi) {
                kaymaSesi->play();
            }
        }
    }
}

   // Sağa Kaydırma
    void OyunMantigi::sagaKaydir() {
        hareketEttiMi = false;
        birlestirmeIsaretleriniTemizle();
        bool birlesmeOlduMu = false;
        for (int i = 0; i < 4; i++) {
            for (int j = 2; j >= 0; j--) { // 3. sütun sabit, 2'den 0'a
                if (tahta[i][j].deger != 0) {
                    int hedefSutun = j;

                    sf::Vector2f baslangicGorselPos = koordinatHesapla(i,j);

                    while (hedefSutun < 3 && tahta[i][hedefSutun + 1].deger == 0) {
                        tahta[i][hedefSutun + 1].deger = tahta[i][hedefSutun].deger;
                        tahta[i][hedefSutun].deger = 0;
                        hedefSutun++;
                        hareketEttiMi = true;
                    }
                    if (hedefSutun < 3 && tahta[i][hedefSutun + 1].deger == tahta[i][hedefSutun].deger && !tahta[i][hedefSutun + 1].birlestiMi) {
                        tahta[i][hedefSutun + 1].deger *= 2;
                        skor += tahta[i][hedefSutun + 1].deger;
                        tahta[i][hedefSutun + 1].birlestiMi = true;
                        tahta[i][hedefSutun].deger = 0;
                        hareketEttiMi = true;
                        birlesmeOlduMu = true;
                    }
                    if(hareketEttiMi){
                        tahta[i][hedefSutun].anlikPos = baslangicGorselPos;
                        tahta[i][hedefSutun].hedefPos = koordinatHesapla(i,hedefSutun);
                        tahta[i][hedefSutun].hareketliMi = true;
                    }
                }
            }
        }
        if(hareketEttiMi) {
            yeniSayiEklenecekMi = true;
            // Eğer birleşme olduysa birleşme sesini, sadece kayma olduysa kayma sesini çal
            if (sesAcikMi) {
                if (birlesmeOlduMu && birlesmeSesi) {
                    birlesmeSesi->play();
                } else if (kaymaSesi) {
                    kaymaSesi->play();
                }
            }
        }
    }

    // YUKARI KAYDIRMA: yukarıdan aşağı doğru kontrol eder
    void OyunMantigi::yukariKaydir() {
        hareketEttiMi = false;
        birlestirmeIsaretleriniTemizle();
        bool birlesmeOlduMu = false;
        for (int j = 0; j < 4; j++) {
            for (int i = 1; i < 4; i++) { // 0. satir sabit, 1'den 3'e
                if (tahta[i][j].deger != 0) {
                    int hedefSatir = i;

                    sf::Vector2f baslangicGorselPos = koordinatHesapla(i,j);

                    while (hedefSatir > 0 && tahta[hedefSatir - 1][j].deger == 0) {
                        tahta[hedefSatir - 1][j].deger = tahta[hedefSatir][j].deger;
                        tahta[hedefSatir][j].deger = 0;
                        hedefSatir--;
                        hareketEttiMi = true;
                    }
                    if (hedefSatir > 0 && tahta[hedefSatir - 1][j].deger == tahta[hedefSatir][j].deger && !tahta[hedefSatir - 1][j].birlestiMi) {
                        tahta[hedefSatir - 1][j].deger *= 2;
                        skor += tahta[hedefSatir - 1][j].deger;
                        tahta[hedefSatir - 1][j].birlestiMi = true;
                        tahta[hedefSatir][j].deger = 0;
                        hareketEttiMi = true;
                        birlesmeOlduMu = true;
                    }
                    if(hareketEttiMi){
                        tahta[hedefSatir][j].anlikPos = baslangicGorselPos;
                        tahta[hedefSatir][j].hedefPos = koordinatHesapla(hedefSatir,j);
                        tahta[hedefSatir][j].hareketliMi = true;
                    }
                }
            }
        }
        // Eğer bir hareket olduysa yeni bir sayı ekle
        if(hareketEttiMi) {
            yeniSayiEklenecekMi = true;
            // Eğer birleşme olduysa birleşme sesini, sadece kayma olduysa kayma sesini çal
            if (sesAcikMi) {
                if (birlesmeOlduMu && birlesmeSesi) {
                    birlesmeSesi->play();
                } else if (kaymaSesi) {
                    kaymaSesi->play();
                }
            }
        }
    }

    // ASAGI KAYDIRMA: Alttan yukari dogru kontrol et
    void OyunMantigi::asagiKaydir() {
        hareketEttiMi = false;

        birlestirmeIsaretleriniTemizle();

        bool birlesmeOlduMu = false;

        for (int j = 0; j < 4; j++) {
            for (int i = 2; i >= 0; i--) { // 3. satir sabit, 2'den 0'a
                if (tahta[i][j].deger != 0) {
                    int hedefSatir = i;

                    sf::Vector2f baslangicGorselPos = koordinatHesapla(i,j);

                    while (hedefSatir < 3 && tahta[hedefSatir + 1][j].deger == 0) {
                        tahta[hedefSatir + 1][j].deger = tahta[hedefSatir][j].deger;
                        tahta[hedefSatir][j].deger = 0;
                        hedefSatir++;
                        hareketEttiMi = true;
                    }
                    if (hedefSatir < 3 && tahta[hedefSatir + 1][j].deger == tahta[hedefSatir][j].deger && !tahta[hedefSatir + 1][j].birlestiMi) {
                        tahta[hedefSatir + 1][j].deger *= 2;
                        skor += tahta[hedefSatir + 1][j].deger;
                        tahta[hedefSatir + 1][j].birlestiMi = true;
                        tahta[hedefSatir][j].deger = 0;
                        hareketEttiMi = true;
                        birlesmeOlduMu = true;
                    }
                    if(hareketEttiMi){
                        tahta[hedefSatir][j].anlikPos = baslangicGorselPos;
                        tahta[hedefSatir][j].hedefPos = koordinatHesapla(hedefSatir,j);
                        tahta[hedefSatir][j].hareketliMi = true;
                    }
                }
            }
        }
        // Eğer bir hareket olduysa yeni bir sayı ekle
        if(hareketEttiMi) {
            yeniSayiEklenecekMi = true;
            // Eğer birleşme olduysa birleşme sesini, sadece kayma olduysa kayma sesini çal
            if (sesAcikMi) {
                if (birlesmeOlduMu && birlesmeSesi) {
                    birlesmeSesi->play();
                } else if (kaymaSesi) {
                    kaymaSesi->play();
                }
            }
        }
    }

    int OyunMantigi::degerAl(int satir,int sutun) const {return tahta[satir][sutun].deger;}

    int OyunMantigi::skorAl() const {return skor;}

    //Sayı kutularının renkleri
    sf::Color OyunMantigi::renkAl(int deger){
        switch(deger){
            case 2:    return sf::Color(238,228,218);      //Kirli Beyaz
            case 4:    return sf::Color(237, 224, 200);    //Krem
            case 8:    return sf::Color(242, 177, 121);    //Acik Turuncu
            case 16:   return sf::Color(245, 149, 99);     //Koyu Turuncu
            case 32:   return sf::Color(246, 124, 95);     //Mercan
            case 64:   return sf::Color(246, 94, 59);      //Parlak Kirmizi
            case 128:  return sf::Color(237, 207, 114);    //Parlak Sari
            case 256:  return sf::Color(237, 204, 97);     //Altın Sarisi
            case 512:  return sf::Color(237, 200, 80);     //Gunes Sarisi
            case 1024: return sf::Color(237, 197, 63);     //Limon Sarisi
            case 2048: return sf::Color(237, 194, 46);     //Ozel Altin
            default:   return sf::Color(205, 193, 180);    // Boş kutu rengi bej
        }
    }

    void OyunMantigi::yenidenBaslat(){
        yuksekSkoruKaydet();   //Önce mevcut skoru kaydedecek
        skor = 0;   //Oyun her başladığında güncel skor sıfır olmalı
        tahtayiSifirla();
    }

   int OyunMantigi::yuksekSkoruYukle() {
        int kayitliSkor = 0;
        ifstream dosyaOku("en_yuksek.txt");
        if (dosyaOku.is_open()) {
            dosyaOku >> kayitliSkor;
            dosyaOku.close();
        }
        return kayitliSkor;
    }

    void OyunMantigi::yuksekSkoruKaydet(){
        if(skor > enYuksekSkor){
            enYuksekSkor = skor;
        }
        ofstream dosyaYaz("en_yuksek.txt");
        if(dosyaYaz.is_open()){
            dosyaYaz <<enYuksekSkor;
            dosyaYaz.close();
        }
    }

    int OyunMantigi::enYuksekSkorAl() const {
        return (skor > enYuksekSkor) ? skor : enYuksekSkor;
    }

    // Herhangi bir kutu 2048 değerine ulaştı mı kontrolü
    bool OyunMantigi::kazandiMi() const {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (tahta[i][j].deger == 2048) {
                    return true; // 2048 bulundu, oyuncu kazandı!
                }
            }
        }
        return false;
    }

    // Hamle imkanı kaldı mı kontrolü
    bool OyunMantigi::bittiMi() const {
        //Tahtada hiç boş hücre var mı?
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (tahta[i][j].deger == 0) {
                    return false; // Boş yer varsa oyun bitmemiştir
                }
            }
        }

        //Boş yer yoksa, yan yana veya alt alta birleşebilecek kutu var mı?
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                // Sağındaki hücreyle aynı değere mi sahip?
                if (j < 3 && tahta[i][j].deger == tahta[i][j + 1].deger) return false;
                // Altındaki hücreyle aynı değere mi sahip?
                if (i < 3 && tahta[i][j].deger == tahta[i + 1][j].deger) return false;
            }
        }
        return true; 
    }

sf::Vector2f OyunMantigi::koordinatHesapla(int satir, int sutun) const {
    return {sutun * 110.f + 10.f, satir * 110.f + 110.f};
}

void OyunMantigi::guncelle() {
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            tahta[i][j].guncelle(); // Kutu içindeki animasyonu tetikler
}

bool OyunMantigi::hareketDevamEdiyorMu() const {
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            if(tahta[i][j].hareketliMi) return true;
    return false;
}

/*sf::Vector2f OyunMantigi::anlikPosAl(int satir, int sutun) const {
    if(tahta[satir][sutun].deger == 0) return koordinatHesapla(satir, sutun);
    return tahta[satir][sutun].anlikPos;
}*/

const Kutu& OyunMantigi::kutuAl(int i, int j) const { return tahta[i][j]; }

void OyunMantigi::sesleriYukle() {
    // Sol paneldeki dosya uzantılarına tam uygun şekilde yüklüyoruz
    if (!kaymaBuffer.loadFromFile("kayma.ogg")) { /* Hata yönetimi */ }
    if (!birlesmeBuffer.loadFromFile("birlesme.ogg")) { }
    if (!kazanmaBuffer.loadFromFile("kazanma.wav")) { }
    if (!kaybetmeBuffer.loadFromFile("kaybetme.wav")) { }

    // setBuffer yerine emplace kullanıyoruz: Buffer'ı vererek anında sf::Sound yaratır
    kaymaSesi.emplace(kaymaBuffer);
    birlesmeSesi.emplace(birlesmeBuffer);
    kazanmaSesi.emplace(kazanmaBuffer);
    kaybetmeSesi.emplace(kaybetmeBuffer);
    
    // -> operatörü ile ayarlara erişiyoruz
    kaymaSesi->setVolume(50.f); 
    birlesmeSesi->setVolume(70.f);
}

void OyunMantigi::kazanmaSesiCal() {
    // Önce ses yüklendi mi diye kontrol ediyoruz (kazanmaSesi doluysa çalışır)
    if (kazanmaSesi && kazanmaSesi->getStatus() != sf::Sound::Status::Playing) {
        kazanmaSesi->play();
    }
}

void OyunMantigi::kaybetmeSesiCal() {
    if (kaybetmeSesi && kaybetmeSesi->getStatus() != sf::Sound::Status::Playing) {
        kaybetmeSesi->play();
    }
}
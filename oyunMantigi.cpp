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
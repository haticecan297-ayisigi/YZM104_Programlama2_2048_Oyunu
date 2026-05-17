#ifndef OYUNMANTIGI_HPP
#define OYUNMANTIGI_HPP
#include <vector>
#include "kutu.hpp"
#include <ctime>
#include <cstdlib>
#include <fstream>   //Dosyalama için

using namespace std;

class OyunMantigi{
    private:
    Kutu tahta[4][4];   //4*4 oyun alanı
    void rastgeleKutuEkle();   //Başlangıçta ve sonrasında rastgele sayı eklemek için
    bool hareketEttiMi; // Hamle sonucunda bir değişiklik oldu mu kontrolü
    void birlestirmeIsaretleriniTemizle(); // Her hamle başında birleşme durumunu sıfırlar
    int skor; //Güncel skor değişkeni
    int enYuksekSkor;

    public:

    OyunMantigi();

    void tahtayiSifirla();   //Oyunu başlangıç haline getirmek için
    void solaKaydir(); // Sola kaydırma ana fonksiyonu
    void sagaKaydir();
    void yukariKaydir();
    void asagiKaydir();

    //Test ve görselleştirme için getter
    int degerAl(int satir,int sutun) const;

    sf::Color renkAl(int deger);

    void yenidenBaslat();

    int skorAl() const;  //Skor privite olduğu için okuması lazım
    
    // Dosyadan okuma işlemi
    int yuksekSkoruYukle();

    // Dosyaya yazma işlemi
    void yuksekSkoruKaydet();

     // Oyun sırasında anlık güncelleme kontrolü ile rekoru döndür
    int enYuksekSkorAl() const;

    //Oyun durum kontrolleri
    bool kazandiMi() const;
    bool bittiMi() const;

};
#endif 
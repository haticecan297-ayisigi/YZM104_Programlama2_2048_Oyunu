#ifndef OYUNMANTIGI_HPP
#define OYUNMANTIGI_HPP
#include <vector>
#include "kutu.hpp"
#include <ctime>
#include <cstdlib>

using namespace std;

class OyunMantigi{
    private:
    Kutu tahta[4][4];   //4*4 oyun alanı
    void rastgeleKutuEkle();   //Başlangıçta ve sonrasında rastgele sayı eklemek için

    public:

    OyunMantigi();

    void tahtayiSifirla();   //Oyunu başlangıç haline getirmek için

    //Test ve görselleştirme için getter
    int degerAl(int satir,int sutun) const {return tahta[satir][sutun].deger;}
    
};
#endif 
#ifndef kutu_hpp
#define kutu_hpp
#include <SFML/Graphics.hpp>

struct Kutu{
    int deger;  //Sayı değerleri: 2,4,8...
    bool birlestiMi;    //Bir hamleden sonra kutuların birleşme durun konrolü
    

    //Animasyon altyapısı
    sf::Vector2f anlikPos;
    sf::Vector2f hedefPos;
    bool hareketliMi;

    Kutu():deger(0),birlestiMi(false){}   //Varsayılan kurucu
    
    float hizi = 0.4f;
    
     void guncelle(){
        //Hareket animasyonu
        if(hareketliMi){
            sf::Vector2f fark = hedefPos - anlikPos;

            if(std::abs(fark.x) < 1.0f && std::abs(fark.y)<1.0f){
                anlikPos = hedefPos;
                hareketliMi = false;
            }else{
                anlikPos += fark * hizi;
            }
        }
    }
};
#endif 
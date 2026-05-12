#ifndef kutu_hpp
#define kutu_hpp
#include <SFML/Graphics.hpp>

struct Kutu{
    int deger;  //Sayı değerleri: 2,4,8...
    bool birlestiMi;    //Bir hamleden sonra kutuların birleşme durun konrolü
    Kutu():deger(0),birlestiMi(false){}   //Varsayılan kurucu
};
#endif 
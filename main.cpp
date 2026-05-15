#include <iostream>
#include <SFML/Graphics.hpp>
#include "oyunMantigi.hpp"
#include <string>
#include <optional>

using namespace std;

int main() {
    //Kütüphane ile oyun penceresi açıyorum
    sf::RenderWindow pencere(sf::VideoMode({450,450}),"2048");
    pencere.setFramerateLimit(60);   //Zaman yönetimi için

    OyunMantigi oyun;   // OyunMAntigi türünde bir değişken atıyorum
    sf::Font font;    //Çizim için

    //Font yükleme kontrolü
    if(!font.openFromFile("arial.ttf")){
        cout<< "HATA: arial.ttf dosyasi bulunamadi!"<<endl;
    }

    //Oyun penceresi kapatılana kadar açık kalması için
    while(pencere.isOpen()){
        while(const optional olay = pencere.pollEvent()){
            if(olay->is<sf::Event::Closed>()){     //X basınca kapanması için
                pencere.close();
            }
        }

         pencere.clear(sf::Color(187, 173, 160)); // Arka plan rengi

        // 4x4 Izgarayı ve Sayıları Çizme (Matriks Mantığı)
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                // Tahta private olduğu için getter fonksiyonunu kullanıyoruz
                int deger = oyun.degerAl(i, j); 

                //Kareyi (Kutuyu) çizmek için
                sf::RectangleShape kare(sf::Vector2f({100.f, 100.f}));
                kare.setPosition({j * 110.f + 10.f, i * 110.f + 10.f});
                
                // Sayı değerine göre rengi sınıftaki fonksiyonu slmsk için
                kare.setFillColor(oyun.renkAl(deger)); 
                pencere.draw(kare);

                //Sayıyı Çiz
                if (deger != 0) {
                    sf::Text metin(font);
                    metin.setString(to_string(deger));
                    metin.setCharacterSize(35);
                    
                    // Sayı rengi: 4 ve altı için koyu, üstü için beyaz
                    metin.setFillColor(deger <= 4 ? sf::Color(119, 110, 101) : sf::Color::White);

                    // sf::FloatRect artık 'size' üyesine sahiptir (size.x = width).
                    const sf::FloatRect metinBoyut = metin.getLocalBounds();
                    metin.setOrigin({metinBoyut.size.x / 2.0f, metinBoyut.size.y / 2.0f});
                    
                    // Merkeze yerleştirme(Ortalama): Kutunun başlangıcı + Kutunun yarısı (50.f)
                    metin.setPosition({j * 110.f + 10.f + 50.f, i * 110.f + 10.f + 50.f});

                    pencere.draw(metin);
                }
            }
        }

        //Ekrana Yansıtma
        pencere.display();
    }
    

    return 0;
}
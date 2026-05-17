#include <iostream>
#include <SFML/Graphics.hpp>
#include "oyunMantigi.hpp"
#include <string>
#include <optional>

using namespace std;

int main() {
    //Kütüphane ile oyun penceresi açıyorum
    sf::RenderWindow pencere(sf::VideoMode({450,560}),"2048");   // Üst kısmına logo ve skor eklemek için değiştirildi
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
                oyun.yuksekSkoruKaydet();   //Pencere kapanınca skoru kaydedecek
                pencere.close();
            }

            // Klavye girisi kontrolu
            if (const auto* basilanTus = olay->getIf<sf::Event::KeyPressed>()) {
                if (basilanTus->code == sf::Keyboard::Key::Left)       oyun.solaKaydir();
                else if (basilanTus->code == sf::Keyboard::Key::Right) oyun.sagaKaydir();
                else if (basilanTus->code == sf::Keyboard::Key::Up)    oyun.yukariKaydir();
                else if (basilanTus->code == sf::Keyboard::Key::Down)  oyun.asagiKaydir();
                else if (basilanTus->code == sf::Keyboard::Key::R) oyun.yenidenBaslat();
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
                kare.setPosition({j * 110.f + 10.f, i * 110.f + 110.f});
                
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
                    metin.setPosition({j * 110.f + 10.f + 50.f, i * 110.f + 110.f + 50.f});

                    pencere.draw(metin);
                }

                //Oyun Logosu
                sf::Text logo(font);
                logo.setString("2048");
                logo.setCharacterSize(45);
                logo.setFillColor(sf::Color(119, 110, 101));
                logo.setStyle(sf::Text::Bold);
                logo.setPosition({20.f, 20.f});
                pencere.draw(logo);

                // 2. Anlık Skor Kutusu ve Yazısı
                sf::RectangleShape skorKutusu(sf::Vector2f({100.f, 50.f}));
                skorKutusu.setPosition({220.f, 25.f});
                skorKutusu.setFillColor(sf::Color(187, 173, 160));
                pencere.draw(skorKutusu);

                sf::Text skorBaslik(font);
                skorBaslik.setString("SCORE:");
                skorBaslik.setCharacterSize(14);
                skorBaslik.setFillColor(sf::Color(238, 228, 218));
                skorBaslik.setPosition({248.f, 30.f});
                pencere.draw(skorBaslik);

                sf::Text skorDeger(font);
                skorDeger.setString(to_string(oyun.skorAl()));
                skorDeger.setCharacterSize(20);
                skorDeger.setFillColor(sf::Color::White);
                 // Ortalamak icin:
                sf::FloatRect sdBounds = skorDeger.getLocalBounds();
                skorDeger.setPosition({270.f - sdBounds.size.x / 2.f, 48.f});
                pencere.draw(skorDeger);

                // 3. En İyi Skor Kutusu ve Yazısı
                sf::RectangleShape bestKutusu(sf::Vector2f({100.f, 50.f}));
                bestKutusu.setPosition({330.f, 25.f});
                bestKutusu.setFillColor(sf::Color(187, 173, 160));
                pencere.draw(bestKutusu);

                sf::Text bestBaslik(font);
                bestBaslik.setString("BEST:");
                bestBaslik.setCharacterSize(14);
                bestBaslik.setFillColor(sf::Color(238, 228, 218));
                bestBaslik.setPosition({365.f, 30.f});
                pencere.draw(bestBaslik);

                sf::Text bestDeger(font);
                bestDeger.setString(to_string(oyun.enYuksekSkorAl()));
                bestDeger.setCharacterSize(20);
                bestDeger.setFillColor(sf::Color::White);
                sf::FloatRect bdBounds = bestDeger.getLocalBounds();
                bestDeger.setPosition({380.f - bdBounds.size.x / 2.f, 48.f});
                pencere.draw(bestDeger);

                //Oyun sonu ekranı çizimi
                if (oyun.kazandiMi() || oyun.bittiMi()) {
                    // Arka planı yarı saydam karartmak için dikdörtgen
                    sf::RectangleShape ekranKarartma(sf::Vector2f({450.f, 560.f}));
                    // Alpha değerini (180) ayarlayarak arkadaki sayıların görünmesini sağlıyoruz
                    ekranKarartma.setFillColor(sf::Color(237, 224, 200, 180)); 
                    pencere.draw(ekranKarartma);

                    // Sonuç Metni
                    sf::Text sonucMetni(font);
                    if (oyun.kazandiMi()) {
                        sonucMetni.setString("YOU WON!");
                    } else {
                        sonucMetni.setString("GAME OVER!");
                    }
                    
                    sonucMetni.setCharacterSize(45);
                    sonucMetni.setFillColor(sf::Color(119, 110, 101));
                    sonucMetni.setStyle(sf::Text::Bold);
                    
                    // Metni tam merkeze hizalama
                    const sf::FloatRect metinBoyut = sonucMetni.getLocalBounds();
                    sonucMetni.setOrigin({metinBoyut.size.x / 2.0f, metinBoyut.size.y / 2.0f});
                    sonucMetni.setPosition({225.f, 260.f}); // X'in ortası 225, Y'nin ortasına yakın
                    pencere.draw(sonucMetni);

                    // Bilgilendirme Metni
                    sf::Text bilgiMetni(font);
                    bilgiMetni.setString("press R to replay");
                    bilgiMetni.setCharacterSize(20);
                    bilgiMetni.setFillColor(sf::Color(119, 110, 101));
                    
                    const sf::FloatRect bilgiBoyut = bilgiMetni.getLocalBounds();
                    bilgiMetni.setOrigin({bilgiBoyut.size.x / 2.0f, bilgiBoyut.size.y / 2.0f});
                    bilgiMetni.setPosition({225.f, 320.f});
                    pencere.draw(bilgiMetni);
                }
            }
        }

        //Ekrana Yansıtma
        pencere.display();
    }
    

    return 0;
}
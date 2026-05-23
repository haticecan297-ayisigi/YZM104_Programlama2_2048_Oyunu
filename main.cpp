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

    //Ses ikonu yükleme
    sf::Texture sesAcikTex, sesKapaliTex;
    bool ikonlarYuklendi = true;
    
    if (!sesAcikTex.loadFromFile("sound_on.png") || !sesKapaliTex.loadFromFile("sound_off.png")) {
        cout << "HATA: Ses ikonlari bulunamadi!" << endl;
        ikonlarYuklendi = false;
    }
    
   std::optional<sf::Sprite> sesIkonu; 
    
    if (ikonlarYuklendi) {
        sesIkonu.emplace(sesAcikTex); 
        
        //orijinal resmin piksel boyutlarını alıyoruz
        sf::Vector2u resimBoyutu = sesAcikTex.getSize();
        
        //İkonun ekranda ne kadar yer kaplayacağını seçiyoruz
        float hedefGenişlik = 30.f; 
        
        //Ölçekleme oranını hesaplıyoruz (Hedef Boyut / Orijinal Boyut)
        float olcek = hedefGenişlik / resimBoyutu.x; 
        
        //Resmi hesaplanan oranda küçültüyoruz
        sesIkonu->setScale({olcek, olcek});
        
        // İkonu best kutusunun tam altına (Y: 85) ortalayarak (X: 365) yerleştiriyoruz
        sesIkonu->setPosition({365.f, 77.f}); 
    }

    // --- Yeniden Başlat Butonu ---
    sf::RectangleShape resetButonu(sf::Vector2f(80.f, 30.f));
    resetButonu.setFillColor(sf::Color(143, 122, 102)); // Biraz daha koyu bir kahve
    resetButonu.setPosition({20.f, 75.f}); // Logonun hemen

    bool oyunBittiSesiCaldiMi = false;   //Sesi bir kere çalmak için

    //Oyun penceresi kapatılana kadar açık kalması için
    while(pencere.isOpen()){

        oyun.guncelle();   //her karede animasyonları 1 adım ilerlet

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
            }

            // YENİ EKLENEN: Fare Tıklama Kontrolü
            if (const auto* tiklama = olay->getIf<sf::Event::MouseButtonPressed>()) {
                    if (tiklama->button == sf::Mouse::Button::Left) {
                        // Fare pozisyonunu al
                        sf::Vector2i farePos = sf::Mouse::getPosition(pencere);

                        // Butonun kapsama alanını (Global Bounds) al
                        sf::FloatRect butonAlani = resetButonu.getGlobalBounds();

                        // Fare koordinatı butonun içinde mi? (AABB Collision)
                        if (butonAlani.contains(sf::Vector2f(farePos))) {
                            oyun.yenidenBaslat();
                            oyunBittiSesiCaldiMi = false;
                        }

                        //Ses İkonu Kontrolü
                        if (ikonlarYuklendi && sesIkonu && sesIkonu->getGlobalBounds().contains(sf::Vector2f(farePos))) {
                            oyun.sesAcikMi = !oyun.sesAcikMi; // Açıksa kapat, kapalıysa aç
                        }
                    }
                }
        }

        oyun.guncelle();  //Animasyonları ilerletir

        //Animasyon bitince sayi ekle
        if(oyun.yeniSayiEklenecekMi && !oyun.hareketDevamEdiyorMu()){
            oyun.rastgeleKutuEkle();
            oyun.yeniSayiEklenecekMi = false;  //Gorev tamamlandi
        }

       pencere.clear(sf::Color(187, 173, 160)); // Arka plan rengi
        
        // --- 1. ARAYÜZ (UI) ÇİZİMLERİ (Döngülerin Dışında!) ---
        
        // Oyun Logosu
        sf::Text logo(font);
        logo.setString("2048");
        logo.setCharacterSize(45);
        logo.setFillColor(sf::Color(119, 110, 101));
        logo.setStyle(sf::Text::Bold);
        logo.setPosition({20.f, 20.f});
        pencere.draw(logo);

        // Skor Kutusu
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
        sf::FloatRect sdBounds = skorDeger.getLocalBounds();
        skorDeger.setPosition({270.f - sdBounds.size.x / 2.f, 48.f});
        pencere.draw(skorDeger);

        // En İyi Skor Kutusu
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

        // YENİ DÜZELTİLEN: Reset Butonu Çizimi
        pencere.draw(resetButonu); // Önce butonun kahverengi şeklini çiziyoruz
        
        sf::Text resetYazisi(font);
        resetYazisi.setString("RESET");
        resetYazisi.setCharacterSize(14);
        resetYazisi.setFillColor(sf::Color::White);
        sf::FloatRect ryBounds = resetYazisi.getLocalBounds();
        resetYazisi.setOrigin({ryBounds.size.x / 2.f, ryBounds.size.y / 2.f});
        // Pozisyonu resetButonu değişkeninle aynı hizada ayarlıyoruz
        resetYazisi.setPosition({20.f + 40.f, 75.f + 15.f}); 
        pencere.draw(resetYazisi); // Sonra üstüne beyaz yazıyı çiziyoruz

        //Ses İkonu Çizimi
        if (ikonlarYuklendi) {
            if (oyun.sesAcikMi) {
                sesIkonu->setTexture(sesAcikTex);
            } else {
                sesIkonu->setTexture(sesKapaliTex);
            }
            pencere.draw(*sesIkonu);
        }


        // --- 2. OYUN TAHTASI ÇİZİMLERİ ---
        
        // Önce boş hücreleri çiziyoruz
        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                sf::RectangleShape bosKutu(sf::Vector2f({100.f, 100.f}));
                bosKutu.setPosition({j * 110.f + 10.f, i * 110.f + 110.f});
                bosKutu.setFillColor(sf::Color(205,193,180));  
                pencere.draw(bosKutu);
            }
        }

        // Sonra dolu ve hareketli kutuları çiziyoruz
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                Kutu k = oyun.kutuAl(i,j);
                if (k.deger != 0) {
                    sf::RectangleShape kutuSekil(sf::Vector2f({100.f, 100.f}));
                    kutuSekil.setPosition(k.anlikPos); 
                    kutuSekil.setFillColor(oyun.renkAl(k.deger));
                    pencere.draw(kutuSekil);

                    sf::Text metin(font, std::to_string(k.deger), 32);
                    // Rengi beyaz veya koyu yapma mantığını geri getirdim
                    metin.setFillColor(k.deger <= 4 ? sf::Color(119, 110, 101) : sf::Color::White);
                    
                    sf::FloatRect metinBoyut = metin.getLocalBounds();
                    metin.setOrigin({metinBoyut.size.x / 2.0f, metinBoyut.size.y / 2.0f});
                    metin.setPosition({k.anlikPos.x + 50.f, k.anlikPos.y + 50.f});
                    pencere.draw(metin);
                }
            }
        }

        // --- 3. OYUN SONU EKRANI ---
        if (oyun.kazandiMi() || oyun.bittiMi()) {

            // YENİ: Ses çalma mantığı
            if (!oyunBittiSesiCaldiMi) {
                if (oyun.kazandiMi()) {
                    oyun.kazanmaSesiCal();
                } else {
                    oyun.kaybetmeSesiCal();
                }
                oyunBittiSesiCaldiMi = true; // Sadece ilk seferde çalışacak
            }


            sf::RectangleShape ekranKarartma(sf::Vector2f({450.f, 560.f}));
            ekranKarartma.setFillColor(sf::Color(237, 224, 200, 180)); 
            pencere.draw(ekranKarartma);

            sf::Text sonucMetni(font);
            sonucMetni.setString(oyun.kazandiMi() ? "YOU WON!" : "GAME OVER!");
            sonucMetni.setCharacterSize(45);
            sonucMetni.setFillColor(sf::Color(119, 110, 101));
            sonucMetni.setStyle(sf::Text::Bold);
            
            const sf::FloatRect metinBoyut = sonucMetni.getLocalBounds();
            sonucMetni.setOrigin({metinBoyut.size.x / 2.0f, metinBoyut.size.y / 2.0f});
            sonucMetni.setPosition({225.f, 260.f}); 
            pencere.draw(sonucMetni);

            sf::Text bilgiMetni(font);
            bilgiMetni.setString("Click RESET to replay");
            bilgiMetni.setCharacterSize(20);
            bilgiMetni.setFillColor(sf::Color(119, 110, 101));
            
            const sf::FloatRect bilgiBoyut = bilgiMetni.getLocalBounds();
            bilgiMetni.setOrigin({bilgiBoyut.size.x / 2.0f, bilgiBoyut.size.y / 2.0f});
            bilgiMetni.setPosition({225.f, 320.f});
            pencere.draw(bilgiMetni);
        }

        // Ekrana Yansıtma
        pencere.display();
    }
    
    return 0;
}
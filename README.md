# 2048 – Sayı Birleştirme Bulmaca Oyunu

![C++17](https://img.shields.io/badge/language-C++17-blue) ![SFML](https://img.shields.io/badge/library-SFML-green) ![Status](https://img.shields.io/badge/status-active-success)

---

## 1. Proje Hakkında

2048, C++ programlama dili ve SFML kütüphanesi kullanılarak geliştirilmiş, mantık ve stratejiye dayalı tek oyunculu bir bulmaca oyunudur. YZM104 Programlama II dersi dönem projesi kapsamında hazırlanan bu oyunda oyuncu; 4x4'lük bir ızgarada rastgele beliren 2 ve 4 değerli karoları yön tuşlarıyla kaydırarak aynı olanları birleştirir ve 2048 değerine ulaşarak en yüksek skoru elde etmeye çalışır.

---

## 🎥 Proje Demo Videosu
Oyunun oynanış mekaniklerini, arayüz özelliklerini ve ses efektlerini içeren demo videosunu izlemek için aşağıdaki bağlantıya tıklayabilirsiniz:

👉 [2048 Oyun Projesi - Demo Videosunu İzle](https://drive.google.com/file/d/1l-cHvAzC_ulcjDLahF-X0nPo3plelxDy/view?usp=sharing)

---

## 2. Özellikler

**Dinamik Oyun Akışı**
* **Rastgele Üretim:** Her geçerli hamleden sonra boş bir hücrede rastgele olarak %90 ihtimalle 2, %10 ihtimalle 4 değeri belirir.
* **Akıcı Animasyonlar:** Karoların kayma ve birleşme hareketleri, başlangıç ve hedef koordinatları hesaplanarak yumuşak geçişlerle ekrana çizilir.

**Kalıcı Skor Sistemi**
* **Skor Takibi:** Her başarılı birleşmede anlık skor artışı hesaplanır ve arayüzde gösterilir.
* **Kayıt Sistemi:** Oyun kapatıldığında elde edilen en yüksek skor `en_yuksek.txt` dosyasına kalıcı olarak kaydedilir ve sonraki açılışlarda "BEST" tablosunda listelenir.

**Arayüz ve Durum Yönetimi**
* **Durum Makinesi (State Machine):** Başlangıç Menüsü, Oyun İçi, Oyun Sonu (Kazanma/Kaybetme) ekranları arasında sorunsuz ve hatasız geçişler.
* **İşitsel Geri Bildirim:** Kayma, birleşme, kazanma ve kaybetme durumları için anında devreye giren özel ses efektleri (Arayüzdeki ikon üzerinden tıklanarak anlık olarak kapatılıp açılabilir).

---

## 3. Teknoloji Yığını

| Kategori | Teknoloji | Açıklama |
| :--- | :--- | :--- |
| **Programlama Dili** | C++ (Standart C++17) | Ana oyun mantığı, matris hesaplamaları ve durum yönetimi |
| **Grafik Kütüphanesi** | SFML | Pencere oluşturma, görüntü çizimi, fontlar ve ses motoru yönetimi |
| **Geliştirme Ortamı** | VS Code / CLion | Tercih edilen IDE/Editör |

---

## 4. Kontroller

Oyun mantığı yön tuşlarına, arayüz etkileşimi ise fareye dayalı olarak tasarlanmıştır:

| Eylem | Tuş / Kontrol |
| :--- | :--- |
| **Karoları Kaydırma** | Yön Tuşları (⬅️ ⬆️ ⬇️ ➡️) |
| **Etkileşim (Başlat/Reset/Ses)** | Farenin Sol Tuşu |
| **Oyundan Çıkış** | Pencereyi Kapatma İkonu (X) |

---

## 5. Proje Nasıl Çalıştırılır?

**Ön Gereksinimler**

* C++ Derleyicisi (MinGW / GCC vb.)
* SFML Kütüphanelerinin (Graphics, Window, System, Audio) sisteme tanımlı olması

**Kurulum Adımları**

1. **Depoyu İndirin:** Proje dosyalarını bilgisayarınıza indirin veya `git clone` komutu ile yerelinize kopyalayın.
2. **Derleme (Terminal üzerinden):** Proje dizinine gidin ve dosyaları SFML ile linkleyerek derleyin:
   `g++ main.cpp oyunMantigi.cpp -o 2048_Game -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio`
3. **Çalıştırma:** Oluşturulan çalıştırılabilir dosyayı başlatın:
   `./2048_Game`

* **Not:** Oyunun düzgün çalışabilmesi için projede kullanılan tüm görsel (`sound_on.png`, `sound_off.png`), işitsel (`.ogg`, `.wav` formatındaki ses efektleri) ve font (`arial.ttf`) dosyalarının, çalıştırılabilir `.exe` dosyası ile aynı dizinde bulunduğundan emin olun.

---

## 6. Proje Yapısı

* **`main.cpp`:** Oyun döngüsü (game loop), olay (event) yakalama, fare/klavye kontrolleri ve SFML render işlemleri.
* **`oyunMantigi.hpp / .cpp`:** Temel oyun kuralları, matris kaydırma algoritmaları, skor yönetimi ve dosya okuma/yazma işlemleri.
* **`kutu.hpp`:** Izgaradaki her bir hücrenin anlık değerini, hareket animasyonu için pozisyon vektörlerini ve birleşme durumlarını tutan yapı.
* **Medya Dosyaları:** Oyun içi varlıklar (Buton ikonları, ses efektleri ve font).

# 🎮 Arduino Tower Game (Stacker)

<details open>
<summary>🇹🇷 <strong>Türkçe</strong></summary>

## 📖 Proje Hakkında

Bu proje, klasik atari salonu oyunu olan "Stacker"ın Arduino ve LED matris modülleri kullanılarak geliştirilmiş interaktif bir versiyonudur. Projenin temel amacı, refleks ve zamanlama yeteneğini kullanarak hareket eden ışık bloklarını üst üste hatasız bir şekilde dizmek ve kulenin en tepesine ulaşmaktır.

![Arduino Tower Game](diagram-image/circuit_diagram.png)

## ✨ Özellikler

- **Dinamik Oynanış**: Oyun 5 piksel genişliğinde bir blokla başlar ve her seviyede blok boyutu küçülebilir
- **Otomatik Zorluk Artışı**: Kule yükseldikçe blokların hareket hızı otomatik olarak artar
- **Hassas Buton Kontrolü**: Milisaniyelik tepkime süresi için optimize edilmiş buton algılama
- **Görsel Efektler**: Kazanma ve kaybetme animasyonları
- **Kompakt Tasarım**: Breadboard üzerinde tam fonksiyonel çalışma

## 🔧 Donanım Gereksinimleri

- **Arduino Uno** (1 adet)
- **MAX7219 8x8 Dot Matrix LED Modül** (3 adet)
- **Push Button** (1 adet)
- **Breadboard ve Jumper Kablolar**
- **5V Güç Kaynağı** (Arduino USB veya harici)

### Donanım Yapısı

Projede 3 adet MAX7219 8x8 LED matris modülü dikey (portrait) olarak konumlandırılarak **8x24 piksellik** uzun bir oyun kulesi oluşturulmuştur.

**Bağlantı Mimarisi:**
- **Güç ve Saat Sinyalleri**: Tüm modüllere paralel (Bus/Ortak Hat yöntemi)
  - 5V ve GND → Tüm modüllere ortak
  - CLK (Clock) → Tüm modüllere ortak
  - CS (Chip Select) → Tüm modüllere ortak
- **Veri Sinyali**: Seri zincir (Daisy Chain yöntemi)
  - DIN → DOUT şeklinde modülden modüle aktarılır

## 📦 Kurulum

### 1. Kütüphane Kurulumu

Projenin çalışması için **LedControl** kütüphanesinin Arduino IDE'ye yüklenmesi gerekmektedir:

1. Arduino IDE'yi açın
2. **Sketch** → **Include Library** → **Manage Libraries** menüsüne gidin
3. Arama kutusuna `LedControl` yazın
4. **LedControl by Eberhard Fahle** kütüphanesini bulun ve yükleyin

### 2. Devre Bağlantısı

Devre şemasına göre bağlantıları yapın:

![Devre Şeması](diagram-image/circuit_diagram.png)

### 3. Kod Yükleme

1. `sketch_nov26a/sketch_nov26a.ino` dosyasını Arduino IDE ile açın
2. Arduino Uno'yu bilgisayara bağlayın
3. Doğru port ve kartı seçin (**Tools** → **Board** → **Arduino Uno**)
4. **Upload** butonuna tıklayarak kodu yükleyin

## 🎯 Nasıl Oynanır

1. Oyun otomatik olarak başlar ve alt seviyeden itibaren ışık blokları sağa-sola hareket eder
2. Bloğu durdurmak için **butona basın**
3. Blok, alttaki katla hizalanmazsa taşan kısımlar kesilir ve blok küçülür
4. Her seviyede hareket hızı artar
5. Kulenin tepesine ulaştığınızda oyunu kazanırsınız!
6. Blok tamamen kaybolursa oyun biter

## 🛠️ Teknik Detaylar

### Yazılım Mimarisi

- **Kütüphane**: LedControl (by Eberhard Fahle)
- **Zamanlama**: `millis()` tabanlı non-blocking timer sistemi
- **Buton Algoritması**: 
  - **State Change Detection**: Durum değişikliği algılama
  - **Debounce**: Mekanik titreme önleme (ark önleme)
  - Standart `delay()` yerine milisaniye hassasiyetinde tepki süresi

### Performans Optimizasyonları

Projenin en kritik geliştirmesi **buton tepkime süresi** optimizasyonudur:
- Standart `delay()` komutları tamamen kaldırılmıştır
- Millis-based zamanlayıcılar ile non-blocking kod yapısı
- Debounce algoritması ile çift basma hatalarının önlenmesi
- Milisaniyelik hassasiyette tepki süresi

### Donanım Adaptasyonu

Başlangıçta 4 modül planlanmışken, yapılan testler ve donanım optimizasyonu sonucu proje **3 modüle** başarıyla uyarlanmıştır. Bu esneklik, projenin modüler yazılım mimarisi sayesinde mümkün olmuştur.

## 🏗️ Proje Yapısı

```
arduino-tower-game/
│
├── sketch_nov26a/
│   └── sketch_nov26a.ino    # Ana Arduino kodu
│
├── diagram-image/
│   └── circuit_diagram.png   # Devre şeması
│
└── README.md                 # Proje dokümantasyonu
```

## 🎓 Öğrenilen Kavramlar

- MAX7219 LED matris kontrolü
- SPI benzeri seri haberleşme (Daisy Chain)
- Non-blocking zamanlama teknikleri
- Debounce algoritmaları
- State machine pattern
- Gerçek zamanlı oyun geliştirme

## 🤝 Katkıda Bulunma

Bu proje eğitim amaçlı geliştirilmiştir. Geliştirmeler ve öneriler için Pull Request açabilirsiniz.

---

⭐ Projeyi beğendiyseniz yıldız vermeyi unutmayın!

</details>

<details>
<summary>🇬🇧 <strong>English</strong></summary>

## 📖 About the Project

This project is an interactive version of the classic arcade game "Stacker", developed using Arduino and LED matrix modules. The main objective is to use your reflexes and timing skills to stack moving light blocks on top of each other without errors and reach the top of the tower.

![Arduino Tower Game](diagram-image/circuit_diagram.png)

## ✨ Features

- **Dynamic Gameplay**: The game starts with a 5-pixel wide block, and the block size can decrease with each level.
- **Automatic Difficulty Increase**: As the tower rises, the movement speed of the blocks automatically increases.
- **Precise Button Control**: Button detection optimized for millisecond response time.
- **Visual Effects**: Winning and losing animations.
- **Compact Design**: Fully functional operation on a breadboard.

## 🔧 Hardware Requirements

- **Arduino Uno** (1 unit)
- **MAX7219 8x8 Dot Matrix LED Module** (3 units)
- **Push Button** (1 unit)
- **Breadboard and Jumper Wires**
- **5V Power Supply** (Arduino USB or external)

### Hardware Structure

The project uses 3 MAX7219 8x8 LED matrix modules positioned vertically (portrait) to create a tall **8x24 pixel** game tower.

**Connection Architecture:**
- **Power and Clock Signals**: Parallel to all modules (Bus/Common Line method)
  - 5V and GND → Common to all modules
  - CLK (Clock) → Common to all modules
  - CS (Chip Select) → Common to all modules
- **Data Signal**: Serial chain (Daisy Chain method)
  - DIN → DOUT transferred from module to module

## 📦 Installation

### 1. Library Installation

For the project to work, the **LedControl** library needs to be installed in the Arduino IDE:

1. Open Arduino IDE.
2. Go to **Sketch** → **Include Library** → **Manage Libraries**.
3. Type `LedControl` in the search box.
4. Find and install the **LedControl by Eberhard Fahle** library.

### 2. Circuit Connection

Make the connections according to the circuit diagram:

![Circuit Diagram](diagram-image/circuit_diagram.png)

### 3. Uploading Code

1. Open the `sketch_nov26a/sketch_nov26a.ino` file with Arduino IDE.
2. Connect the Arduino Uno to your computer.
3. Select the correct port and board (**Tools** → **Board** → **Arduino Uno**).
4. Click the **Upload** button to upload the code.

## 🎯 How to Play

1. The game starts automatically, and light blocks move left and right starting from the bottom level.
2. **Press the button** to stop the block.
3. If the block is not aligned with the layer below, the overflowing parts are cut off, and the block shrinks.
4. The movement speed increases with each level.
5. You win the game when you reach the top of the tower!
6. The game ends if the block completely disappears.

## 🛠️ Technical Details

### Software Architecture

- **Library**: LedControl (by Eberhard Fahle)
- **Timing**: `millis()` based non-blocking timer system
- **Button Algorithm**: 
  - **State Change Detection**: Detecting status changes
  - **Debounce**: Mechanical bounce prevention
  - Reaction time in milliseconds instead of standard `delay()`

### Performance Optimizations

The most critical improvement of the project is the **button response time** optimization:
- Standard `delay()` commands have been completely removed.
- Non-blocking code structure with Millis-based timers.
- Prevention of double-press errors with the Debounce algorithm.
- Response time with millisecond precision.

### Hardware Adaptation

While originally planned with 4 modules, the project was successfully adapted to **3 modules** as a result of tests and hardware optimization. This flexibility was made possible by the project's modular software architecture.

## 🏗️ Project Structure

```
arduino-tower-game/
│
├── sketch_nov26a/
│   └── sketch_nov26a.ino    # Main Arduino code
│
├── diagram-image/
│   └── circuit_diagram.png   # Circuit diagram
│
└── README.md                 # Project documentation
```

## 🎓 Concepts Learned

- MAX7219 LED matris kontrolü
- SPI-like serial communication (Daisy Chain)
- Non-blocking timing techniques
- Debounce algorithms
- State machine pattern
- Real-time game development

## 🤝 Contributing

This project was developed for educational purposes. You can open a Pull Request for improvements and suggestions.

---

⭐ Don't forget to star if you like the project!

</details>

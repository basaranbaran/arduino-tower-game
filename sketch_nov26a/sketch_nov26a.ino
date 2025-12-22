/*
 * Project: Arduino Vertical Stacker Game (Ultimate Fix)
 * Fix: "State Change Detection" (Durum Değişikliği Algılama)
 * Çift basma ve başlangıç hatası tamamen giderildi.
 */

#include "LedControl.h"

// --- PIN TANIMLAMALARI ---
#define PIN_DIN 11
#define PIN_CLK 13
#define PIN_CS  10
#define PIN_BUTTON 2

#define NUM_DEVICES 3 

LedControl lc = LedControl(PIN_DIN, PIN_CLK, PIN_CS, NUM_DEVICES);

// --- OYUN DEĞİŞKENLERİ ---
unsigned long delayTime = 150; 
unsigned long lastUpdate = 0;

// --- YENİ BUTON MANTIĞI ---
int buttonState;             // Butonun şu anki kararlı hali
int lastButtonState = HIGH;  // Bir önceki turdaki hali
unsigned long lastDebounceTime = 0;  
unsigned long debounceDelay = 50;    // 50ms bekleme (titreme önleyici)

int currentLevel = 0;
int maxLevels = 24; 
int blockSize = 5; 
int blockPos = 0;
int direction = 1;

bool gameOver = false;
bool gameRunning = false; // Oyunun başladığını kontrol etmek için

byte grid[32]; 

void setup() {
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  randomSeed(analogRead(0));
  
  for (int i = 0; i < NUM_DEVICES; i++) {
    lc.shutdown(i, false);
    lc.setIntensity(i, 5);
    lc.clearDisplay(i);
  }
  
  resetGame();
}

void loop() {
  // Eğer oyun bittiyse bekle
  if (gameOver) {
    playGameOverAnimation();
    // Animasyon bitince, butonun BIRAKILMASINI bekle ve yeniden başlat
    while(digitalRead(PIN_BUTTON) == LOW); 
    delay(500); // Yanlışlıkla hemen başlamasın diye yarım saniye bekle
    resetGame();
    return;
  }

  // --- 1. BUTON KONTROLÜ (EN SAĞLAM YÖNTEM) ---
  int reading = digitalRead(PIN_BUTTON);

  // Eğer butonda bir değişiklik varsa (Basıldı veya Çekildi)
  if (reading != lastButtonState) {
    lastDebounceTime = millis(); // Sayacı sıfırla
  }

  // Eğer geçen süre 50ms'den fazlaysa (Yani bu bir titreme değil, gerçek basışsa)
  if ((millis() - lastDebounceTime) > debounceDelay) {
    
    // Butonun durumu gerçekten değişmişse
    if (reading != buttonState) {
      buttonState = reading;

      // VE buton şu an BASILI ise (LOW)
      if (buttonState == LOW) {
        handleButtonPress(); // Sadece o an 1 kere çalışır!
      }
    }
  }

  // Son durumu kaydet
  lastButtonState = reading;


  // --- 2. HAREKET ZAMANLAYICISI ---
  if (millis() - lastUpdate >= delayTime) {
    moveBlock();
    lastUpdate = millis(); 
  }
}

void handleButtonPress() {
  // Oyun bitmişse işlem yapma
  if (gameOver) return;

  if (!checkStack()) {
    gameOver = true;
  } else {
    currentLevel++;
    
    if (currentLevel >= maxLevels) {
      playWinAnimation();
      gameOver = true; // Kazanınca da oyun biter, animasyona girer
      return;
    }
    
    if (delayTime > 40) delayTime -= 4;
    
    blockPos = 0;
  }
}

void moveBlock() {
  if (gameOver) return;

  drawRow(currentLevel, 0); 
  
  blockPos += direction;
  
  if (blockPos + blockSize > 8 || blockPos < 0) {
    direction *= -1;
    blockPos += direction * 2;
  }
  
  byte rowData = 0;
  for (int i = 0; i < blockSize; i++) {
    rowData |= (1 << (blockPos + i));
  }
  
  drawRow(currentLevel, rowData);
}

bool checkStack() {
  if (currentLevel == 0) {
    byte rowData = 0;
    for (int i = 0; i < blockSize; i++) rowData |= (1 << (blockPos + i));
    grid[currentLevel] = rowData;
    return true;
  }

  byte currentRow = 0;
  for (int i = 0; i < blockSize; i++) currentRow |= (1 << (blockPos + i));
  
  byte prevRow = grid[currentLevel - 1];
  byte overlap = currentRow & prevRow; 

  if (overlap == 0) return false; 

  grid[currentLevel] = overlap;
  
  blockSize = 0;
  for (int i = 0; i < 8; i++) {
    if (bitRead(overlap, i)) blockSize++;
  }
  
  drawRow(currentLevel, grid[currentLevel]); 
  return true;
}

void drawRow(int y, byte data) {
  int deviceIndex = y / 8; 
  int rowIndex = y % 8;    
  if (deviceIndex >= NUM_DEVICES) return;
  lc.setRow(deviceIndex, rowIndex, data);
}

void resetGame() {
  // Başlamadan önce butonun BIRAKILDIĞINDAN emin ol
  // Bu satır, oyuna girer girmez yanlışlıkla basmayı engeller
  while(digitalRead(PIN_BUTTON) == LOW) { delay(10); }

  for (int i = 0; i < NUM_DEVICES; i++) lc.clearDisplay(i);
  for (int i = 0; i < 32; i++) grid[i] = 0;
  
  currentLevel = 0;
  blockSize = 5; 
  blockPos = 0;
  delayTime = 150;
  gameOver = false;
  direction = 1;
  lastUpdate = millis();
  
  // Değişkenleri sıfırla
  buttonState = HIGH;
  lastButtonState = HIGH;
}

void playGameOverAnimation() {
  for (int k = 0; k < 3; k++) {
    for (int i = 0; i < NUM_DEVICES; i++) lc.clearDisplay(i);
    delay(200); 
    for (int y = 0; y <= currentLevel; y++) drawRow(y, grid[y]);
    delay(200);
  }
}

void playWinAnimation() {
  for (int i = 0; i < NUM_DEVICES; i++) {
    for (int r = 0; r < 8; r++) {
      lc.setRow(i, r, 255);
      delay(50);
    }
  }
  delay(1000);
}
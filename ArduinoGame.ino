const int ledPins[] = {2, 3, 4, 5, 6}; // LED燈腳位
const int buttonPin = 7; // 按鈕腳位
int currentLED = 0; // 當前亮起的LED燈
bool buttonPressed = false;
int delayTime = 200; // 初始延遲時間
unsigned long lastDebounceTime = 0; // 去彈的最後時間
unsigned long debounceDelay = 50; // 去彈延遲時間
unsigned long lastLEDChangeTime = 0; // 上次LED變化的時間

void setup() {
  for (int i = 0; i < 5; i++) {
    pinMode(ledPins[i], OUTPUT); // 設定LED燈腳位為輸出
    digitalWrite(ledPins[i], LOW); // 初始化所有LED為關閉
  }
  pinMode(buttonPin, INPUT_PULLUP); // 設定按鈕腳位為輸入，並啟用內部上拉電阻
}

void loop() {
  int buttonState = digitalRead(buttonPin); // 讀取按鈕狀態
  unsigned long currentTime = millis(); // 獲取當前時間

  // 去彈處理
  if (buttonState == LOW && (currentTime - lastDebounceTime) > debounceDelay) {
    lastDebounceTime = currentTime; // 更新去彈時間
    if (!buttonPressed) {
      buttonPressed = true;
      if (currentTime - lastLEDChangeTime > delayTime) { // 非阻塞延遲
        digitalWrite(ledPins[currentLED], HIGH); // 點亮當前LED燈
        delay(50); // 短暫點亮
        digitalWrite(ledPins[currentLED], LOW); // 熄滅當前LED燈
        currentLED = (currentLED + 1) % 5; // 移動到下一個LED燈
        delayTime = max(50, delayTime - 10); // 每次按下按鈕後減少延遲時間，最小為50毫秒
        lastLEDChangeTime = currentTime; // 更新LED變化時間
      }
    }
  } else if (buttonState == HIGH) {
    buttonPressed = false; // 重置按鈕狀態
  }
}

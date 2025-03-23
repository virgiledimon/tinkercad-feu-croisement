// === Broches 74HC595 EAST ===
const int eLATCH_PIN = 3;
const int eCLOCK_PIN = 2;
const int eDATA_PIN  = 4;

// === Broches 74HC595 SOUTH ===
const int sLATCH_PIN = A4;
const int sCLOCK_PIN = A3;
const int sDATA_PIN  = A5;

// === Feu EAST ===
const int eCarGreenLed  = 7;
const int eCarOrangeLed = 6;
const int eCarRedLed    = 5;
const int ePieGreenLed  = 0;
const int ePieRedLed    = 1;

// === Feu SOUTH ===
const int sCarGreenLed  = 8;
const int sCarOrangeLed = 9;
const int sCarRedLed    = 10;
const int sPieGreenLed  = 11;
const int sPieRedLed    = 12;

// Temps des feux
const int greenTime = 60;
const int orangeTime = 5;
const int redTime = 50;

// === Chiffres 7 segments ===
byte digits[] = {
  0b00111111, // 0
  0b00000110, // 1
  0b01011011, // 2
  0b01001111, // 3
  0b01100110, // 4
  0b01101101, // 5
  0b01111101, // 6
  0b00000111, // 7
  0b01111111, // 8
  0b01101111  // 9
};

void setup() {
  // EAST
  pinMode(eCarGreenLed, OUTPUT);
  pinMode(eCarOrangeLed, OUTPUT);
  pinMode(eCarRedLed, OUTPUT);
  pinMode(ePieGreenLed, OUTPUT);
  pinMode(ePieRedLed, OUTPUT);

  // SOUTH
  pinMode(sCarGreenLed, OUTPUT);
  pinMode(sCarOrangeLed, OUTPUT);
  pinMode(sCarRedLed, OUTPUT);
  pinMode(sPieGreenLed, OUTPUT);
  pinMode(sPieRedLed, OUTPUT);

  // 595 EAST
  pinMode(eLATCH_PIN, OUTPUT);
  pinMode(eCLOCK_PIN, OUTPUT);
  pinMode(eDATA_PIN, OUTPUT);

  // 595 SOUTH
  pinMode(sLATCH_PIN, OUTPUT);
  pinMode(sCLOCK_PIN, OUTPUT);
  pinMode(sDATA_PIN, OUTPUT);
}

void loop() {
  // === PHASE 1 : EAST vert (60), SOUTH rouge (50)
  setFeu(eCarGreenLed, eCarOrangeLed, eCarRedLed, ePieGreenLed, ePieRedLed, HIGH, LOW, LOW, LOW, HIGH);
  setFeu(sCarGreenLed, sCarOrangeLed, sCarRedLed, sPieGreenLed, sPieRedLed, LOW, LOW, HIGH, HIGH, LOW);
  dualCountdown(eLATCH_PIN, eCLOCK_PIN, eDATA_PIN, greenTime, sLATCH_PIN, sCLOCK_PIN, sDATA_PIN, redTime);

  // === PHASE 2 : EAST orange (5), SOUTH rouge (5)
  setFeu(eCarGreenLed, eCarOrangeLed, eCarRedLed, ePieGreenLed, ePieRedLed, LOW, HIGH, LOW, LOW, HIGH);
  setFeu(sCarGreenLed, sCarOrangeLed, sCarRedLed, sPieGreenLed, sPieRedLed, LOW, LOW, HIGH, HIGH, LOW);
  dualCountdown(eLATCH_PIN, eCLOCK_PIN, eDATA_PIN, orangeTime, sLATCH_PIN, sCLOCK_PIN, sDATA_PIN, 0);

  // === PHASE 3 : SOUTH vert (60), EAST rouge (50)
  setFeu(eCarGreenLed, eCarOrangeLed, eCarRedLed, ePieGreenLed, ePieRedLed, LOW, LOW, HIGH, HIGH, LOW);
  setFeu(sCarGreenLed, sCarOrangeLed, sCarRedLed, sPieGreenLed, sPieRedLed, HIGH, LOW, LOW, LOW, HIGH);
  dualCountdown(sLATCH_PIN, sCLOCK_PIN, sDATA_PIN, greenTime, eLATCH_PIN, eCLOCK_PIN, eDATA_PIN, redTime);

  // === PHASE 4 : SOUTH orange (5), EAST rouge (5)
  setFeu(eCarGreenLed, eCarOrangeLed, eCarRedLed, ePieGreenLed, ePieRedLed, LOW, LOW, HIGH, HIGH, LOW);
  setFeu(sCarGreenLed, sCarOrangeLed, sCarRedLed, sPieGreenLed, sPieRedLed, LOW, HIGH, LOW, LOW, HIGH);
  dualCountdown(sLATCH_PIN, sCLOCK_PIN, sDATA_PIN, orangeTime, eLATCH_PIN, eCLOCK_PIN, eDATA_PIN, 0);
}

void dualCountdown(
  int latch1, int clock1, int data1, int time1,
  int latch2, int clock2, int data2, int time2) {

  for (int i = 0; i <= max(time1, time2); i++) {
    if (i <= time1) displayDigit(latch1, clock1, data1, time1 - i);
    if (i <= time2) displayDigit(latch2, clock2, data2, time2 - i);
    delay(1000);
  }
}

void displayDigit(int latch, int clock, int data, int value) {
  int tens = value / 10;
  int units = value % 10;

  digitalWrite(latch, LOW);
  shiftOut(data, clock, MSBFIRST, digits[units]);  // droite
  shiftOut(data, clock, MSBFIRST, digits[tens]);   // gauche
  digitalWrite(latch, HIGH);
}

// === Fonction pour allumer un feu voiture + piéton ===
void setFeu(int carG, int carO, int carR, int pieG, int pieR,
            bool gVal, bool oVal, bool rVal, bool pgVal, bool prVal) {
  digitalWrite(carG, gVal);
  digitalWrite(carO, oVal);
  digitalWrite(carR, rVal);
  digitalWrite(pieG, pgVal);
  digitalWrite(pieR, prVal);
}


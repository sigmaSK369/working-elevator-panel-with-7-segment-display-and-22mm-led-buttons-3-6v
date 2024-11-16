// Cesta: elevator_panel_no_driver/elevator_panel_no_driver.ino

// Definovanie pinov pre každý segment 7-segmentového displeja
#define SEG_A 2
#define SEG_B 3
#define SEG_C 4
#define SEG_D 5
#define SEG_E 6
#define SEG_F 7
#define SEG_G 8
#define SEG_DP 9 // Desatinná bodka (ak nepoužívate, môžete vynechať)

// Piny tlačidiel
#define BTN1 10
#define BTN2 11
#define BTN3 12

// Piny LED tlačidiel
#define LED1 13
#define LED2 A0
#define LED3 A1

int currentFloor = 1;

// Mapovanie segmentov pre čísla 0–9 (1 znamená zapnutý segment)
const byte digitMap[10][7] = {
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};

void setup() {
  // Inicializácia pinov pre 7-segmentový displej
  pinMode(SEG_A, OUTPUT);
  pinMode(SEG_B, OUTPUT);
  pinMode(SEG_C, OUTPUT);
  pinMode(SEG_D, OUTPUT);
  pinMode(SEG_E, OUTPUT);
  pinMode(SEG_F, OUTPUT);
  pinMode(SEG_G, OUTPUT);
  pinMode(SEG_DP, OUTPUT); // Ak nepoužívate, môžete ho vynechať

  // Inicializácia tlačidiel
  pinMode(BTN1, INPUT_PULLUP);
  pinMode(BTN2, INPUT_PULLUP);
  pinMode(BTN3, INPUT_PULLUP);

  // Inicializácia LED tlačidiel
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  // Vypnúť všetky LED
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);

  // Zobraziť aktuálne poschodie
  displayDigit(currentFloor);
}

void loop() {
  // Kontrola tlačidiel
  if (digitalRead(BTN1) == LOW) {
    moveToFloor(1);
  } else if (digitalRead(BTN2) == LOW) {
    moveToFloor(2);
  } else if (digitalRead(BTN3) == LOW) {
    moveToFloor(3);
  }
}

void moveToFloor(int targetFloor) {
  if (targetFloor == currentFloor) return; // Už sme na poschodí

  // Indikácia LED pre poschodie
  updateLEDs(targetFloor);

  // Simulácia prechodu medzi poschodiami
  for (int i = currentFloor; i != targetFloor; i += (targetFloor > currentFloor ? 1 : -1)) {
    displayDigit(i);
    delay(1000); // Simuluje čas medzi poschodiami
  }

  // Aktualizácia na cieľové poschodie
  currentFloor = targetFloor;
  displayDigit(currentFloor);
}

void updateLEDs(int targetFloor) {
  // Vypnúť všetky LED
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);

  // Zapnúť LED pre cieľové poschodie
  switch (targetFloor) {
    case 1:
      digitalWrite(LED1, HIGH);
      break;
    case 2:
      digitalWrite(LED2, HIGH);
      break;
    case 3:
      digitalWrite(LED3, HIGH);
      break;
  }
}

void displayDigit(int digit) {
  // Zobraziť číslo na 7-segmentovom displeji
  digitalWrite(SEG_A, digitMap[digit][0]);
  digitalWrite(SEG_B, digitMap[digit][1]);
  digitalWrite(SEG_C, digitMap[digit][2]);
  digitalWrite(SEG_D, digitMap[digit][3]);
  digitalWrite(SEG_E, digitMap[digit][4]);
  digitalWrite(SEG_F, digitMap[digit][5]);
  digitalWrite(SEG_G, digitMap[digit][6]);
  // Ak nepoužívate DP (bodku), nechajte ju vypnutú
  digitalWrite(SEG_DP, LOW);
}

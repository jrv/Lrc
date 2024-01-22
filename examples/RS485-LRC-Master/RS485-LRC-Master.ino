#include <SoftwareSerial.h> 
#include "Lrc.h"
#define DE 7

SoftwareSerial mySerial(8, 9); // RX, TX
Lrc lrc;
char buffer[64];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  mySerial.begin(38400);
  pinMode(DE, OUTPUT);
  digitalWrite(DE, LOW);
  lrc.begin();
}

char bytes[] = "0103002E0005";

void loop() {
  uint8_t LRC = lrc.get(bytes, sizeof(bytes));
  Serial.print("Sending:  ");
  Serial.print(bytes);
  Serial.print(" ");
  Serial.println(LRC, HEX);
  digitalWrite(DE, HIGH);
  mySerial.print(bytes);
  mySerial.print(LRC, HEX);
  mySerial.print("\r\n");
  digitalWrite(DE, LOW);
  int cnt = 0;
  int bcnt = 0;
  while (cnt < 200) {
    while (mySerial.available()) {
      buffer[bcnt++] = mySerial.read();
      cnt = 0;
    }
    delay(1);
    cnt++;
  }
  if (bcnt == 0) {
    Serial.println("No response received");
  } else {
    uint8_t lrc1 = lrc.Char2Int8(&buffer[bcnt-4]);
    uint8_t lrc2 = lrc.get(buffer, bcnt-4);
    for(int x=bcnt-4; x<sizeof(buffer);x++) {
        buffer[x] = 0x00;
    }
    Serial.print("Response: ");
    Serial.print(buffer);
    Serial.print(" ");
    Serial.print(lrc1, HEX);
    if (lrc1 == lrc2) {
      Serial.println(" (Lrc OK)");
      Serial.print("Values: ");
      uint16_t l = lrc.Char2Int16(&buffer[14]);
      Serial.print("L1: ");
      Serial.print(l/10.0);
      Serial.print(" Amp, L2: ");
      l = lrc.Char2Int16(&buffer[18]);
      Serial.print(l/10.0);
      Serial.print(" Amp, L3: ");
      l = lrc.Char2Int16(&buffer[22]);
      Serial.print(l/10.0);
      Serial.print(" Amp");
    } else {
      Serial.print(" (Lrc failure: ");
      Serial.println(lrc2, HEX);
      Serial.println(")");
    }
  }
  
  delay(5000);
}

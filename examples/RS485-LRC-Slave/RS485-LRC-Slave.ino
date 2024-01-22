#include <SoftwareSerial.h> 
#include "Lrc.h"
#define DE 7

SoftwareSerial mySerial(8, 9); // RX, TX
Lrc lrc;
char buffer[64];
int bcnt;
int cnt;
int pcnt;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  mySerial.begin(38400);
  pinMode(DE, OUTPUT);
  digitalWrite(DE, LOW);
  lrc.begin();
  bcnt = 0;
  cnt = 0;
  pcnt = 0;
}

char bytes[] = "01030A2EC2921500C600AC0064";
// char bytes[] = "01030A2EB29215000100010001";
void loop() {
  while (mySerial.available()) {
    buffer[bcnt++] = mySerial.read();
    cnt = 0;
  }
  delay(1);
  cnt++;
  if (cnt > 100) { // rx timeout
    if (bcnt > 0) {
      uint8_t lrc1 = lrc.Char2Int8(&buffer[bcnt-4]);
      uint8_t lrc2 = lrc.get(buffer, bcnt-4);
      for(int x=bcnt-4; x<sizeof(buffer);x++) {
        buffer[x] = 0x00;
      }
      Serial.println();
      Serial.print("Received: ");
      Serial.print(buffer);
      Serial.print(" ");
      Serial.print(lrc1, HEX);
      if (lrc1 == lrc2) {
        Serial.println(" (Lrc OK)");
      } else {
        Serial.print(" (Lrc failure: ");
        Serial.println(lrc2, HEX);
        Serial.println(")");
      }
      delay(50);
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
      bcnt = 0;
      pcnt = 0;
    }
    cnt = 0;
    pcnt++;
    Serial.print(".");
    if (pcnt > 40) {
      Serial.println();
      pcnt = 0;
    }
  }
} 

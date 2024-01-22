#include "Lrc.h"

Lrc lrc;
char buffer[64];
char lrcStr[2];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  lrc.begin();
  
}


void loop() {
  char bytes[] = "01030A2EC2921500C600AC0064";
 
  uint8_t lrc1 = lrc.get(bytes, sizeof(bytes));
  Serial.print("Original: ");
  Serial.print(bytes);
  Serial.print(" ");
  Serial.println(lrc1, HEX);
  int bcnt = 0;
  for (int x=0; x<sizeof(bytes); x++) {
    buffer[bcnt++] = bytes[x]; 
  }
  char buff[2];
  lrc.Int2Char(buff, lrc1);
  buffer[bcnt++] = buff[0];
  buffer[bcnt++] = buff[1];
  uint8_t lrc2 = lrc.Char2Int8(&buffer[bcnt-2]);
  buffer[bcnt-2] = '\r';
  buffer[bcnt-1] = '\n';
  Serial.print("Response: ");
  Serial.print(buffer);
  Serial.print(" ");
  Serial.print(lrc2, HEX);
  if (lrc1 == lrc2) {
    Serial.println(" (Lrc OK)");
  } else {
    Serial.println(" (Lrc failure)");
  }
  delay(5000);

}

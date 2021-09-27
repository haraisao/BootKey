
/*
 * Use HID-Project
 */
#include  "HID-Project.h"
#include <EEPROM.h>

#define ADDR  0x000
void setup() {
  ///// 
  int csec = 40;
  int i, n = 5;

  i = EEPROM.read(ADDR);
  if(i>0){
    csec = i;
  }else{
    EEPROM.write(ADDR, csec);
  }

  Keyboard.begin();

  delay(csec*100);
  for(i=0; i<n; ++i){
    Keyboard.write(KEY_UP_ARROW);
    delay(100);
  }
  Keyboard.write(KEY_ENTER);
  Serial.begin(9600);
}

void loop() {
  String buf;
  int size = Serial.available();
  if ( size > 1){
    buf = Serial.readStringUntil("\n");
    int csec = buf.toInt();
    if(csec > 0){
      EEPROM.write(ADDR, csec);
      csec = EEPROM.read(ADDR);
    }
    Serial.print("Set delay:");
    Serial.println(csec);
  }
  delay(3000);
}

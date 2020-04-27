 #include "AS5600_IIC.h"

void setup() {
  Serial.begin(115200);
  Serial.println("Start initing.....");
  AS5600_IIC_Init();
}

void loop() {
    long int a = millis();
    word value =  AS5600_IIC_Read_OneByte((0x36<<1),0x0e);   
    value <<= 8;
    value |= AS5600_IIC_Read_OneByte((0x36<<1),0x0f); 
    Serial.print(millis() - a);
    Serial.print("  ");
    Serial.println(value);
    delay(200);
}

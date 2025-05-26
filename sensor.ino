#include <SoftwareSerial.h>

SoftwareSerial mySerial(11, 10); // RX, TX
unsigned char data[4] = {};
float distance;
float calibrationFactor = 0.23; // turn this value higher if distance is measuring too low, lower if too high.

void setup()
{
  Serial.begin(57600);
  mySerial.begin(9600); 
}

void loop()
{
  do {
    for (int i = 0; i < 4; i++) {
      data[i] = mySerial.read();
    }
  } while (mySerial.read() == 0xff); //header, otherwise nothing

  mySerial.flush();

  if (data[0] == 0xff) ;//header 
  {
    int sum = (data[0] + data[1] + data[2]) & 0x00FF;
    if (sum == data[3])
    {
      distance = (data[1] << 8) + data[2]; // distance in mm (air)
      float distanceInWater = distance * calibrationFactor; // distance in mm (water)

      if (distanceInWater > 30) {
        Serial.print("distance = ");
        Serial.print(distanceInWater / 10); // converting mm to cm
        Serial.println(" cm (underwater)");
      } else {
        Serial.println("Below the lower limit (underwater)");
      }
    } else {
      Serial.println("ERROR");
    }
  }
  delay(100);
}
#include <SoftwareSerial.h>
#include<TinyGPS.h>
TinyGPS tGPS;
SoftwareSerial SerialGPS(4, 3);
unsigned long chars;
unsigned short sentences, failed_checksum;
void setup()
{
  Serial.begin(9600);
  Serial.println("Little buoy");
  Serial.println("v2. Utilizando tinyGPS");
  Serial.print("Testing TinyGPS library v. ");
  Serial.println(TinyGPS::library_version());
  SerialGPS.begin(9600);
}
0d
void loop()
{
  while (SerialGPS.available())
  {
    int c = SerialGPS.read();
    if (tGPS.encode(c))
    {
      // process new gps info here
      float flat, flon;
      unsigned long fix_age;
      tGPS.f_get_position(&flat, &flon);
      float falt = tGPS.f_altitude(); // +/- altitude in meters
      Serial.print("Coordenadas (DD): ");
      Serial.print(flat, 5);
      Serial.print(", ");
      Serial.print(flon, 5);
      Serial.print(" ALT:");
      Serial.print(falt, 5);
      Serial.print(" SAT:");
      Serial.println(tGPS.satellites());
    }
  }
}

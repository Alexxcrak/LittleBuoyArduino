#include <SoftwareSerial.h>
#include<TinyGPS.h>
TinyGPS tGPS;
SoftwareSerial SerialGPS(4, 3);
SoftwareSerial SerialA6(5, 6);
unsigned long chars;
bool st = 0;
void setup()
{

  Serial.begin(9600);
  Serial.println("Little buoy");
  Serial.println("Iniciando...");

  //GPS neo6mv2
  SerialGPS.begin(9600);

  //A6 mini
  SerialA6.begin(9600);
  SerialA6.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
  SerialA6.println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
  updateSerial();
  SerialA6.println("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged
  updateSerial();
  SerialA6.println("AT+CREG?"); //Check whether it has registered in the network
  updateSerial();
}

void loop() {

  if (millis() % 1000 < 0.1) {
    updateSerial();
          st = !st;
    digitalWrite(LED_BUILTIN,st);
    while (SerialGPS.available() )
    {
     
      //int c =
      Serial.write(SerialGPS.read());
      /*if (tGPS.encode(c))
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
      }*/
    }
  }

}
void updateSerial() {

  while (Serial.available())
  {
    SerialA6.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while (SerialA6.available())
  {
    Serial.write(SerialA6.read());//Forward what Software Serial received to Serial Port
  }
}

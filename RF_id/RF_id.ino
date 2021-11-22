#include <EEPROM.h>
#include <MFRC522.h>
#include <SPI.h>
 
#define SS_PIN D4
#define RST_PIN D2
#define RELAY_1 D1
 
MFRC522 rfid(SS_PIN, RST_PIN);
int F;
 
void setup() {
    Serial.begin (9600);
    SPI.begin();
    rfid.PCD_Init();
    pinMode(RELAY_1, OUTPUT);
    digitalWrite(RELAY_1, LOW);
}
 
void loop() {
    F= digitalRead(RELAY_1);
    if(F == LOW) {
     
      //Mencari Kartu Baru
      if ( ! rfid.PICC_IsNewCardPresent())
    {
    return;
    }
      //Memilih salah satu dari Kartu
      if ( ! rfid.PICC_ReadCardSerial())
    {
    return;
    }
    Serial.print("UID tag :");
    String content="";
    byte letter;
    for (byte i = 0; i < rfid.uid.size; i++)
    {
      Serial.print(rfid.uid.uidByte[i] < 0x10 ? "0" : " ");
      Serial.print(rfid.uid.uidByte[i], HEX);
      content.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
      content.concat(String(rfid.uid.uidByte[i],HEX));
    }
      Serial.println();
      Serial.print("Message : ");
      content.toUpperCase();
      if (content.substring(1) == "87 20 50 2A") //Ganti ID Di sini
      {
        Serial.println("Lampu Nyala");
        digitalWrite(RELAY_1, HIGH);
        delay (5000);
      }
    } else if (F == HIGH) {
      if ( ! rfid.PICC_ReadCardSerial()) {
        return;
      }
        Serial.print("UID tag :");
        String ID= "";
        byte letter;
        for (byte i = 0; i < rfid.uid.size; i++)
        {
      Serial.print(rfid.uid.uidByte[i] < 0x10 ? "0" : " ");
      Serial.print(rfid.uid.uidByte[i], HEX);
      ID.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
      ID.concat(String(rfid.uid.uidByte[i],HEX));
    }
      Serial.println();
      Serial.print("Message : ");
      ID.toUpperCase();
      if (ID.substring(1) == "87 20 50 2A") // Ganti ID di sini
      {
        Serial.println("Lampu Mati");
        digitalWrite(RELAY_1, LOW);
        delay (5000);
      }
    }
}

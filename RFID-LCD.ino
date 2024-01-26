#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

 int led1=6;
 int led2=7;
 
#define RST_PIN 9
#define SS_PIN 10
 
byte readCard[4];
String MasterTag = "FCF1A132";
String user1 = "D4CD7C89";
String user2 = "90567989"; 
String user3 = "E67C7889"; 
String user4 = "E9D42A8C";
String user5 = "F7D87689";// REPLACE this Tag ID with your Tag ID!!!
String tagID = "";
 
// Create instances
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() 
{
  lcd.init();
  lcd.backlight();
  SPI.begin(); // SPI bus
  mfrc522.PCD_Init(); // MFRC522
   pinMode(led1,OUTPUT);
   pinMode(led2,OUTPUT);
 
  lcd.clear();
  lcd.print("Inventory Manage");
  lcd.setCursor(0, 1);
  lcd.print("Scan Product>>");
}
 int M2Mpieces = 7;
 int LCDpieces = 9;
 int Arduino = 12;
 int M2Fpieces = 76;
 int RFID = 88;
 int RELAY = 92;
void loop() 
{
    Serial.begin(9600);
  //Wait until new tag is available
  while (getID()) 
  {
    lcd.clear();
    lcd.setCursor(0, 0);
     
    if (tagID == MasterTag || tagID == user1 || tagID == user2 || tagID == user3 || tagID == user4 || tagID == user5) 
    {
      if(tagID == MasterTag)
      {
        lcd.print("  ARDUINO UNO  ");
        lcd.setCursor(0, 1);
          if(Arduino == 0)
          {
            lcd.print("Out of Stock");
                 digitalWrite(led2,HIGH); 
       digitalWrite(led1,LOW); 
       delay(200);
          }
          else
          {
          Arduino = Arduino - 1;
        lcd.print(Arduino);
         lcd.print(" Pieces ");
         digitalWrite(led1,HIGH); 
          digitalWrite(led2,LOW);
          delay(2000);
          }
      }
      else if(tagID == user2)
      {
        lcd.print("    LCD    ");
        lcd.setCursor(0, 1);
        if(LCDpieces == 0)
        {
          lcd.print("Out of Stock");
          digitalWrite(led2,HIGH); 
       digitalWrite(led1,LOW); 
       delay(200);
        }
        else
        {
          LCDpieces = LCDpieces - 1;
        lcd.print(LCDpieces);
        lcd.print(" Pieces ");
         digitalWrite(led1,HIGH); 
          digitalWrite(led2,LOW);
          delay(2000);
           }
      }
      else if(tagID == user3)
      {
        lcd.print("Jumper Wire M2M");
        lcd.setCursor(0, 1);
        if(M2Mpieces == 0)
        {
          lcd.print(" OUT of STOCK ");
               digitalWrite(led2,HIGH); 
       digitalWrite(led1,LOW); 
       delay(200);
        }
        else
        {
        M2Mpieces = M2Mpieces - 1;
        lcd.print(M2Mpieces);
        lcd.print(" Pieces ");
         digitalWrite(led1,HIGH); 
          digitalWrite(led2,LOW);
          delay(2000);
        }
      }
      else if(tagID == user4)
      {
        lcd.print("Jumper Wire M2F");
        lcd.setCursor(0, 1);
        if(M2Fpieces == 0)
        {
             lcd.print(" OUT of STOCK ");
                  digitalWrite(led2,HIGH); 
       digitalWrite(led1,LOW); 
       delay(200);
        }
        else
        {
          M2Fpieces = M2Fpieces - 1;
        lcd.print(M2Fpieces);
        lcd.print(" Pieces ");
         digitalWrite(led1,HIGH); 
          digitalWrite(led2,LOW);
          delay(2000);
        }
      }
      else if(tagID == user5)
      {
        lcd.print("  RFID Scanner  ");
        lcd.setCursor(0, 1);
        if(RFID == 0)
        {
          lcd.print(" OUT of STOCK ");
               digitalWrite(led2,HIGH); 
       digitalWrite(led1,LOW); 
       delay(200);
        }
        else{
          RFID = RFID - 1;
        lcd.print(RFID);
        lcd.print(" Pieces");
        digitalWrite(led1,HIGH); 
        digitalWrite(led2,LOW);
        delay(2000);
        }
      }
      else
      {
          lcd.print("    Relay    ");
          lcd.setCursor(0, 1);
          if(RELAY == 0)
          {
            lcd.print(" OUT of STOCK ");
                   digitalWrite(led2,HIGH); 
       digitalWrite(led1,LOW); 
       delay(200);
          }
          else
          {

          RELAY = RELAY - 1;
          lcd.print(RELAY);
        lcd.print(" Pieces");
       digitalWrite(led1,HIGH); 
       digitalWrite(led2,LOW);
       delay(2000);
          }
      // You can write any code here like opening doors, switching on a relay, lighting up an LED, or anything else you can think of.
      }
      
    }
    else
    {
       digitalWrite(led2,HIGH); 
       digitalWrite(led1,LOW);  
      lcd.print(" UNAVAIlable!");
       delay(2000);
    }
     
      // lcd.setCursor(0, 1);
      // lcd.print(" ID : ");
      // lcd.print(tagID);
       
 
     digitalWrite(led2,LOW); 
     digitalWrite(led1,LOW);
    lcd.clear();
    lcd.print("Inventory Manage");
    lcd.setCursor(0, 1);
    lcd.print("Scan Product>>");
  }
}
 
//Read new tag if available
boolean getID() 
{
  // Getting ready for Reading PICCs
  if ( ! mfrc522.PICC_IsNewCardPresent()) { //If a new PICC placed to RFID reader continue
  return false;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) { //Since a PICC placed get Serial and continue
  return false;
  }
  tagID = "";
  for ( uint8_t i = 0; i < 4; i++) { // The MIFARE PICCs that we use have 4 byte UID
  //readCard[i] = mfrc522.uid.uidByte[i];
  tagID.concat(String(mfrc522.uid.uidByte[i], HEX)); // Adds the 4 bytes in a single String variable
  }
  tagID.toUpperCase();
  mfrc522.PICC_HaltA(); // Stop reading
  return true;
}

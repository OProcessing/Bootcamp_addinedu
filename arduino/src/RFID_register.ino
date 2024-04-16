/*
 * --------------------------------------------------------------------------------------------------------------------
 * Example sketch/program showing how to read data from a PICC to serial.
 * --------------------------------------------------------------------------------------------------------------------
 * This is a MFRC522 library example; for further details and other examples see: https://github.com/miguelbalboa/rfid
 * 
 * Example sketch/program showing how to read data from a PICC (that is: a RFID Tag or Card) using a MFRC522 based RFID
 * Reader on the Arduino SPI interface.
 * 
 * When the Arduino and the MFRC522 module are connected (see the pin layout below), load this sketch into Arduino IDE
 * then verify/compile and upload it. To see the output: use Tools, Serial Monitor of the IDE (hit Ctrl+Shft+M). When
 * you present a PICC (that is: a RFID Tag or Card) at reading distance of the MFRC522 Reader/PCD, the serial output
 * will show the ID/UID, type and any data blocks it can read. Note: you may see "Timeout in communication" messages
 * when removing the PICC from reading distance too early.
 * 
 * If your reader supports it, this sketch/program will read all the PICCs presented (that is: multiple tag reading).
 * So if you stack two or more PICCs on top of each other and present them to the reader, it will first output all
 * details of the first and then the next PICC. Note that this may take some time as all data blocks are dumped, so
 * keep the PICCs at reading distance until complete.
 * 
 * @license Released into the public domain.
 * 
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 *
 * More pin layouts for other boards can be found here: https://github.com/miguelbalboa/rfid#pin-layout
 */

#include <SPI.h>
#include <MFRC522.h>
#include <List.hpp>

#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above

List<MFRC522::Uid> tag_list;
// const byte MY_TAG[4] = {0xC3, 0xA3, 0xD5, 0x0F};
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
const int R = 4;
const int G = 3;
const int B = 2;
int color;
int count = 0;
bool led_state = false;
bool registered = false;

int status;
void LED (bool r, bool g, bool b) ;

void setup() {
	Serial.begin(9600);		// Initialize serial communications with the PC
	while (!Serial);		// Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
	SPI.begin();			// Init SPI bus
	mfrc522.PCD_Init();		// Init MFRC522
	delay(4);				// Optional delay. Some board do need more time after init to be ready, see Readme
	mfrc522.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details
	Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));

  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(2, INPUT);
}

void loop() {
	// Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
	if ( ! mfrc522.PICC_IsNewCardPresent()) {
    if (count > 0) {
      if (count % 15 == 0) {
        led_state = !led_state;
        digitalWrite(color, led_state);
      }
      count --;
      delay(1);
    }
    else {
      digitalWrite(R, HIGH);
      digitalWrite(G, HIGH);
      digitalWrite(B, HIGH);
      
    }
		return;
  }
	// Select one of the cards
	if ( ! mfrc522.PICC_ReadCardSerial()) {
		return;
	}

  // Read UID
  digitalWrite(R, LOW);
  digitalWrite(G, LOW);
  digitalWrite(B, LOW);
  Serial.print("Read UID Tag : ");
  for ( byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
  }
  Serial.println();

  // status in Register
    // Register
  registered = false;
  for (int i = 0; i < tag_list.getSize(); i++) {
    if (memcmp(tag_list.get(i).uidByte, mfrc522.uid.uidByte, 4) == 0) {
      registered = true;
    }
  }
  status = digitalRead(2);
  if (status) { // register
    if (!registered) {
      color = B;
      tag_list.addLast(mfrc522.uid);
    }
    else {
      color = R;
    }
    count = 75;
    led_state = 1;
    digitalWrite(color, led_state);
  }
  else {  //verification
    Serial.print(", Check UID Tag : ");
    if (registered) {
      Serial.print("Valid");
    }
    else {
      Serial.print("Invalid");
    }
    Serial.println();
  }

  // Print Tag List
  Serial.print("Registered Tag List (");
  Serial.print(tag_list.getSize());
  Serial.print(") :");
  Serial.println();
 
  for (int i = 0; i < tag_list.getSize(); i++) {
    for (byte j = 0; j < 4; j++) {
      Serial.print(tag_list.get(i).uidByte[j] < 0x10 ? " 0" : " ");
      Serial.print(tag_list.get(i).uidByte[j], HEX);
    }
    Serial.println();
  }
  delay(500);
}
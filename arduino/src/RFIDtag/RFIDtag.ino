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

#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above

struct TagData
{
  char name[16];
  long total;
  long payment;
};

MFRC522 rc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

MFRC522::StatusCode checkAuth(int index, MFRC522::MIFARE_Key key)
{
  MFRC522::StatusCode status = rc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, index, &key, &(rc522.uid));

  if (status != MFRC522::STATUS_OK)
  {
    Serial.print("Authentication Failed : ");
    Serial.println(rc522.GetStatusCodeName(status));
  }
  return status;
}

MFRC522::StatusCode writeString (int index, MFRC522::MIFARE_Key key, String data)
{
  MFRC522::StatusCode status = checkAuth(index, key);
  if (status != MFRC522::STATUS_OK)
  {
    return status;
  }
  
  char buffer[16];
  memset(buffer, 0x00, sizeof(buffer));
  data.toCharArray(buffer, data.length() + 1);

  status = rc522.MIFARE_Write(index, (byte*)&buffer, 16);
  if (status != MFRC522::STATUS_OK)
  {
    Serial.print("Write Failed : ");
    Serial.println(rc522.GetStatusCodeName(status));
  }
  return status;
}

MFRC522::StatusCode readString(int index, MFRC522::MIFARE_Key key, String &data)
{
  MFRC522::StatusCode status = checkAuth(index, key);
  if (status != MFRC522::STATUS_OK)
  {
    return status;
  }

  byte buffer[18];
  byte length = 18;

  status = rc522.MIFARE_Read(index, buffer, &length);
  if (status != MFRC522::STATUS_OK)
  {
    Serial.print("Read Failed : ");
    Serial.println(rc522.GetStatusCodeName(status));
  }
  else
  {
    data = String((char*)buffer);
  }
  return status;
}

void toBytes(byte* buffer, int data, int offset = 0);
int toInteger(byte* buffer, int offset = 0);

MFRC522::StatusCode writeInteger(int index, MFRC522::MIFARE_Key key, int data)
{
  MFRC522::StatusCode status = checkAuth(index, key);
  if (status != MFRC522::STATUS_OK)
  {
    return status;
  }
  byte buffer[16];
  memset(buffer, 0x00, sizeof(buffer));
  toBytes(buffer, data);

  status = rc522.MIFARE_Write(index, buffer, sizeof(buffer));
  if (status != MFRC522::STATUS_OK)
  {
    Serial.print("Write Failed : ");
    Serial.println(rc522.GetStatusCodeName(status));
  }
  return status;
}
MFRC522::StatusCode readInteger(int index, MFRC522::MIFARE_Key key, int& data)
{
  MFRC522::StatusCode status = checkAuth(index, key);
  if (status != MFRC522::STATUS_OK)
  {
    return status;
  }
  byte buffer[18];
  byte length = 18;

  status = rc522.MIFARE_Read(index, buffer, &length);
  if (status != MFRC522::STATUS_OK)
  {
    Serial.print("Read Failed : ");
    Serial.println(rc522.GetStatusCodeName(status));
  }
  else
  {
    data = toInteger(buffer);
  }
  return status;
}

MFRC522::StatusCode writeTagData(int index, MFRC522::MIFARE_Key key, TagData data)
{
  MFRC522::StatusCode status = checkAuth(index, key);
  if (status != MFRC522::STATUS_OK)
  {
    return status;
  }

  byte buffer[32];
  memset(buffer, 0x00, sizeof(buffer));
  memcpy(buffer, &data, sizeof(data));

  for (int i = 0; i < 2; i ++)
  {
    status = rc522.MIFARE_Write(index + i, buffer + (i * 16), 16);
    if (status != MFRC522::STATUS_OK)
    {
      Serial.print("Write Failed : ");
      Serial.println(rc522.GetStatusCodeName(status));
    }
  }
  return status;
}

MFRC522::StatusCode readTagData(int index, MFRC522::MIFARE_Key key, TagData& data)
{
  MFRC522::StatusCode status = checkAuth(index, key);
  if (status != MFRC522::STATUS_OK)
  {
    return status;
  }

  byte buffer[34];
  byte length = 18;

  for (int i = 0; i < 2; i ++)
  {
    status = rc522.MIFARE_Write(index + i, buffer + (i * 16), &length);
    if (status != MFRC522::STATUS_OK)
    {
      Serial.print("Read Failed : ");
      Serial.println(rc522.GetStatusCodeName(status));
    }
  }
  memcpy(&data, buffer, sizeof(data));
  return status;
}

void setup() {
	Serial.begin(9600);		// Initialize serial communications with the PC
	SPI.begin();			// Init SPI bus
	rc522.PCD_Init();		// Init MFRC522
  Serial.println();
	Serial.println("start!");
}

void loop() {

  String cmd = "";
  while(Serial.available() > 0)
  {
    cmd = Serial.readStringUntil('\n');
  }
  if (!rc522.PICC_IsNewCardPresent()) {
    return;
  }
  const int index = 60;

  MFRC522::MIFARE_Key key;
  for (int i = 0; i < 6; i++)
  {
    key.keyByte[i] = 0xFF;
  }

  MFRC522::StatusCode status;
  String s_data;
  int i_data;
  TagData t_data;
  String s_temp;

  if (cmd.length() > 0)
  {
    Serial.print("cmd : ");
    switch(cmd.charAt(0))
    {
      case 'w' :
        Serial.println("write");
        switch (cmd.charAt(1))
        {
          case 's' :
            Serial.println("String");
            status = writeString(60, key, "nomaefg");
            break;
          case 'i' :
            Serial.println("integer");
            status = writeInteger(61, key, 32767);
            rc522.PICC_DumpToSerial(&(rc522.uid));
            break;
          case 't' :
            Serial.println("struct");
            s_temp = "nomaefg";
            s_temp.toCharArray(t_data.name, s_temp.length() + 1);
            t_data.total = 2147483647;
            t_data.payment = 2000000000;
            status = writeTagData(56, key, t_data);
            rc522.PICC_DumpToSerial(&(rc522.uid));
            break;
          default :
            Serial.println("unknown type");
            status = MFRC522::STATUS_ERROR;
            break;
        }
        break;
      case 'r' :
        Serial.print("read ");
        switch (cmd.charAt(1))
        {
          case 's' :
            Serial.println("String");
            status = readString(60, key, s_data);
            Serial.print(s_data);
            break;
          case 'i' :
            Serial.println("integer");
            status = readInteger(61, key, i_data);
            Serial.print(i_data);
            break;
          case 't' :
            Serial.println("struct");
            status = writeTagData(56, key, t_data);
            Serial.print(" name : "); Serial.println(String(t_data.name));
            Serial.print(" total : "); Serial.println(String(t_data.total));
            Serial.print(" payment : "); Serial.println(String(t_data.payment));
            break;
          default :
            Serial.println("unknown type");
            status = MFRC522::STATUS_ERROR;
            break;
        }
        break;
      default :
        Serial.println("unknown");
        status = MFRC522::STATUS_ERROR;
        break;
    }

    if (status == MFRC522::STATUS_OK)
    {
      Serial.println("success!");
    }
  }
}

void toBytes(byte* buffer, int data, int offset = 0)
{
  buffer[offset] = data & 0xFF;
  buffer[offset + 1] = (data >> 8) & 0xFF;
}

int toInteger(byte* buffer, int offset = 0)
{
  return(buffer[offset + 1] << 8 | buffer[offset]);
}

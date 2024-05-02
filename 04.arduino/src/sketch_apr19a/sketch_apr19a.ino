#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above

struct TagData
{
  long id;                         // 4
  char obj_name[12];               // 12

  char from[12];                   // 12
  long from_num;                   // 4

  char from_address[16];           // 16
  
  char to[12];                     // 12
  long to_num;                     // 4

  char to_address[16];             // 16

  long current_state;              // 4
};

MFRC522 rc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
MFRC522::StatusCode checkAuth(int index, MFRC522::MIFARE_Key key);
MFRC522::StatusCode writeTagData(int index, MFRC522::MIFARE_Key key, TagData data);
MFRC522::StatusCode readTagData(int index, MFRC522::MIFARE_Key key, TagData& data);

void setup() {
	Serial.begin(9600);		// Initialize serial communications with the PC
	SPI.begin();			// Init SPI bus
	rc522.PCD_Init();		// Init MFRC522
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
    switch(cmd.charAt(0))
    {
      case 'w' :
        t_data.id = 0002;
        s_temp = "strawberry";
        s_temp.toCharArray(t_data.obj_name, s_temp.length() + 1);
        s_temp = "mingimingi";
        s_temp.toCharArray(t_data.from, s_temp.length() + 1);
        t_data.from_num = 1234567890;
        s_temp = "SeoulSeocho";
        s_temp.toCharArray(t_data.from_address, s_temp.length() + 1);
        s_temp = "mingyeong";
        s_temp.toCharArray(t_data.to, s_temp.length() + 1);
        t_data.to_num = 1012345678;
        s_temp = "CheonanDujeong";
        s_temp.toCharArray(t_data.to_address, s_temp.length() + 1);
        t_data.current_state = 5;
        status = writeTagData(48, key, t_data);
        break;
      case 'r' :
        status = readTagData(48, key, t_data);
        Serial.println(String(t_data.id));     
        Serial.println(String(t_data.obj_name));
        Serial.println("From");
        Serial.println(String(t_data.from));
        Serial.println(String(t_data.from_num));
        Serial.println(String(t_data.from_address));
        Serial.println("To");
        Serial.println(String(t_data.to));        
        Serial.println(String(t_data.to_num));
        Serial.println(String(t_data.to_address));
        Serial.println(String(t_data.current_state));
        break;
      default :
        Serial.println("unknown");
        delay(100);
        status = MFRC522::STATUS_ERROR;
        break;
    }

    if (status == MFRC522::STATUS_OK)
    {
      Serial.println("success!");
    }
  }
}

MFRC522::StatusCode checkAuth(int index, MFRC522::MIFARE_Key key)
{
  MFRC522::StatusCode status = rc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, index, &key, &(rc522.uid));

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
    status = rc522.MIFARE_Read(index + i, buffer + (i * 16), &length);
  }
  memcpy(&data, buffer, sizeof(data));
  return status;
}
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above

struct TagData
{
  long id;                         // 4
  char obj_name[12];               // 12

  // char from[12];                   // 12
  // long from_num;                   // 4

  // char from_address[16];           // 16
  
  // char to[12];                     // 12
  // long to_num;                     // 4

  // char to_address[16];             // 16

  // long current_state;              // 4
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
void toBytes(byte* buffer, int data, int offset = 0)
{
  buffer[offset] = data & 0xFF;
  buffer[offset + 1] = (data >> 8) & 0xFF;
}
int toInteger(byte* buffer, int offset = 0)
{
  return(buffer[offset + 1] << 8 | buffer[offset]);
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
    status = rc522.MIFARE_Read(index + i, buffer + (i * 16), &length);
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
  cmd = 'r';
  if (cmd.length() > 0)
  {
    Serial.print("cmd : ");
    switch(cmd.charAt(0))
    {
      case 'w' :
        t_data.id = 0002;
        s_temp = "strawberry";
        s_temp.toCharArray(t_data.obj_name, s_temp.length() + 1);
        
        // s_temp = "kwakmingi";
        // s_temp.toCharArray(t_data.from, s_temp.length() + 1);
        // t_data.from_num = 1098765432;

        // s_temp = "seoulteheranro";
        // s_temp.toCharArray(t_data.from_address, s_temp.length() + 1);

        // s_temp = "kimmingyeon";
        // s_temp.toCharArray(t_data.to, s_temp.length() + 1);
        // t_data.to_num = 1012345678;

        // s_temp = "cheonandujeong";
        // s_temp.toCharArray(t_data.to_address, s_temp.length() + 1);
        // t_data.current_state = 5;

        status = writeTagData(48, key, t_data);
        break;
      case 'r' :
        status = readTagData(48, key, t_data);
        //Serial.print(" id : "); 
        Serial.print("GG");
        //Serial.println(String(t_data.id));
        //Serial.print(" name : "); 
        Serial.println(String(t_data.obj_name));

        // Serial.print(" from_ : "); 
        // Serial.println(String(t_data.from));
        // Serial.print(" from_num : "); 
        // Serial.println(String(t_data.from_num));
        // Serial.print(" from_add : "); 
        // Serial.println(String(t_data.from_address));

        // Serial.print(" to_ : "); 
        // Serial.println(String(t_data.to));
        // Serial.print(" to_num : "); 
        // Serial.println(String(t_data.to_num));
        // Serial.print(" to_add : "); 
        // Serial.println(String(t_data.to_address));

        // Serial.print(" state : "); 
        // Serial.println(String(t_data.current_state)
        break;
      default :
        //Serial.println("unknown");
        status = MFRC522::STATUS_ERROR;
        break;
    }

    if (status == MFRC522::STATUS_OK)
    {
      //Serial.println("success!");
    }
  }
}


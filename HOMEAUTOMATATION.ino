String Name = "room";
int ID = 1;

#define BLYNK_TEMPLATE_ID "TEMPLATE_ID"
#define BLYNK_DEVICE_NAME "DEVICE_NAME"
#define BLYNK_AUTH_TOKEN "AUTH TOKEN";
char ssid[] = "WIFI NAME";
char pass[] = "WIFI PASSWORD";
char auth[] = BLYNK_AUTH_TOKEN;
#define NUM_SWITHC  6 //NUMBER OF INPUT
#define NUM_MODULE 2  //NUMBER OF RELAY BOARD
#define Debug_print true //CHANGE TO true FOR SERIAL PRINT
#define BMP_280 true    //CHAHGE TO false IF USING BMP180 SENSOR
#define CURRENT_SENSOR true //CHANGE TO FALSE IF NO CURRENT TRANSFORMER

//======================================LIBRARY==============================//

#include <FastLED.h>
#include <ESP8266WiFi.h>
#include <ESP8266Ping.h>
#define BLYNK_PRINT Serial
bool wifi_available_status = false;
bool internet_available_status = false;
const char* remote_ip = "www.google.com"; // Remote host to ping
WiFiClient espClient;
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <EEPROM.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_BMP085.h>
#include "addrOutput.h"
#include "EmonLib.h"
#define BLYNK_USE_128_VPINS true


long int Wifi_Reconnect_Timer = millis();
long int Net_Reconnect_Timer = millis();
BlynkTimer timer;

#define FASTLED_ESP8266_NODEMCU_PIN_ORDER
#define DATA_PIN  5
int load = D0;
int clockEnablePin = D8;
int dataIn = D6;
int clockIn = D7;
int Current_Input_Switch[100];
int Pervious_Input_Switch[100];
int Num_74HC165;
bool intial_data = 0;
CRGB module[NUM_MODULE];
addrOut out(module, NUM_MODULE);
unsigned long lastTime = 0;
unsigned long timerDelay = 1000;  // send SENSOR readings timer
bool sensor_available = false;
Adafruit_BMP085 bmp180;
Adafruit_BMP280 bmp280;
EnergyMonitor emon1;

//===============================DATA VARIABLE=================================//
typedef struct message_transfer {
  String Name;
  int ID;
  int Switch_Count;
  bool S[100];
  double AMP;
  float temperature;
  float pressure;
} message_transfer;

message_transfer DataTX;


//=====================================VIRTUAL PIN READ ============================================//
BLYNK_WRITE(V0)
{
  DataTX.S[0] = param.asInt();
}

BLYNK_WRITE(V1)
{
  DataTX.S[1] = param.asInt();
}

BLYNK_WRITE(V2)
{
  DataTX.S[2] = param.asInt();
}
BLYNK_WRITE(V3)
{
  DataTX.S[3] = param.asInt();
}

BLYNK_WRITE(V4)
{
  DataTX.S[4] = param.asInt();
}
BLYNK_WRITE(V5)
{
  DataTX.S[5] = param.asInt();
}

BLYNK_WRITE(V6)
{
  DataTX.S[6] = param.asInt();
}

BLYNK_WRITE(V7)
{
  DataTX.S[7] = param.asInt();
}

BLYNK_WRITE(V8)
{
  DataTX.S[8] = param.asInt();
}

BLYNK_WRITE(V9)
{
  DataTX.S[9] = param.asInt();
}

BLYNK_WRITE(V10)
{
  DataTX.S[10] = param.asInt();
}

BLYNK_WRITE(V11)
{
  DataTX.S[11] = param.asInt();
}

BLYNK_WRITE(V12)
{
  DataTX.S[12] = param.asInt();
}
BLYNK_WRITE(V13)
{
  DataTX.S[13] = param.asInt();
}

BLYNK_WRITE(V14)
{
  DataTX.S[14] = param.asInt();
}
BLYNK_WRITE(V15)
{
  DataTX.S[15] = param.asInt();
}

BLYNK_WRITE(V16)
{
  DataTX.S[16] = param.asInt();
}

BLYNK_WRITE(V17)
{
  DataTX.S[17] = param.asInt();
}

BLYNK_WRITE(V18)
{
  DataTX.S[18] = param.asInt();
}

BLYNK_WRITE(V19)
{
  DataTX.S[19] = param.asInt();
}

BLYNK_WRITE(V20)
{
  DataTX.S[20] = param.asInt();
}

BLYNK_WRITE(V21)
{
  DataTX.S[21] = param.asInt();
}

BLYNK_WRITE(V22)
{
  DataTX.S[22] = param.asInt();
}
BLYNK_WRITE(V23)
{
  DataTX.S[23] = param.asInt();
}

BLYNK_WRITE(V24)
{
  DataTX.S[24] = param.asInt();
}

BLYNK_WRITE(V25)
{
  DataTX.S[25] = param.asInt();
}

BLYNK_WRITE(V26)
{
  DataTX.S[26] = param.asInt();
}

BLYNK_WRITE(V27)
{
  DataTX.S[27] = param.asInt();
}

BLYNK_WRITE(V28)
{
  DataTX.S[28] = param.asInt();
}

BLYNK_WRITE(V29)
{
  DataTX.S[29] = param.asInt();
}

BLYNK_WRITE(V30)
{
  DataTX.S[30] = param.asInt();
}

BLYNK_WRITE(V31)
{
  DataTX.S[31] = param.asInt();
}

BLYNK_WRITE(V32)
{
  DataTX.S[32] = param.asInt();
}
BLYNK_WRITE(V33)
{
  DataTX.S[33] = param.asInt();
}

BLYNK_WRITE(V34)
{
  DataTX.S[34] = param.asInt();
}
BLYNK_WRITE(V35)
{
  DataTX.S[35] = param.asInt();
}

BLYNK_WRITE(V36)
{
  DataTX.S[36] = param.asInt();
}

BLYNK_WRITE(V37)
{
  DataTX.S[37] = param.asInt();
}

BLYNK_WRITE(V38)
{
  DataTX.S[38] = param.asInt();
}

BLYNK_WRITE(V39)
{
  DataTX.S[39] = param.asInt();
}

BLYNK_WRITE(V40)
{
  DataTX.S[40] = param.asInt();
}

BLYNK_WRITE(V41)
{
  DataTX.S[41] = param.asInt();
}

BLYNK_WRITE(V42)
{
  DataTX.S[42] = param.asInt();
}
BLYNK_WRITE(V43)
{
  DataTX.S[43] = param.asInt();
}

BLYNK_WRITE(V44)
{
  DataTX.S[44] = param.asInt();
}
BLYNK_WRITE(V45)
{
  DataTX.S[45] = param.asInt();
}

BLYNK_WRITE(V46)
{
  DataTX.S[46] = param.asInt();
}

BLYNK_WRITE(V47)
{
  DataTX.S[47] = param.asInt();
}

BLYNK_WRITE(V48)
{
  DataTX.S[48] = param.asInt();
}

BLYNK_WRITE(V49)
{
  DataTX.S[49] = param.asInt();
}

BLYNK_WRITE(V50)
{
  DataTX.S[50] = param.asInt();
}

BLYNK_WRITE(V51)
{
  DataTX.S[51] = param.asInt();
}

BLYNK_WRITE(V52)
{
  DataTX.S[52] = param.asInt();
}
BLYNK_WRITE(V53)
{
  DataTX.S[53] = param.asInt();
}

BLYNK_WRITE(V54)
{
  DataTX.S[54] = param.asInt();
}
BLYNK_WRITE(V55)
{
  DataTX.S[55] = param.asInt();
}

BLYNK_WRITE(V56)
{
  DataTX.S[56] = param.asInt();
}

BLYNK_WRITE(V57)
{
  DataTX.S[57] = param.asInt();
}

BLYNK_WRITE(V58)
{
  DataTX.S[58] = param.asInt();
}

BLYNK_WRITE(V59)
{
  DataTX.S[59] = param.asInt();
}

BLYNK_WRITE(V60)
{
  DataTX.S[60] = param.asInt();
}

BLYNK_WRITE(V61)
{
  DataTX.S[61] = param.asInt();
}

BLYNK_WRITE(V62)
{
  DataTX.S[62] = param.asInt();
}
BLYNK_WRITE(V63)
{
  DataTX.S[63] = param.asInt();
}

BLYNK_WRITE(V64)
{
  DataTX.S[64] = param.asInt();
}
BLYNK_WRITE(V65)
{
  DataTX.S[65] = param.asInt();
}

BLYNK_WRITE(V66)
{
  DataTX.S[66] = param.asInt();
}

BLYNK_WRITE(V67)
{
  DataTX.S[67] = param.asInt();
}

BLYNK_WRITE(V68)
{
  DataTX.S[68] = param.asInt();
}

BLYNK_WRITE(V69)
{
  DataTX.S[69] = param.asInt();
}

BLYNK_WRITE(V70)
{
  DataTX.S[70] = param.asInt();
}

BLYNK_WRITE(V71)
{
  DataTX.S[71] = param.asInt();
}

BLYNK_WRITE(V72)
{
  DataTX.S[72] = param.asInt();
}
BLYNK_WRITE(V73)
{
  DataTX.S[73] = param.asInt();
}

BLYNK_WRITE(V74)
{
  DataTX.S[74] = param.asInt();
}
BLYNK_WRITE(V75)
{
  DataTX.S[75] = param.asInt();
}

BLYNK_WRITE(V76)
{
  DataTX.S[76] = param.asInt();
}

BLYNK_WRITE(V77)
{
  DataTX.S[77] = param.asInt();
}

BLYNK_WRITE(V78)
{
  DataTX.S[78] = param.asInt();
}

BLYNK_WRITE(V79)
{
  DataTX.S[79] = param.asInt();
}

BLYNK_WRITE(V80)
{
  DataTX.S[80] = param.asInt();
}

BLYNK_WRITE(V81)
{
  DataTX.S[81] = param.asInt();
}

BLYNK_WRITE(V82)
{
  DataTX.S[82] = param.asInt();
}
BLYNK_WRITE(V83)
{
  DataTX.S[83] = param.asInt();
}

BLYNK_WRITE(V84)
{
  DataTX.S[84] = param.asInt();
}
BLYNK_WRITE(V85)
{
  DataTX.S[85] = param.asInt();
}

BLYNK_WRITE(V86)
{
  DataTX.S[86] = param.asInt();
}

BLYNK_WRITE(V87)
{
  DataTX.S[87] = param.asInt();
}

BLYNK_WRITE(V88)
{
  DataTX.S[88] = param.asInt();
}

BLYNK_WRITE(V89)
{
  DataTX.S[89] = param.asInt();
}

BLYNK_WRITE(V90)
{
  DataTX.S[90] = param.asInt();
}

BLYNK_WRITE(V91)
{
  DataTX.S[91] = param.asInt();
}

BLYNK_WRITE(V92)
{
  DataTX.S[92] = param.asInt();
}
BLYNK_WRITE(V93)
{
  DataTX.S[93] = param.asInt();
}

BLYNK_WRITE(V94)
{
  DataTX.S[94] = param.asInt();
}
BLYNK_WRITE(V95)
{
  DataTX.S[95] = param.asInt();
}

BLYNK_WRITE(V96)
{
  DataTX.S[96] = param.asInt();
}

BLYNK_WRITE(V97)
{
  DataTX.S[97] = param.asInt();
}

BLYNK_WRITE(V98)
{
  DataTX.S[98] = param.asInt();
}

BLYNK_WRITE(V99)
{
  DataTX.S[99] = param.asInt();
}


//==================================VIRTUAL PIN WRITE===================================//
void Data_CLOUD_write(int i)
{
  switch (i)
  {
    case 0:
      Blynk.virtualWrite(V0, DataTX.S[0]);
      break;
    case 1:
      Blynk.virtualWrite(V1, DataTX.S[1]);
      break;
    case 2:
      Blynk.virtualWrite(V2, DataTX.S[2]);
      break;
    case 3:
      Blynk.virtualWrite(V3, DataTX.S[3]);
      break;
    case 4:
      Blynk.virtualWrite(V4, DataTX.S[4]);
      break;
    case 5:
      Blynk.virtualWrite(V5, DataTX.S[5]);
      break;
    case 6:
      Blynk.virtualWrite(V6, DataTX.S[6]);
      break;
    case 7:
      Blynk.virtualWrite(V7, DataTX.S[7]);
      break;
    case 8:
      Blynk.virtualWrite(V8, DataTX.S[8]);
      break;
    case 9:
      Blynk.virtualWrite(V9, DataTX.S[9]);
      break;
    case 10:
      Blynk.virtualWrite(V10, DataTX.S[10]);
      break;
    case 11:
      Blynk.virtualWrite(V11, DataTX.S[11]);
      break;
    case 12:
      Blynk.virtualWrite(V12, DataTX.S[12]);
      break;
    case 13:
      Blynk.virtualWrite(V13, DataTX.S[13]);
      break;
    case 14:
      Blynk.virtualWrite(V14, DataTX.S[14]);
      break;
    case 15:
      Blynk.virtualWrite(V15, DataTX.S[15]);
      break;
    case 16:
      Blynk.virtualWrite(V16, DataTX.S[16]);
      break;
    case 17:
      Blynk.virtualWrite(V17, DataTX.S[17]);
      break;
    case 18:
      Blynk.virtualWrite(V18, DataTX.S[18]);
      break;
    case 19:
      Blynk.virtualWrite(V19, DataTX.S[19]);
      break;
    case 20:
      Blynk.virtualWrite(V20, DataTX.S[20]);
      break;
    case 21:
      Blynk.virtualWrite(V21, DataTX.S[21]);
      break;
    case 22:
      Blynk.virtualWrite(V22, DataTX.S[22]);
      break;
    case 23:
      Blynk.virtualWrite(V23, DataTX.S[23]);
      break;
    case 24:
      Blynk.virtualWrite(V24, DataTX.S[24]);
      break;
    case 25:
      Blynk.virtualWrite(V25, DataTX.S[25]);
      break;
    case 26:
      Blynk.virtualWrite(V26, DataTX.S[26]);
      break;
    case 27:
      Blynk.virtualWrite(V27, DataTX.S[27]);
      break;
    case 28:
      Blynk.virtualWrite(V28, DataTX.S[28]);
      break;
    case 29:
      Blynk.virtualWrite(V29, DataTX.S[29]);
      break;
    case 30:
      Blynk.virtualWrite(V30, DataTX.S[30]);
      break;
    case 31:
      Blynk.virtualWrite(V31, DataTX.S[31]);
      break;
    case 32:
      Blynk.virtualWrite(V32, DataTX.S[32]);
      break;
    case 33:
      Blynk.virtualWrite(V33, DataTX.S[33]);
      break;
    case 34:
      Blynk.virtualWrite(V34, DataTX.S[34]);
      break;
    case 35:
      Blynk.virtualWrite(V35, DataTX.S[35]);
      break;
    case 36:
      Blynk.virtualWrite(V36, DataTX.S[36]);
      break;
    case 37:
      Blynk.virtualWrite(V37, DataTX.S[37]);
      break;
    case 38:
      Blynk.virtualWrite(V38, DataTX.S[38]);
      break;
    case 39:
      Blynk.virtualWrite(V39, DataTX.S[39]);
      break;
    case 40:
      Blynk.virtualWrite(V40, DataTX.S[40]);
      break;
    case 41:
      Blynk.virtualWrite(V41, DataTX.S[41]);
      break;
    case 42:
      Blynk.virtualWrite(V42, DataTX.S[42]);
      break;
    case 43:
      Blynk.virtualWrite(V43, DataTX.S[43]);
      break;
    case 44:
      Blynk.virtualWrite(V44, DataTX.S[44]);
      break;
    case 45:
      Blynk.virtualWrite(V45, DataTX.S[45]);
      break;
    case 46:
      Blynk.virtualWrite(V46, DataTX.S[46]);
      break;
    case 47:
      Blynk.virtualWrite(V47, DataTX.S[47]);
      break;
    case 48:
      Blynk.virtualWrite(V48, DataTX.S[48]);
      break;
    case 49:
      Blynk.virtualWrite(V49, DataTX.S[49]);
      break;
    case 50:
      Blynk.virtualWrite(V50, DataTX.S[50]);
      break;
    case 51:
      Blynk.virtualWrite(V51, DataTX.S[51]);
      break;
    case 52:
      Blynk.virtualWrite(V52, DataTX.S[52]);
      break;
    case 53:
      Blynk.virtualWrite(V53, DataTX.S[53]);
      break;
    case 54:
      Blynk.virtualWrite(V54, DataTX.S[54]);
      break;
    case 55:
      Blynk.virtualWrite(V55, DataTX.S[55]);
      break;
    case 56:
      Blynk.virtualWrite(V56, DataTX.S[56]);
      break;
    case 57:
      Blynk.virtualWrite(V57, DataTX.S[57]);
      break;
    case 58:
      Blynk.virtualWrite(V58, DataTX.S[58]);
      break;
    case 59:
      Blynk.virtualWrite(V59, DataTX.S[59]);
      break;
    case 60:
      Blynk.virtualWrite(V60, DataTX.S[60]);
      break;
    case 61:
      Blynk.virtualWrite(V61, DataTX.S[61]);
      break;
    case 62:
      Blynk.virtualWrite(V62, DataTX.S[62]);
      break;
    case 63:
      Blynk.virtualWrite(V63, DataTX.S[63]);
      break;
    case 64:
      Blynk.virtualWrite(V64, DataTX.S[64]);
      break;
    case 65:
      Blynk.virtualWrite(V65, DataTX.S[65]);
      break;
    case 66:
      Blynk.virtualWrite(V66, DataTX.S[66]);
      break;
    case 67:
      Blynk.virtualWrite(V67, DataTX.S[67]);
      break;
    case 68:
      Blynk.virtualWrite(V68, DataTX.S[68]);
      break;
    case 69:
      Blynk.virtualWrite(V69, DataTX.S[69]);
      break;
    case 70:
      Blynk.virtualWrite(V70, DataTX.S[70]);
      break;
    case 71:
      Blynk.virtualWrite(V71, DataTX.S[71]);
      break;
    case 72:
      Blynk.virtualWrite(V72, DataTX.S[72]);
      break;
    case 73:
      Blynk.virtualWrite(V73, DataTX.S[73]);
      break;
    case 74:
      Blynk.virtualWrite(V74, DataTX.S[74]);
      break;
    case 75:
      Blynk.virtualWrite(V75, DataTX.S[75]);
      break;
    case 76:
      Blynk.virtualWrite(V76, DataTX.S[76]);
      break;
    case 77:
      Blynk.virtualWrite(V77, DataTX.S[77]);
      break;
    case 78:
      Blynk.virtualWrite(V78, DataTX.S[78]);
      break;
    case 79:
      Blynk.virtualWrite(V79, DataTX.S[79]);
      break;
    case 80:
      Blynk.virtualWrite(V80, DataTX.S[80]);
      break;
    case 81:
      Blynk.virtualWrite(V81, DataTX.S[81]);
      break;
    case 82:
      Blynk.virtualWrite(V82, DataTX.S[82]);
      break;
    case 83:
      Blynk.virtualWrite(V83, DataTX.S[83]);
      break;
    case 84:
      Blynk.virtualWrite(V84, DataTX.S[84]);
      break;
    case 85:
      Blynk.virtualWrite(V85, DataTX.S[85]);
      break;
    case 86:
      Blynk.virtualWrite(V86, DataTX.S[86]);
      break;
    case 87:
      Blynk.virtualWrite(V87, DataTX.S[87]);
      break;
    case 88:
      Blynk.virtualWrite(V88, DataTX.S[88]);
      break;
    case 89:
      Blynk.virtualWrite(V89, DataTX.S[89]);
      break;
    case 90:
      Blynk.virtualWrite(V90, DataTX.S[90]);
      break;
    case 91:
      Blynk.virtualWrite(V91, DataTX.S[91]);
      break;
    case 92:
      Blynk.virtualWrite(V92, DataTX.S[92]);
      break;
    case 93:
      Blynk.virtualWrite(V93, DataTX.S[93]);
      break;
    case 94:
      Blynk.virtualWrite(V94, DataTX.S[94]);
      break;
    case 95:
      Blynk.virtualWrite(V95, DataTX.S[95]);
      break;
    case 96:
      Blynk.virtualWrite(V96, DataTX.S[96]);
      break;
    case 97:
      Blynk.virtualWrite(V97, DataTX.S[97]);
      break;
    case 98:
      Blynk.virtualWrite(V98, DataTX.S[98]);
      break;
    case 99:
      Blynk.virtualWrite(V99, DataTX.S[99]);
      break;
  }
}

//=================================SYNC VARIABLE==========================//
BLYNK_CONNECTED() {
  for (int i = 1; i < NUM_SWITHC + 1; i++)
  {
    Data_CLOUD_write(i);
  }

}

//=============================EEPROM WRITE====================================//
void Data_EEPROM_write()
{
  for (int i = 1; i <= NUM_SWITHC ; i++) {
    EEPROM.write(i, DataTX.S[i]);
  }
  EEPROM.commit();
}


//==================================WRITING TO REALY MODULE================================//
void Data_Switch_write()
{
  for (int i = 1; i <= NUM_MODULE * 3; i++) {
    if (DataTX.S[i] == 0)
    {
      out.off(i);
    }
    else
    {
      out.on(i);
    }
  }
  Data_EEPROM_write();
}


//========================================READING SHIFT REGISTER==============================//

void Input_Data()
{

  for (int j = 0; j < (Num_74HC165 * 8); j++)
  {
    Pervious_Input_Switch[j] = Current_Input_Switch[j];
  }
  digitalWrite(clockEnablePin, HIGH);
  digitalWrite(load, LOW);
  delay(5);
  digitalWrite(load, HIGH);
  delay(5);
  digitalWrite(clockEnablePin, LOW);
  int j = 0;

  for (int i = 0; i < (Num_74HC165 * 16) - 1; i++)
  {
    if (i % 2 == 0)
    {

      digitalWrite(clockIn, HIGH);
      Current_Input_Switch[j] = digitalRead(dataIn);
      j++;
    }
    else
    {
      digitalWrite(clockIn, LOW);
    }
    delay(1);
  }
  int temp[100];
  for (int j = 0; j < (Num_74HC165 * 8); j++)
  {
    temp[j] = Current_Input_Switch[j];
  }
  int i = 0;
  for (int j = (Num_74HC165 * 8) - 1; i < (Num_74HC165 * 8); j--)
  {
    Current_Input_Switch[j] = temp[i];
    i++;
  }

}

//=======================================WIFI SCAN===================================//

void initial_wifi_fail()
{
  // SCAN ALL THE AVAILABLE WIFI//
  if (wifi_available_status == false)
  {
    if (millis() - Wifi_Reconnect_Timer > 12000)
    {
      WiFi.scanNetworks(true);
      if (Debug_print)
      {
        Serial.print("\nScan start ... ");
      }
      Wifi_Reconnect_Timer = millis();
    }
    int n = WiFi.scanComplete();
    if (n >= 0)
    {
      if (Debug_print)
      {
        Serial.printf("%d network(s) found\n", n);
      }
      for (int i = 0; i < n; i++)
      {
        if (WiFi.SSID(i) == ssid)
        {
          if (Debug_print)
          {
            Serial.println(" networks found");
          }
          //IF REQUIRED NETWORK FOUND IT WILL CONNECT TO IT//
          WiFi.begin(ssid, pass);
          while (WiFi.status() != WL_CONNECTED) {
            if (Debug_print)
            {
              Serial.print(".");
            }
            delay(100);
          }
          wifi_available_status = true;
        }
      }
      WiFi.scanDelete();
    }
  }
  //CHECKING FOR INTERNET AVAILABILITY IN THE WIFI//
  if (wifi_available_status == true && internet_available_status == false)
  {
    if (millis() - Net_Reconnect_Timer > 12000)
    {
      //PING TO GOOGLE.COM AND CHECK FOR RESPONCE//
      if  (Ping.ping(remote_ip)) {
        if (Debug_print)
        {
          Serial.println("Connected to Internet");
        }
        internet_available_status = true;
        Blynk.config(auth);

      }
      Net_Reconnect_Timer = millis();
    }

  }
}
void setup() {
  //INTIALIZING PINS//
  pinMode(load, OUTPUT);
  pinMode(clockEnablePin, OUTPUT);
  pinMode(clockIn, OUTPUT);
  pinMode(dataIn, INPUT);
  if (Debug_print)
  {
    Serial.begin(115200);
    Serial.print(" ");
  }
  //READING EEPROM DATA
  EEPROM.begin(512);
  for (int i = 1; i <= NUM_SWITHC ; i++) {
    DataTX.S[i] = EEPROM.read(i);
    if (Debug_print)
    {
      Serial.print(DataTX.S[i]);
      Serial.print(" ");
    }
  }
  FastLED.addLeds<WS2811, DATA_PIN>(module, NUM_MODULE);
  if (Debug_print)
  {
    Serial.println(" ");
  }
  //WRITING EEPROM DATA TO RELAY
  for (int i = 1; i <= NUM_MODULE * 3; i++) {
    out.off(i);
  }
  delay(100);
  for (int i = 1; i <= NUM_MODULE * 3; i++) {
    if (DataTX.S[i] == 0)
    {
      out.off(i);
    }
    else
    {
      out.on(i);
    }
  }
  delay(100);
  //CALCULATING NUMBER OF SHIFT REGISTER//
  float n = NUM_SWITHC / 8.0;
  if (n - int(n) != 0)
  {
    Num_74HC165 = int(n) + 1;
  }
  else
  {
    Num_74HC165 = int(n);
  }
  //CHECKING FOR WIFI//
  WiFi.scanNetworks();
  int wn = WiFi.scanComplete();
  if (wn >= 0)
  {
    if (Debug_print)
    {
      Serial.printf("%d network(s) found\n", wn);
    }
    for (int i = 0; i < wn; i++)
    {
      if (WiFi.SSID(i) == ssid)
      {
        wifi_available_status = true;
        if (Debug_print)
        {
          Serial.println(" networks found");
        }
      }
    }
    WiFi.scanDelete();
  }
  //IF WIFI REQUIRED AVAILABLE CONNECTING TO IT //
  if (wifi_available_status)
  {
    BLYNK_LOG2(BLYNK_F("Connecting to "), ssid);
    WiFi.mode(WIFI_STA);

    if (WiFi.status() != WL_CONNECTED) {
      if (pass && strlen(pass)) {
        WiFi.begin(ssid, pass);
      } else {
        WiFi.begin(ssid);
      }
    }
    while (WiFi.status() != WL_CONNECTED) {
      if (Debug_print)
      {

        Serial.print(".");
      }
      delay(100);
    }
    BLYNK_LOG1(BLYNK_F("Connected to WiFi"));

    IPAddress myip = WiFi.localIP();
    (void)myip;
    BLYNK_LOG_IP("IP: ", myip);

  }
  //CHECKING FOR INTERNET IN THE CONNECTED WIFI//
  if  (Ping.ping(remote_ip)) {
    if (Debug_print)
    {
      Serial.println("Connected to Internet");
    }
    internet_available_status = true;
  }
  //IF INTERNET AVAILABLE CONFIGURING THE BLYNK//
  if (internet_available_status)
  {
    Blynk.config(auth);
  }
  //CHECKING FOR SENSOR
  if (Debug_print)
  {
    Serial.println("Sensor test");
  }
  if (BMP_280)
  {
    if ( bmp280.begin(0x76, 0x58))
    {
      if (Debug_print)
      {
        Serial.println("BMP 280 Sensor available");
      }
      sensor_available = true;
    }
  }
  else
  {
    if ( bmp180.begin())
    {
      if (Debug_print)
      {
        Serial.println("BMP 180 Sensor available");
      }
      sensor_available = true;
    }
  }

  delay(100);
  if (CURRENT_SENSOR)
  {
    emon1.current(A0, 4.9);
  }
  if (Debug_print)
  {
    Serial.println("Setup end");
  }
}

void loop() {

  //IF WIFI & INTERNET AVAILABLE IT WILL RUN ON ONLINE, ELSE IT WILL RUN IN OFFLINE
  if (wifi_available_status && internet_available_status)
  {
    Blynk.run();
  }

  //READING INPUT DATA
  Input_Data();

  if (Debug_print)
  {
    Serial.print("D :");
  }

  //WRITING DATA TO CLOUD
  for (int i = 0; i < NUM_SWITHC; i++)
  {
    if (Current_Input_Switch[i] != Pervious_Input_Switch[i])
    {
      DataTX.S[i + 1] = (!DataTX.S[i + 1]);
      Data_CLOUD_write(i + 1);
    }
    if (Debug_print)
    {
      Serial.print(DataTX.S[i + 1]);
      Serial.print(" ");
    }
  }

  //WRITING DATA TO RELAY
  Data_Switch_write();

  //UPLAODE SENSOR DATA EVERY SEC
  if ((millis() - lastTime) > timerDelay) {
    if (CURRENT_SENSOR)
    {
      DataTX.AMP = emon1.calcIrms(1480);
      Blynk.virtualWrite(V100, DataTX.AMP);

    }
    else
    {
      Blynk.virtualWrite(V100, 0);
    }
    if (sensor_available)
    {
      if (BMP_280)
      {
        DataTX.temperature = bmp280.readTemperature();
        DataTX.pressure = bmp280.readPressure();
        Blynk.virtualWrite(V101, DataTX.temperature);
        Blynk.virtualWrite(V102, DataTX.pressure / 100.0);

      }
      else
      {
        DataTX.temperature = bmp180.readTemperature();
        DataTX.pressure = bmp180.readPressure();
        Blynk.virtualWrite(V101, DataTX.temperature);
        Blynk.virtualWrite(V102, DataTX.pressure / 100.0);
      }

    }
    else
    {
      Blynk.virtualWrite(V8, 0);
      Blynk.virtualWrite(V9, 0);
    }
    lastTime = millis();
  }

  //IF WIFI OR INTERNET FAIL AT STARTING IT WILL RE-INITIATE CONNECTION
  if (wifi_available_status == false || internet_available_status == false)
  {
    initial_wifi_fail();
  }

  if (Debug_print)
  {
    Serial.print(" AMP : ");
    Serial.print(DataTX.AMP);
    Serial.print(" TEMP : ");
    Serial.print(DataTX.temperature);
    Serial.print(" PRESSURE : ");
    Serial.print(DataTX.pressure / 100.0);
    Serial.println(" ");
  }
}

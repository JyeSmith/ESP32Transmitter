#include "HardwareConfig.h"
#include "Tasks.h"
//#include "FrskyD.ino"
//#include "FrskyX.h"
#include "FrskyCommon.h"
#include "ADC.h"




uint16_t ReadFrSky_2way();

#define DEBUG_SERIAL

uint32_t lastcallback = 0;
uint32_t nextcallbackdelay = 0;

#ifdef DEBUG_SERIAL
uint32_t nextDebugSerialPrintTime = 0;
uint16_t intervalDebugSerialPrintTime = 200; // ms
#endif

void setup() {

#ifdef OLED
  oledSetup();
#endif

#ifdef DEBUG_SERIAL
  Serial.begin(115200);
  Serial.println("Booting....");
  
#endif

  InitHardwarePins();
  InitADCtimer();

  //InitFailsafe();
  //option = FORCE_FRSKYX_TUNING;

  RX_num = 00;
  MProtocol_id_master = ESP.getEfuseMac();//0x12345678;

  MProtocol_id = RX_num + MProtocol_id_master;
  set_rx_tx_addr(MProtocol_id);
//  BIND_IN_PROGRESS;

  //initFrSky_2way();
  //initFrSkyX();

  //Channel_data = 1750;
  //protocol_init();
  remote_callback = ReadFrSky_2way; 
  StartSendTask();
  

}


void loop() {
  
#ifdef DEBUG_SERIAL
  if (nextDebugSerialPrintTime < millis()) {
    nextDebugSerialPrintTime += intervalDebugSerialPrintTime;
    
    Serial.println(state);
    
    for (int i = 0; i < 7; i++) {
      Serial.print("Channel_data ");
      Serial.print(i);
      Serial.print(" = ");
      Serial.println(Channel_data[i]);
    }
    Serial.println("");
  }
#endif

}

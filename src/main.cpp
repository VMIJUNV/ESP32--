#include "Arduino.h"
#include "EPD_3in7.h"
#include "GUI_Paint.h"
#include "fonts.h"
#include "SPIFFS.h"
#include "wireless.h"
#include "API.h"

int i=1;
void setup() 
{
  Serial.begin(115200);

  Init_wireless();

  SPIFFS.begin(true);

  IO_init();
  EPD_3IN7_4Gray_Init();
  EPD_3IN7_4Gray_Clear();
}

void loop() 
{
  server.handleClient();
  if (i==1){
    Update_display_Read();
    i=0;
  }
}

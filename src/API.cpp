#include "API.h"

extern WebServer server; 

UWORD Imagesize = ((EPD_3IN7_WIDTH % 4 == 0)? (EPD_3IN7_WIDTH / 4 ): (EPD_3IN7_WIDTH / 4 + 1)) * EPD_3IN7_HEIGHT;
UBYTE *BlackImage = (UBYTE *)malloc(Imagesize);

String SPIFFS_Read(char *path)
{
    File f;
    String state;
    f = SPIFFS.open(path, "r");
    f.seek(0);
    state = f.readString();
    f.close();
    return state;
}

void SPIFFS_Write(char *path,char *text)
{
    File f;
    f = SPIFFS.open(path, "w");
    f.print(text);
    f.close();
}



void Update_display()
{
  String state =server.arg("value");
  if (state == "refresh"){
    SPIFFS_Write((char*)"/coufig.txt",(char*)"refresh");
  }
  else if (state == "User") {
    SPIFFS_Write((char*)"/coufig.txt",(char*)"User");
  }
  else
  {
    SPIFFS_Write((char*)"/coufig.txt",(char*)"hhh");
    SPIFFS_Write((char*)"/customize.txt",(char*)state.c_str());
  }
  Update_display_Read();
}

extern char poet1[];
void Update_display_Read()
{
  String state = SPIFFS_Read((char*)"/coufig.txt");
  if (state == "refresh"){
    Draw_text(poet1);
  }
  else if (state == "User") {
    Draw_text((char*)"功能开发中");
  }
  else
  {
    state = SPIFFS_Read((char*)"/customize.txt");
    Draw_text((char*)state.c_str());
  }
}

extern int EPD_X;
extern int EPD_Y;
void Draw_text(char *str)
{
    String conf1=SPIFFS_Read((char *)"/couf1.txt");
    String conf2=SPIFFS_Read((char *)"/couf2.txt");
    if (strcmp(conf2.c_str(), "1")  == 0){Paint_NewImage(BlackImage, EPD_3IN7_WIDTH, EPD_3IN7_HEIGHT, 90, WHITE);EPD_X=480;EPD_Y=280;}
    else {Paint_NewImage(BlackImage, EPD_3IN7_WIDTH, EPD_3IN7_HEIGHT, 0, WHITE);EPD_X=280;EPD_Y=480;}
    Paint_SetScale(4);
    Paint_Clear(WHITE);
    if (strcmp(conf1.c_str(), "16")  == 0){Paint_DrawString_CN(0,0,str,&Font16,GRAY4,WHITE);}
    else {Paint_DrawString_CN(0,0,str,&Font32,GRAY4,WHITE);}
    EPD_3IN7_4Gray_Display(BlackImage);
}
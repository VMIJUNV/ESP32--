#ifndef __API_H
#define __API_H

#include "Arduino.h"
#include <WiFi.h>
#include <WebServer.h>
#include"FS.h"
#include "SPIFFS.h"
#include "GUI_Paint.h"

void Update_display();
void Update_display_Read();
void SPIFFS_Write(char *path,char *text);
String SPIFFS_Read(char *path);
void Draw_text(char *str);


#endif
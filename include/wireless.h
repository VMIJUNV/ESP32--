#ifndef __WIRELESS_H
#define __WIRELESS_H

#include "Arduino.h"
#include <WiFi.h>
#include <WebServer.h>
#include"FS.h"
#include "SPIFFS.h"
#include "GUI_Paint.h"

#include "API.h"

extern WebServer server;

void Init_wireless();
void Update_display();

#endif
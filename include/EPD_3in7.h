/*****************************************************************************
* | File      	:   EPD_3IN7.h
* | Author      :   Waveshare team
* | Function    :   3.7inch e-paper
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2020-07-16
* | Info        :
* -----------------------------------------------------------------------------
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#ifndef __EPD_3IN7_H_
#define __EPD_3IN7_H_

#include "Arduino.h"
#include <SPI.h>


#define UBYTE   uint8_t
#define UWORD   uint16_t
#define UDOUBLE uint32_t

// Display resolution
#define EPD_3IN7_WIDTH       280
#define EPD_3IN7_HEIGHT      480 

#define SPI_SCK  18            
#define SPI_SDA  23               
#define SPI_RST  2              
#define SPI_DC   15              
#define SPI_CS   5               
#define SPI_BLK  22
#define BUSY_PIN 4

#define SPI_FREQUENCY           40 * 1000000

#define SPI_RST_0  digitalWrite(SPI_RST,LOW)               
#define SPI_RST_1  digitalWrite(SPI_RST,HIGH)
#define SPI_DC_0  digitalWrite(SPI_DC,LOW)               
#define SPI_DC_1  digitalWrite(SPI_DC,HIGH)
#define SPI_CS_0  digitalWrite(SPI_CS,LOW)               
#define SPI_CS_1 digitalWrite(SPI_CS,HIGH)
#define SPI_BLK_0 digitalWrite(SPI_BLK,LOW)
#define SPI_BLK_1 digitalWrite(SPI_BLK,HIGH)

void IO_init(void );
void EPD_3IN7_4Gray_Clear(void);
void EPD_3IN7_4Gray_Init(void);
void EPD_3IN7_4Gray_Display(const UBYTE *Image);

void EPD_3IN7_1Gray_Clear(void);
void EPD_3IN7_1Gray_Init(void);
void EPD_3IN7_1Gray_Display(const UBYTE *Image);
void EPD_3IN7_1Gray_Display_Part(const UBYTE *Image, UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend);
void EPD_3IN7_Sleep(void);
 
#endif

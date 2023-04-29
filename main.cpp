// uLCD-144-G2 demo program for uLCD-4GL LCD driver library
//
#include "mbed.h"
#include "uLCD_4DGL.h"

uLCD_4DGL uLCD(p28,p27,p30); // serial tx, serial rx, reset pin;
RawSerial pc(USBTX, USBRX);

void display_time(char time) {
    if(time == '\r') {
        uLCD.cls();
        return;
    }
    uLCD.putc(time);
}

int main()
{
    // basic printf demo = 16 by 18 characters on screen
    uLCD.puts("\nHello uLCD World\n"); //Default Green on black text
    while(true) {
        char c = pc.getc();
        display_time(c);
    }
}

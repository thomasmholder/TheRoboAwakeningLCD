// uLCD-144-G2 demo program for uLCD-4GL LCD driver library
//
#include "mbed.h"
#include "uLCD_4DGL.h"

uLCD_4DGL uLCD(p9, p10, p6); // serial tx, serial rx, reset pin;
RawSerial ble(p13, p14);
RawSerial pc(USBTX, USBRX);
RawSerial pi(p28, p27);

void display_text(const char text) {
    if (text == '\r') {
        uLCD.cls();
        uLCD.text_height(2);
        uLCD.text_width(1);
        uLCD.locate(0, 4);
    } else {
        uLCD.putc(text);
    }
}

void printf_char(const char text, const char* source) {
    if (text == '\r') {
        pc.printf("from %s: \\r (0x%x)\r\n", source, (int) text);
    } else if (text == '\n') {
        pc.printf("from %s: \\n (0x%x)\r\n", source, (int) text);
    } else {
        pc.printf("from %s: %c (0x%x)\r\n", source, text, (int) text);
    }
}

void on_ble_read(void) {
    while (ble.readable()) {
        const char c = ble.getc();
        printf_char(c, "ble");
        pi.putc(c);
    }
}

void on_pi_read(void) {
    while (pi.readable()) {
        const char c = pi.getc();
        printf_char(c, "pi");
        display_text(c);
    }
}

int main()
{
    // basic printf demo = 16 by 18 characters on screen
    //uLCD.puts("\nHello uLCD World\n"); //Default Green on black text
    uLCD.baudrate(115200);
    uLCD.cls();
    uLCD.text_height(2);
    uLCD.text_width(1);
    uLCD.locate(0, 4);
    uLCD.puts("Initializing...\n");
    pc.baud(115200);
    pc.printf("\r\nInitializing...\r\n");
    pi.attach(&on_pi_read);
    ble.attach(&on_ble_read);
    while (true) {
        sleep();
    }
}

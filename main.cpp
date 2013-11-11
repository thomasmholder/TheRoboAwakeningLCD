//
// TFT_4DGL is a class to drive 4D Systems TFT touch screens
//
// Copyright (C) <2010> Stephane ROCHON <stephane.rochon at free.fr>
//
// TFT_4DGL is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// TFT_4DGL is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with TFT_4DGL.  If not, see <http://www.gnu.org/licenses/>.

#include "mbed.h"
#include "uLCD_4DGL.h"

#define SIZE_X  128
#define SIZE_Y  128
//

uLCD_4DGL uLCD(p9,p10,p11); // serial tx, serial rx, reset pin;

int main()
{

    uLCD.baudrate(115200);
    uLCD.background_color(DGREY);
    uLCD.circle(60, 50, 30, 0xFF00FF);
    uLCD.triangle(120, 100, 40, 40, 10, 100, 0x0000FF);
    uLCD.line(0, 0, 80, 60, 0xFF0000);
    uLCD.rectangle(50, 50, 100, 90, 0x00FF00);
    uLCD.pixel(60, 60, BLACK);
    uLCD.read_pixel(120, 70);
    uLCD.circle(120, 60, 10, BLACK);
    uLCD.set_font(FONT_8X8);
    uLCD.text_mode(TRANSPARENT);
    uLCD.text_char('B', 9, 8, BLACK);
    uLCD.text_char('I',10, 8, BLACK);
    uLCD.text_char('G',11, 8, BLACK);
    uLCD.text_string("This is a test of string", 1, 14, FONT_5X7, WHITE);

}

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
#include "TFT_4DGL.h"

TFT_4DGL ecran(p9,p10,p11); // serial tx, serial rx, reset pin;

int main() {
    char s[500];
    int x = 0, y = 0, status, xc = 0, yc = 0;
    
 
    ecran.baudrate(115200);
// new code to set resolution to 640 by 480
// also changed max size_x and size_y in TFT_4DGL_graphics.h
// Screen_res command is 12 decimal and not 12hex as listed in manual
    ecran.display_control(SCREEN_RES, char(1));
    ecran.background_color(DGREY);
    ecran.circle(120, 160, 80, 0xFF00FF);
    ecran.triangle(120, 100, 40, 300, 200, 270, 0x0000FF);
    ecran.line(0, 0, 239, 319, 0xFF0000);
    ecran.rectangle(50, 50, 200, 90, 0x00FF00);
    ecran.ellipse(100, 250, 80, 30, 0xFFFF00);
    ecran.pixel(120, 160, BLACK);
    ecran.read_pixel(120, 170);
    ecran.screen_copy(50, 50, 200, 200, 100, 100);
    ecran.pen_size(WIREFRAME);
    ecran.circle(120, 160, 60, BLACK);
    ecran.set_font(FONT_8X8);
    ecran.text_mode(TRANSPARENT);
    ecran.text_char('B', 9, 8, BLACK);
    ecran.text_char('I',10, 8, BLACK);
    ecran.text_char('G',11, 8, BLACK);
    ecran.graphic_char('G', 120, 120, BLACK, 4, 4);
    ecran.text_string("This is a test of string", 2, 12, FONT_8X8, WHITE);
    ecran.graphic_string("This is a test of graphic string", 20, 200, FONT_8X8, WHITE, 2, 2);
    ecran.text_button("OK", UP, 40, 260, 0xFF0000, FONT_8X8, BLACK, 2, 2);
// demo code deleted here for touch screen - no touch screen on uVGA II

 
}
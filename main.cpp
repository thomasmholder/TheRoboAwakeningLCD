//
// TFT_4DGL is a class to drive 4D Systems LCD screens
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

//#define SIZE_X  128
//#define SIZE_Y  128
//

uLCD_4DGL uLCD(p9,p10,p11); // serial tx, serial rx, reset pin;

int main()
{

    // basic printf demo = 16 by 18 characters on screen
    uLCD.printf("\nHello uLCD World\n"); //Default Green on black text
    uLCD.printf("\n  Starting Demo...");
    uLCD.text_width(4); //4X size text
    uLCD.text_height(4);
    uLCD.color(RED);
    for (int i=10; i>=0; --i) {
        uLCD.locate(1,2);
        uLCD.printf("%2D",i);
        wait(.5);
    }

    uLCD.cls();

    uLCD.printf("Change baud rate......");
    uLCD.baudrate(600000); //jack up baud rate to max for fast display
    //if demo hangs here - try lower baud rates
    // printf text only full screen mode demo
    uLCD.background_color(BLUE);
    uLCD.cls();
    uLCD.locate(0,0);
    uLCD.color(WHITE);
    uLCD.textbackground_color(BLUE);
    uLCD.set_font(FONT_7X8);
    uLCD.text_mode(OPAQUE);
    int i=0;
    while(i<64) {
        if(i%16==0) uLCD.cls();
        uLCD.printf("TxtLine %2D Page %D\n",i%16,i/16 );
        i++; //16 lines with 18 charaters per line
    }
    wait(0.5);
    //demo graphics commands
    uLCD.background_color(BLACK);
    uLCD.cls();
    uLCD.background_color(DGREY);
    uLCD.circle(60, 50, 30, 0xFF00FF);
    uLCD.triangle(120, 100, 40, 40, 10, 100, 0x0000FF);
    uLCD.line(0, 0, 80, 60, 0xFF0000);
    uLCD.rectangle(50, 50, 100, 90, 0x00FF00);
    uLCD.pixel(60, 60, BLACK);
    uLCD.read_pixel(120, 70);
    uLCD.circle(120, 60, 10, BLACK);
    uLCD.set_font(FONT_7X8);
    uLCD.text_mode(TRANSPARENT);
    uLCD.text_bold(ON);
    uLCD.text_char('B', 9, 8, BLACK);
    uLCD.text_char('I',10, 8, BLACK);
    uLCD.text_char('G',11, 8, BLACK);
    uLCD.text_italic(ON);
    uLCD.text_string("This is a test of string", 1, 4, FONT_7X8, WHITE);
    wait(2);

//Bouncing Ball Demo
    float fx=50.0,fy=21.0,vx=1.0,vy=0.4;
    int x=50,y=21,radius=4;
    uLCD.background_color(BLACK);
    uLCD.cls();
    //draw walls
    uLCD.line(0, 0, 127, 0, WHITE);
    uLCD.line(127, 0, 127, 127, WHITE);
    uLCD.line(127, 127, 0, 127, WHITE);
    uLCD.line(0, 127, 0, 0, WHITE);
    for (int i=0; i<1500; i++) {
        //draw ball
        uLCD.circle(x, y, radius, RED);
        //bounce off edge walls and slow down a bit?
        if ((x<=radius+1) || (x>=126-radius)) vx = -.90*vx;
        if ((y<=radius+1) || (y>=126-radius)) vy = -.90*vy;
        //erase old ball location
        uLCD.circle(x, y, radius, BLACK);
        //move ball
        fx=fx+vx;
        fy=fy+vy;
        x=(int)fx;
        y=(int)fy;
    }
    wait(0.5);
//draw an image pixel by pixel
    int pixelcolors[50][50];
    uLCD.background_color(BLACK);
    uLCD.cls();
//compute Mandelbrot set image for display
//image size in pixels and  setup
    const unsigned ImageHeight=128;
    const unsigned ImageWidth=128;
    //region to display
    double MinRe = -0.75104;
    double MaxRe = -0.7408;
    double MinIm = 0.10511;
    double MaxIm = MinIm+(MaxRe-MinRe)*ImageHeight/ImageWidth;
    double Re_factor = (MaxRe-MinRe)/(ImageWidth-1);
    double Im_factor = (MaxIm-MinIm)/(ImageHeight-1);
    unsigned MaxIterations = 2048;
    for(unsigned y=0; y<ImageHeight; ++y) {
        double c_im = MaxIm - y*Im_factor;
        for(unsigned x=0; x<ImageWidth; ++x) {
            double c_re = MinRe + x*Re_factor;
            double Z_re = c_re, Z_im = c_im;
            int niterations=0;
            for(unsigned n=0; n<MaxIterations; ++n) {
                double Z_re2 = Z_re*Z_re, Z_im2 = Z_im*Z_im;
                if(Z_re2 + Z_im2 > 4) {
                    niterations = n;
                    break;
                }
                Z_im = 2*Z_re*Z_im + c_im;
                Z_re = Z_re2 - Z_im2 + c_re;
            }
            if (niterations!=(MaxIterations-1))
                uLCD.pixel(x,y,((niterations & 0xF00)<<12)+((niterations & 0xF0)<<8)+((niterations & 0x0F)<<4) );
        }
    }
    wait(5);
// PLASMA wave BLIT animation
//draw an image using BLIT (Block Image Transfer) fastest way to transfer pixel data
    uLCD.cls();
    int num_cols=50;
    int num_rows=50;
    int frame=0;
    double a,b,c=0.0;
    while(frame<50) {
        for (int k=0; k<num_cols; k++) {
            b= (1+sin(3.14159*k*0.75/(num_cols-1.0)+c))*0.5;
            for (int i=0; i<num_rows; i++) {
                a= (1+sin(3.14159*i*0.75/(num_rows-1.0)+c))*0.5;
                // a and b will be a sine wave output between 0 and 1
                // sine wave was scaled for nice effect across array
                // uses a and b to compute pixel colors based on rol and col location in array
                // also keeps colors at the same brightness level
                if ((a+b) <.667)
                    pixelcolors[i][k] =  (255-(int(254.0*((a+b)/0.667)))<<16) | (int(254.0*((a+b)/0.667))<<8) | 0;
                else if ((a+b)<1.333)
                    pixelcolors[i][k] = (0 <<16) | (255-(int (254.0*((a+b-0.667)/0.667)))<<8) | int(254.0*((a+b-0.667)/0.667));
                else
                    pixelcolors[i][k] = (int(255*((a+b-1.333)/0.667))<<16) | (0<<8)  | (255-(int (254.0*((a+b-1.333)/0.667))));
            }
        }
        uLCD.BLIT(39, 39, 50, 50, &pixelcolors[0][0]);
        c = c + 0.0314159*3.0;
        if (c > 6.2831) c = 0.0;
        frame++;
    }
    uLCD.cls();
    //SD card needed with image and video files for last two demos
    while(1){}  //remove line, if SD card is used
    uLCD.cls();
    uLCD.media_init();
    uLCD.set_sector_address(0x001D, 0x4C01);
    uLCD.display_image(0,0);
    wait(10);
    while(1) {
        uLCD.cls();
        uLCD.media_init();
        uLCD.set_sector_address(0x001D, 0x4C42);
        uLCD.display_video(0,0);
    }
}



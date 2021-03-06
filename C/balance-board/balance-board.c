#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "lib/fonts.h"
#include "lib/st7735.h"
#include "lib/ICM20948.h"

float getMax (float a, float b) {
    if (a > b) {
        return a;
    }
    else {
        return b;
    }
}

float getAbs (float a) {
    if (a < 0) {
        return a * -1;
    }
    else {
        return a;
    }
}

int main() {
    stdio_init_all();
    setvbuf(stdout, NULL, _IONBF, 0);
    sleep_ms(1000);

    // TODO: Setup the ST7735 on GPIO 4 and 5, using I2C

    sleep_ms(1000);

    // TODO: Setup the IMU

    float x;
    float y;
    float z; // Unused but needed for the below function
    float max;
    uint16_t colour = ST7735_GREEN;

    while (true) {
        // TODO: Get, and assign, the values from the accelation of the IMU
        // Hint: When assigning to x, y and z, use the absolute value!

        max = getMax(x, y);
        if (max < 0.33f) {
            if (colour != ST7735_GREEN) {
                colour = ST7735_GREEN;
                ST7735_FillScreen(colour);
            }
        }
        else if (max >= 0.33f && max < 0.66f) {
            if (colour != ST7735_YELLOW) {
                colour = ST7735_YELLOW;
                ST7735_FillScreen(colour);
            }
        }
        else {
            if (colour != ST7735_RED) {
                colour = ST7735_RED;
                ST7735_FillScreen(colour);
            }
        }

        sleep_ms(50);
    }
}
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
    ST7735_Init();
    ST7735_FillScreen(ST7735_WHITE);

    i2c_init(i2c0, 400 * 1000);
    gpio_set_function(4, GPIO_FUNC_I2C);
    gpio_set_function(5, GPIO_FUNC_I2C);

    gpio_pull_up(4);
    gpio_pull_up(5);

    sleep_ms(1000);

    IMU_EN_SENSOR_TYPE enMotionSensorType;
    imuInit(&enMotionSensorType);
    if (IMU_EN_SENSOR_TYPE_ICM20948 != enMotionSensorType) {
        printf("Failed to initialise IMU...");
    }
    printf("IMU initialised!");

    float x;
    float y;
    float z; // Unused but needed for the below function
    float max;
    uint16_t colour = ST7735_GREEN;

    while (true) {
        icm20948AccelRead(&x, &y, &z);
        x = getAbs(x);
        y = getAbs(y);

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
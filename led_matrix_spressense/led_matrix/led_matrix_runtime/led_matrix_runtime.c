
/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <debug.h>
#include <nuttx/i2c/i2c_master.h>
#include "rgbMatrixI2CDriver/rgbMatrix.h"
#include <pthread.h>
#include "pubsub-c/pubsub.h"
#include "led_matrix_runtime.h"
#include "HSV-RGB-Conversion/hsv.h"
/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* I2C settings */

#define I2C_SLAVE_ADDR 0x24
#define I2C_SPEED I2C_SPEED_FAST

/* ICMD defnitions */

#define ICMD_AVAILABLE_SIZE(n) (0x10 + (n))
#define ICMD_FIXLEN_TRANS(n) (0x80 + (n))
#define ICMD_VARLEN_TRANS(n) (0xa0 + (n))

/* User defined buffer id */

#define WRITE_BUFFER 0
#define READ_BUFFER 1
#define VERSION_BUFFER 2
#define TIMESTAMP_BUFFER 3

uint8_t rectangle_coor[] = {0, 0, 7, 7};

uint8_t green[][2] = {{2, 1}, {3, 1}, {5, 1}, {1, 2}, {2, 2}, {4, 2}, {5, 2}, {6, 2}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {6, 3}, {2, 4}, {4, 4}, {5, 4}, {1, 5}, {3, 5}, {5, 5}, {6, 5}, {1, 6}, {2, 6}, {5, 6}, {6, 6}};

uint8_t flash[][2] = {{4, 1}, {3, 2}, {5, 3}, {3, 4}, {2, 5}, {4, 5}};
uint8_t red[][2] = {{0, 3}, {7, 3}, {0, 6}, {7, 6}};
uint8_t yellow[][2] = {{3, 0}, {4, 0}, {3, 6}, {4, 6}, {3, 7}, {4, 7}};
uint8_t color[7][3] = {{255, 0, 0},
                       {255, 102, 0},
                       {255, 255, 0},
                       {0, 255, 0},
                       {0, 128, 128},
                       {0, 0, 255},
                       {128, 0, 128}};

struct I2C1735 handle;

void tree()
{
    int lenTotal_green = sizeof(green) / sizeof(uint8_t);
    int lenLow_green = sizeof(green[0]) / sizeof(uint8_t);
    int lenHigh_green = lenTotal_green / lenLow_green;
    for (int i = 0; i < lenHigh_green; i++)
    {
        draw_point_color(&handle, green[i], 0, 60, 0);
    }
    image_test(&handle);
    int lenTotal_yellow = sizeof(yellow) / sizeof(uint8_t);
    int lenLow_yellow = sizeof(yellow[0]) / sizeof(uint8_t);
    int lenHigh_yellow = lenTotal_yellow / lenLow_yellow;
    for (int i = 0; i < lenHigh_yellow; i++)
    {
        draw_point_color(&handle, yellow[i], 60, 60, 0);
    }
    image_test(&handle);
    int lenTotal_red = sizeof(red) / sizeof(uint8_t);
    int lenLow_red = sizeof(red[0]) / sizeof(uint8_t);
    int lenHigh_red = lenTotal_red / lenLow_red;
    for (int i = 0; i < lenHigh_red; i++)
    {
        draw_point_color(&handle, red[i], 60, 0, 0);
    }
    image_test(&handle);
}

int i = 0;
void dot()
{
    int lenTotal_flash = sizeof(flash) / sizeof(uint8_t);
    int lenLow_flash = sizeof(flash[0]) / sizeof(uint8_t);
    int lenHigh_flash = lenTotal_flash / lenLow_flash;
    // for (int i=0; i<lenHigh_flash; i++){
    //   draw_point_color(flash[i],100,100,100);
    // }
    // image_test();
    for (int j = 0; j < lenHigh_flash; j++)
    {
        draw_point_color(&handle, flash[j], color[i][0], color[i][1], color[i][2]);
        i++;
        if (i == 7)
        {
            i = 0;
        }
    }
    image_test(&handle);
}

const uint8_t charBlank[8][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}};

const uint8_t heart0[8][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}};

const uint8_t heart1[8][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}};

const uint8_t heart2[8][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {0, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0}};

const uint8_t heart3[8][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {0, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}};

const uint8_t heart4[8][8] = {
    {0, 1, 1, 0, 0, 1, 1, 0},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {0, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}};

static void draw_bitmap_red(uint8_t image[8][8])
{
    disp_show_color(&handle, 0, 0, 0);
    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            if (image[x][y] == 1)
            {
                uint8_t pos[2] = {x, y};
                draw_point_color(&handle, pos, 120, 0, 0);
            }
        }
    }
    image_test(&handle);
}

void heart_animation(void)
{
    draw_bitmap_red(charBlank);
    usleep(1000000);
    draw_bitmap(heart0);
    usleep(100000);
    draw_bitmap(heart1);
    usleep(100000);
    draw_bitmap(heart2);
    usleep(100000);
    draw_bitmap(heart3);
    usleep(100000);
    draw_bitmap(heart4);
    usleep(1000000);
    draw_bitmap(heart3);
    usleep(100000);
    draw_bitmap(heart2);
    usleep(100000);
    draw_bitmap(heart1);
    usleep(100000);
    draw_bitmap(heart0);
    usleep(100000);
}

void fade_color(int speed_usleep, struct HsvColor prev, struct HsvColor next)
{
    for (uint8_t n = 0; n < 255; n++)
    {
        if (prev.h < next.h)
        {
            prev.h++;
        }
        if (prev.s < next.s)
        {
            prev.s++;
        }
        if (prev.v < next.v)
        {
            prev.v++;
        }
        if (prev.h > next.h)
        {
            prev.h--;
        }
        if (prev.s > next.s)
        {
            prev.s--;
        }
        if (prev.v > next.v)
        {
            prev.v--;
        }
        struct RgbColor col = HsvToRgb(prev);
        disp_show_color(&handle, col.r, col.g, col.b);
    }
}

void led_matrix_thread(void *params)
{
    memset(&handle, 0, sizeof(handle));
    RGBMatrixInit(&handle);
    for (;;)
    {
        struct HsvColor current = {0, 0, 0};
        struct HsvColor next = {0, 255, 90};
        fade_color(10000, current, next);

        next = (struct HsvColor){128, 255, 90};
        current = (struct HsvColor){0, 255, 90};
        fade_color(10000, current, next);

        current = (struct HsvColor){128, 255, 90};
        next = (struct HsvColor){0, 0, 0};
        fade_color(10000, current, next);
    }
}

void led_trigger_thread(void *params)
{
    for (;;)
    {
        // PUB_BOOL_FL("dot.ready", true, FL_STICKY);
        usleep(100000);
    }
}
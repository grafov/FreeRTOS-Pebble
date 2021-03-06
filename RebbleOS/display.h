#ifndef __DISPLAY_H
#define __DISPLAY_H

#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "ugui.h"

/*display_done: G9 (in)
display_intn: G10 (in)
display_reset: G15 (out)
display_sclk: G13 (out)

*/

#define DISPLAY_MODE_BOOTLOADER      0
#define DISPLAY_MODE_FULLFAT         1

// todo TYPEDEF ENUM
#define DISPLAY_CMD_DRAW             1
#define DISPLAY_CMD_RESET            2

#define DISPLAY_STATE_BOOTING        0
#define DISPLAY_STATE_FRAME_INIT     1
#define DISPLAY_STATE_FRAME          2
#define DISPLAY_STATE_IDLE           3


#define BLACK 0x0
#define BLUE   0x03
#define GREEN 0x0C
#define RED  0x30


typedef struct {
//    SPI *spi;  // SPI6
    GPIO_TypeDef *PortDisplay;
    uint16_t PinReset;
    uint16_t PinPower;
    uint16_t PinCs;
    uint16_t PinBacklight;
    GPIO_TypeDef *PortBacklight;
    
    uint16_t PinMiso;
    uint16_t PinMosi;
    uint16_t PinSck;
    
    // inputs
    uint16_t PinResetDone;
    uint16_t PinIntn;
    
    
    // stuff from qemu
    uint16_t NumRows;
    uint16_t NumCols;
    uint8_t NumBorderRows;
    uint8_t NumBorderCols;
    
    
    //state
    uint8_t BacklightEnabled;
    uint8_t Brightness;
    uint8_t PowerOn;
    uint8_t State; // busy etc
    uint8_t DisplayMode; // bootloader or full
    
    char DisplayBuffer[24192];
} display_t;


void display_init(void);
void display_done_ISR(uint8_t cmd);
void display_reset(uint8_t enabled);
void display_on();
void display_send_frame();
void backlight_set(uint16_t brightness);
void display_logo(char *frameData);
uint16_t display_checkerboard(char *frameData, uint8_t invert);
void display_cmd(uint8_t cmd, char *data);
void vDisplayISRProcessor(void *pvParameters);
void vDisplayCommandTask(void *pvParameters);

// move to scanline
void scanline_convert_buffer(void);
void scanline_rgb888pixel_to_frambuffer(UG_S16 x, UG_S16 y, UG_COLOR c);

#endif

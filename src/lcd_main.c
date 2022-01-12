#include <stdio.h>
#include "lib/LCD/LCD_1in8.h"
#include "lib/Config/Debug.h"
#include "lib/GUI/GUI_Paint.h"

// Function Declaration
int main(void);
int loop_5ms();
int loop_1ms(UWORD *Image);
int loop_100us();

// Parameters Declaration for drawing dots.
uint16_t x_point = 0;
uint16_t y_point = 0;
uint16_t color_one;
DOT_PIXEL pixel_type;
DOT_STYLE dot_style;


// Drawing Reference code
// Paint_DrawPoint(2, 1, BLACK, DOT_PIXEL_2X2, DOT_FILL_RIGHTUP);
// Paint_DrawLine(10, 5, 40, 36, BLUE, DOT_PIXEL_2X2, LINE_STYLE_SOLID);

bool reserved_addr(uint8_t addr) {
    return (addr & 0x78) == 0 || (addr & 0x78) == 0x78;
}


// Runs other loops.
int main(void)
{
    // Delay Main to let other stuff to properly setup.
    DEV_Delay_ms(100);
    printf("LCD_1in8_main Demo\r\n");
    DEV_Module_Init();

    // LCD Init
    LCD_1IN8_Init(HORIZONTAL);
    LCD_1IN8_Clear(WHITE);
    
    // Set up Image.
    UDOUBLE Imagesize = LCD_1IN8_HEIGHT*LCD_1IN8_WIDTH*2;
    UWORD *BlackImage;
    BlackImage = (UWORD *)malloc(Imagesize);

    // Create a new image cache named BlackImage and fill it with white
    Paint_NewImage((UBYTE *)BlackImage, LCD_1IN8.WIDTH,LCD_1IN8.HEIGHT, 90, WHITE);
    Paint_SetScale(65);
    Paint_Clear(WHITE);
    Paint_SetRotate(ROTATE_90);

    // Wait time to initialize Everything.
    DEV_Delay_ms(2000);

    // Main Loop to refresh the screen.
    while(1) {
        printf("Inside Main loop\n");
        loop_100us();
        loop_1ms(BlackImage);
        loop_5ms();
    }

}

int loop_5ms() {
    
    printf("Inside 5ms loop\n");
    DEV_Delay_ms(5);
}

int loop_1ms(UWORD *Image) {

    printf("Inside 1ms loop\n");


    if(x_point > LCD_1IN8_WIDTH) {
        x_point = 0;
    }
    
    if(y_point > LCD_1IN8_HEIGHT) {
        y_point = 0;
    }

    color_one = BLACK;
    pixel_type = DOT_PIXEL_2X2;
    dot_style = DOT_FILL_RIGHTUP;

    Paint_DrawPoint(x_point, y_point, color_one, pixel_type, dot_style);
    x_point = x_point + 1;
    y_point = y_point + 1;

    LCD_1IN8_Display(Image);
    DEV_Delay_ms(1);
}

int loop_100us() {
    
    printf("Inside 100us loop\n");
    DEV_Delay_us(100);
}
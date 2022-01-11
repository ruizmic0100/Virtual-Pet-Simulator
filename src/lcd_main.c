#include <stdio.h>
#include "lib/LCD/LCD_1in8.h"
#include "lib/Config/Debug.h"
#include "lib/GUI/GUI_Paint.h"

bool reserved_addr(uint8_t addr) {
    return (addr & 0x78) == 0 || (addr & 0x78) == 0x78;
}

int main(void)
{
    DEV_Delay_ms(100);
    printf("LCD_1in8_main Demo\r\n");
    DEV_Module_Init();

    // LCD Init
    LCD_1IN8_Init(HORIZONTAL);
    LCD_1IN8_Clear(WHITE);

    // LCD_SetBacklight(1023)
    UDOUBLE Imagesize = LCD_1IN8_HEIGHT*LCD_1IN8_WIDTH*2;
    UWORD *BlackImage;
    BlackImage = (UWORD *)malloc(Imagesize);

    // Create a new image cache named IMAGE_RGB and fill it with white
    Paint_NewImage((UBYTE *)BlackImage, LCD_1IN8.WIDTH,LCD_1IN8.HEIGHT, 0, WHITE);
    Paint_SetScale(65);
    Paint_Clear(WHITE);
    Paint_SetRotate(ROTATE_0);
    Paint_Clear(WHITE);

    // Drawing
    Paint_DrawPoint(2, 1, BLACK, DOT_PIXEL_2X2, DOT_FILL_RIGHTUP);
    Paint_DrawLine(10, 5, 40, 36, BLUE, DOT_PIXEL_2X2, LINE_STYLE_SOLID);

    LCD_1IN8_Display(BlackImage);
    DEV_Delay_ms(2000);

}
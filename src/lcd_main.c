#include <stdio.h>
#include "../Pico_LCD_code/c/lib/LCD/LCD_1in8.h"
#include "../Pico_LCD_code/c/lib/Config/Debug.h"

bool reserved_addr(uint8_t addr) {
    return (addr & 0x78) == 0 || (addr & 0x78) == 0x78;
}

int main(void)
{
    DEV_Delay_ms(100);
    printf("LCD_1in8_main Demo\r\n");

    return 1;
}
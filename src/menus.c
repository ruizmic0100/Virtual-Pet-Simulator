#include "include/menus.h"
#include "include/character_config.h"
#include "lib/Fonts/fonts.h"
#include "lib/GUI/ImageData.h"
#include "lib/GUI/GUI_Paint.h"

void statsMenuDisplay();
void characterMenuDisplay();

menu_state character_menu = 0;
menu_state inventory_menu = 1;
menu_state stats_menu = 2;

// Display information for stats Menu.
void statsMenuDisplay() {

    Paint_DrawString_EN(1, 1, "Stats", &Font20, WHITE, BLACK); 
    Paint_DrawString_EN(1, 20, "Level", &Font12, WHITE, BLACK); 
    Paint_DrawString_EN(1, 30, "STR", &Font12, WHITE, BLACK); 
    Paint_DrawString_EN(1, 40, "VIT", &Font12, WHITE, BLACK);
    Paint_DrawString_EN(1, 50, "INT", &Font12, WHITE, BLACK);


    Paint_DrawNum(25, 20, Level, &Font12, 0, BLACK, WHITE);
    Paint_DrawNum(25, 30, Strength, &Font12, 0, BLACK, WHITE);
    Paint_DrawNum(25, 40, Vitality, &Font12, 0, BLACK, WHITE);
    Paint_DrawNum(25, 50, Intelligence, &Font12, 0, BLACK, WHITE);

}


// Display main character menu.
void characterMenuDisplay() {

    Paint_DrawRectangle(4, 20, 130, 110, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawNum(25, 50, Level, &Font12, 0, BLACK, WHITE);
    draw_player_character_Standby();
}
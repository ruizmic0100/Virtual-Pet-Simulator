#include "include/menus.h"
#include "lib/Fonts/fonts.h"
#include "lib/GUI/ImageData.h"
#include "lib/GUI/GUI_Paint.h"

void draw_player_character_Standby() {
    Paint_DrawImage(player_character_image_Standby,0,1,20,20);
}
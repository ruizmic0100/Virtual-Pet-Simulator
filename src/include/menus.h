#ifndef MENUS_H
#define MENUS_H
// Defining a menu_state as an int
typedef int menu_state;


// Menu States
menu_state character_menu;
menu_state inventory_menu;
menu_state stats_menu;

void statsMenuDisplay();
void characterMenuDisplay();

#endif
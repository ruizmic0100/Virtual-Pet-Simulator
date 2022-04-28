#include "include/itemlist.h"




// Enum for Item ID's.
enum ItemIdentifier {
	gold
};

// enum for Weapon ID's.
struct WeaponIdentifier {
	int longsword;	
};

// Struct for Long Sword 
struct LongSword {
	int value;
	int level;
	int damage;
};
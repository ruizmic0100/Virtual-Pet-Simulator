#ifndef CHARACTER_CONFIG_H
#define CHARACTER_CONFIG_H

int initializeWarriorStats();

// Definitions for stats.
#define STR 0
#define VIT 0
#define INT 0

// Defining a global_stat as an int.
typedef int global_stat;

// Global Variables.
global_stat Strength;
global_stat Vitality;
global_stat Intelligence;
global_stat Level;

// Struct for Stats
struct WarriorStats {
    int Strength;
    int Vitality;
    int Intelligence;
    int Level;
};

#endif
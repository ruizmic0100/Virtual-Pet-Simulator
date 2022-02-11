#include "include/character_config.h"

// Definitions for stats.
#define STR 0
#define VIT 0
#define INT 0

int initializeWarriorStats();
int increaseStrengthStat();

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


// Stats Can't be zero.
int initializeWarriorStats() {

    struct WarriorStats level_1_stats;
    level_1_stats.Strength = 3;
    level_1_stats.Vitality = 5;
    level_1_stats.Intelligence = 1;
    level_1_stats.Level = 1;
    setWarriorStats(&level_1_stats);
}

int setWarriorStats(struct WarriorStats *stats) {

    Strength = stats->Strength;
    Vitality = stats->Vitality;
    Intelligence = stats->Intelligence;
}

int increaseStrengthStat() {
    Strength = Strength + 1;
}

#include "include/character_config.h"


int initializeWarriorStats();
int increaseStrengthStat();


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

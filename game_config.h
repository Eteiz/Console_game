//
// Created by MrsRo on 27.12.2022.
//

#ifndef CONSOLE_GAME_GAME_CONFIG_H
#define CONSOLE_GAME_GAME_CONFIG_H


using namespace std;

#include <string>

// Player
string player_name;
int player_hp = 100;
int player_hp_max = 100;
int player_def = 0; // Change to 80 when defend option is chosen

int heavy_attack_chance = 20;
int heavy_attack_damage = 30;

int basic_attack_chance = 70;
int basic_attack_damage = 15;

int light_attack_chance = 90;
int light_attack_damage = 7;

int player_heal = 15;
int player_persuasion_chance = 65;

// Enemy
string enemy_name = "THE GUARDIAN";
int enemy_hp = 100;
int enemy_hp_max = 100;
int enemy_persuasion = 0;
int enemy_persuasion_max = 100;
const int enemy_persuasion_factor = 25;

int enemy_chance_for_heal = 10;
int enemy_chance_for_heavy = 30;
int enemy_chance_for_basic = 60;
int enemy_dice = enemy_chance_for_heal + enemy_chance_for_heavy + enemy_chance_for_basic;

int enemy_heal = 15;

int enemy_heavy_attack_chance = 20;
int enemy_heavy_attack_damage = 20;

int enemy_basic_attack_chance = 60;
int enemy_basic_attack_damage = 10;

#endif //CONSOLE_GAME_GAME_CONFIG_H

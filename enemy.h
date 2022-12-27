//
// Created by MrsRo on 27.12.2022.
//

#ifndef CONSOLE_GAME_ENEMY_H
#define CONSOLE_GAME_ENEMY_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include "game_config.h"
#include "layout.h"
#include "dialog.h"

using namespace std;

class Enemy {
private:
    int health = enemy_hp;
    int health_max = enemy_hp_max;

    int persuasion = enemy_persuasion;
    int persuasion_max = enemy_persuasion_max;
    int persuasion_factor = enemy_persuasion_factor;

    vector<char> enemy_layout;
public:
    Enemy() {
        fstream DataFile;
        // NOTE: Text file should be put in cmake-build-debug folder
        DataFile.open("boss.txt", ios::in); // 32x16, begins with x
        if (!DataFile.is_open()) cout << "Unable to load enemy model, check the .txt file";
        string data;

        while (getline(DataFile, data, 'x'));
        for (int a = 0; a < data.size(); a++) {
            if (data[a] != '\n') enemy_layout.push_back(data[a]);
        }
        DataFile.close();
    };

    ~Enemy() { enemy_layout.clear(); }

    void ClearEnemy() { for (int a = 0; a < 512; a++) enemy_layout[a] = ' '; }

    vector<char> GetVector() { return enemy_layout; }

    string GetName() { return enemy_name; }

    void SubHealth(int value) { health -= value; }

    void AddHealth(int value) { health += value; }

    int GetHealth() { return health; }

    int GetMaxHealth() { return health_max; }

    void AddPersuasion(int value) { persuasion += value; }

    void SubPersuasion(int value) { persuasion -= value; }

    int GetPersuasion() { return persuasion; }

    int GetMaxPersuasion() { return persuasion_max; }

    int GetFactorPersuasion() { return persuasion_factor; }
};


class Dialog {
private:
    vector<char> dialog_layout;
    int x_d_size;
    int y_d_size;

public:

    Dialog(int counter) {
        dialog_layout.clear();

        int size = 0;
        for (int a = 0; game_dialog[counter][a] != '\0'; a++) size++;

        x_d_size = size;
        y_d_size = 1;

        for (int a = 0; a < x_d_size; a++) dialog_layout.push_back(game_dialog[counter][a]);
    }

    ~Dialog() { dialog_layout.clear(); }

    vector<char> GetVector() { return dialog_layout; }

    int Get_x() { return x_d_size; }

    int Get_y() { return y_d_size; }
};

#endif //CONSOLE_GAME_ENEMY_H

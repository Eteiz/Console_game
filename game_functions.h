//
// Created by MrsRo on 27.12.2022.
//

#ifndef CONSOLE_GAME_GAME_FUNCTIONS_H
#define CONSOLE_GAME_GAME_FUNCTIONS_H

#include <iostream>
#include <conio.h>
#include <random>
#include <windows.h>
#include <string>

using namespace std;

#include "layout.h"
#include "enemy.h"
#include "game_config.h"


void GameGetch() {
    while (true) {
        unsigned char a = getch();
        if (a == ' ') break;
        else if (tolower(a) == 'q') terminate();
    }
    system("cls");
}

int RandomNumber(int first, int last) {
    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_int_distribution<> distr(first, last); // define the range

    return distr(gen);
}

void GenerateMap_Buttons(Layout main, Layout menu_panel, Layout enemy_panel, Layout button_heavy_atk,
                         Layout button_normal_atk,
                         Layout button_light_atk, Layout button_heal, Layout button_def, Layout button_pers,
                         Enemy nubert) {

    menu_panel.DrawOnLayout(2, 4, 16, 5, button_heavy_atk.GetVector());
    menu_panel.DrawOnLayout(19, 4, 16, 5, button_normal_atk.GetVector());
    menu_panel.DrawOnLayout(36, 4, 16, 5, button_light_atk.GetVector());
    menu_panel.DrawOnLayout(53, 4, 16, 5, button_heal.GetVector());
    menu_panel.DrawOnLayout(70, 4, 16, 5, button_def.GetVector());
    menu_panel.DrawOnLayout(87, 4, 16, 5, button_pers.GetVector());

    main.DrawOnLayout(2, 29, 106, 10, menu_panel.GetVector());
    main.DrawOnLayout(2, 1, 106, 5, enemy_panel.GetVector());
    main.DrawOnLayout(39, 12, 32, 16, nubert.GetVector());
    main.PrintLayout();
}

void GenerateMap_Dialog(Layout main, Layout menu_panel, Layout enemy_panel, Enemy nubert, int dialog_counter) {
    GameGetch();
    main.ResetLayout();
    if (dialog_counter >= 5 && dialog_counter < 23) {
        main.DrawOnLayout(2, 29, 106, 10, menu_panel.GetVector());
        main.DrawOnLayout(2, 1, 106, 5, enemy_panel.GetVector());
    }
    main.DrawOnLayout(39, 12, 32, 16, nubert.GetVector());

    Dialog dialog_panel(dialog_counter);
    main.DrawOnLayout((int) (110 - dialog_panel.GetVector().size()) / 2, 8, dialog_panel.Get_x(), dialog_panel.Get_y(),
                      dialog_panel.GetVector());
    main.PrintLayout();
}

#endif //CONSOLE_GAME_GAME_FUNCTIONS_H

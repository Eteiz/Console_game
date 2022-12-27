#include <iostream>
#include <conio.h>
#include <random>
#include <windows.h>
#include <string>

using namespace std;

#include "layout.h"
#include "enemy.h"
#include "game_config.h"
#include "game_functions.h"

int main() {


    // Setting cmd size
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r); //stores the console's current dimensions

    MoveWindow(console, r.left, r.top, 830, 700, TRUE); // 800 width, 100 height

    // Creating game assets

    enum game_state {
        WIN_PACIFIST,
        WIN_ATTACK,
        LOSE,
        NEITHER
    };

    enum button_state {
        HEAVY_ATTACK,
        NORMAL_ATTACK,
        LIGHT_ATTACK,
        HEAL,
        DEFEND,
        PERSUADE
    };

    enum game_state game = NEITHER;
    enum button_state button;
    enum dialog_state dialog = DIALOG_0;

    Layout main(110, 40, '.');
    Layout menu_panel(106, 10, '#');

    Layout button_heavy_atk(16, 5, 'o'), button_normal_atk(16, 5, 'o'), button_light_atk(16, 5, 'o'),
            button_heal(16, 5, 'o'), button_def(16, 5, 'o'), button_pers(16, 5, 'o');

    button_heavy_atk.AddText(2, 2, "HEAVY ATTACK"); // 12
    button_normal_atk.AddText(2, 2, "BASIC ATTACK"); // 13
    button_light_atk.AddText(2, 2, "LIGHT ATTACK"); // 12
    button_heal.AddText(6, 2, "HEAL"); // 4
    button_def.AddText(5, 2, "DEFEND"); // 6
    button_pers.AddText(4, 2, "PERSUADE"); // 8

    Enemy nubert;
    Layout enemy_panel(106, 5, '#');
    Enemy start;
    start.ClearEnemy();

    //==============================================================

    // STATE: MAIN MENU
    string title = "GAME";
    string controls_1 = "CONTROLS";
    string controls_2 = "x - Click button";
    string controls_3 = "space - Go through dialog/actions";
    string controls_4 = "q - Exit game";
    string controls_5 = "PRESS SPACE TO START";

    main.AddText((110 - (int) title.size()) / 2, 8, title);
    main.AddText((110 - (int) controls_1.size()) / 2, 10, controls_1);
    main.AddText((110 - (int) controls_2.size()) / 2, 12, controls_2);
    main.AddText((110 - (int) controls_3.size()) / 2, 13, controls_3);
    main.AddText((110 - (int) controls_4.size()) / 2, 14, controls_4);
    main.AddText((110 - (int) controls_5.size()) / 2, 17, controls_5);

    main.PrintLayout();

    // STATE: START OF THE GAME
    main.ResetLayout();
    for (int a = 49; a < 60; a++) GenerateMap_Dialog(main, menu_panel, enemy_panel, start, a);

    GameGetch();
    string name_question = "\"What is your name?\"";
    for (int a = 0; a < (550 + (110 - name_question.size()) / 2); a++) cout << ' ';
    cout << name_question;
    for (int a = 0; a <= 110 - name_question.size(); a++) cout << ' ';
    cout << "> ";
    cin >> player_name;
    transform(player_name.begin(), player_name.end(), player_name.begin(), ::toupper);

    //STATE: BATTLE
    while (game == NEITHER) {

        // SUBSTATE: UPDATE OF MAP
        main.ResetLayout();
        button = HEAVY_ATTACK;

        // SUBSTATE: LOADING STATS, BOSS, MENU PANEL
        // Player stats
        string player_stats_1 = "PLAYER: " + player_name;
        string player_stats_2 = "HEALTH: " + to_string(player_hp) + " / " + to_string(player_hp_max);
        // Enemy stats
        string enemy_stats_1 = "ENEMY: " + nubert.GetName();
        string enemy_stats_2 = "HEALTH: " + to_string(nubert.GetHealth()) + " / " + to_string(nubert.GetMaxHealth());
        string enemy_stats_3 =
                "PERSUASION: " + to_string(nubert.GetPersuasion()) + "% / " + to_string(nubert.GetMaxPersuasion()) +
                "%";

        menu_panel.AddText(8, 2, player_stats_1);
        menu_panel.AddText(41, 2, player_stats_2);

        enemy_panel.AddText(8, 2, enemy_stats_1);
        enemy_panel.AddText(41, 2, enemy_stats_2);
        enemy_panel.AddText(74, 2, enemy_stats_3);

        // SUBSTATE: LOADING DIALOG
        switch (dialog) {
            case DIALOG_0: {
                for (int a = 0; a < 5; a++) GenerateMap_Dialog(main, menu_panel, enemy_panel, nubert, a);
                dialog = DIALOG_1;
                break;
            }
            case DIALOG_1: {
                for (int a = 5; a < 8; a++) GenerateMap_Dialog(main, menu_panel, enemy_panel, nubert, a);
                dialog = DIALOG_2;
                break;
            }

            case DIALOG_2: {
                for (int a = 8; a < 11; a++) GenerateMap_Dialog(main, menu_panel, enemy_panel, nubert, a);
                dialog = DIALOG_3;
                break;
            }
            case DIALOG_3: {
                for (int a = 11; a < 15; a++) GenerateMap_Dialog(main, menu_panel, enemy_panel, nubert, a);
                dialog = DIALOG_4;
                break;
            }
            case DIALOG_4: {
                for (int a = 15; a < 20; a++) GenerateMap_Dialog(main, menu_panel, enemy_panel, nubert, a);
                dialog = REST;
                break;
            }
            case REST: {
                int a = RandomNumber(20, 22);
                GenerateMap_Dialog(main, menu_panel, enemy_panel, nubert, a);
            }

        }

        // SUBSTATE: LOADING CHOICE BUTTONS
        GameGetch();
        main.ResetLayout();

        button_heavy_atk.AddText(2, 3, "************");
        button_normal_atk.AddText(2, 3, "             ");
        button_light_atk.AddText(2, 3, "            ");
        button_heal.AddText(6, 3, "    ");
        button_def.AddText(5, 3, "      ");
        button_pers.AddText(4, 3, "        ");

        GenerateMap_Buttons(main, menu_panel, enemy_panel, button_heavy_atk, button_normal_atk, button_light_atk,
                            button_heal, button_def, button_pers, nubert);

        // SUBSTATE: CHOOSING ONE OF OPTIONS
        while (true) {
            unsigned char a = getch();
            if (a == 'x') break;
            else if (a == 0 || a == 0xE0) {

                a = getch();
                if (a == 77) { // RIGHT

                    if (button == HEAVY_ATTACK) {

                        button = NORMAL_ATTACK;
                        system("cls");
                        main.ResetLayout();

                        button_heavy_atk.AddText(2, 3, "            ");
                        button_normal_atk.AddText(2, 3, "************");
                        button_light_atk.AddText(2, 3, "            ");
                        button_heal.AddText(6, 3, "    ");
                        button_def.AddText(5, 3, "      ");
                        button_pers.AddText(4, 3, "        ");

                        GenerateMap_Buttons(main, menu_panel, enemy_panel, button_heavy_atk, button_normal_atk,
                                            button_light_atk, button_heal, button_def, button_pers, nubert);

                    } else if (button == NORMAL_ATTACK) {

                        button = LIGHT_ATTACK;
                        system("cls");
                        main.ResetLayout();

                        button_heavy_atk.AddText(2, 3, "            ");
                        button_normal_atk.AddText(2, 3, "            ");
                        button_light_atk.AddText(2, 3, "************");
                        button_heal.AddText(6, 3, "    ");
                        button_def.AddText(5, 3, "      ");
                        button_pers.AddText(4, 3, "        ");

                        GenerateMap_Buttons(main, menu_panel, enemy_panel, button_heavy_atk, button_normal_atk,
                                            button_light_atk, button_heal, button_def, button_pers, nubert);

                    } else if (button == LIGHT_ATTACK) {

                        button = HEAL;
                        system("cls");
                        main.ResetLayout();

                        button_heavy_atk.AddText(2, 3, "            ");
                        button_normal_atk.AddText(2, 3, "            ");
                        button_light_atk.AddText(2, 3, "            ");
                        button_heal.AddText(6, 3, "****");
                        button_def.AddText(5, 3, "      ");
                        button_pers.AddText(4, 3, "        ");

                        GenerateMap_Buttons(main, menu_panel, enemy_panel, button_heavy_atk, button_normal_atk,
                                            button_light_atk, button_heal, button_def, button_pers, nubert);

                    } else if (button == HEAL) {

                        button = DEFEND;
                        system("cls");
                        main.ResetLayout();

                        button_heavy_atk.AddText(2, 3, "            ");
                        button_normal_atk.AddText(2, 3, "            ");
                        button_light_atk.AddText(2, 3, "            ");
                        button_heal.AddText(6, 3, "    ");
                        button_def.AddText(5, 3, "******");
                        button_pers.AddText(4, 3, "        ");

                        GenerateMap_Buttons(main, menu_panel, enemy_panel, button_heavy_atk, button_normal_atk,
                                            button_light_atk, button_heal, button_def, button_pers, nubert);

                    } else if (button == DEFEND) {

                        button = PERSUADE;
                        system("cls");
                        main.ResetLayout();

                        button_heavy_atk.AddText(2, 3, "            ");
                        button_normal_atk.AddText(2, 3, "            ");
                        button_light_atk.AddText(2, 3, "            ");
                        button_heal.AddText(6, 3, "    ");
                        button_def.AddText(5, 3, "      ");
                        button_pers.AddText(4, 3, "********");

                        GenerateMap_Buttons(main, menu_panel, enemy_panel, button_heavy_atk, button_normal_atk,
                                            button_light_atk, button_heal, button_def, button_pers, nubert);

                    } else if (button == PERSUADE) { continue; }

                } else if (a == 75) { // LEFT

                    if (button == HEAVY_ATTACK) {
                        continue;
                    } else if (button == NORMAL_ATTACK) {

                        button = HEAVY_ATTACK;
                        system("cls");
                        main.ResetLayout();

                        button_heavy_atk.AddText(2, 3, "************");
                        button_normal_atk.AddText(2, 3, "            ");
                        button_light_atk.AddText(2, 3, "            ");
                        button_heal.AddText(6, 3, "    ");
                        button_def.AddText(5, 3, "      ");
                        button_pers.AddText(4, 3, "        ");

                        GenerateMap_Buttons(main, menu_panel, enemy_panel, button_heavy_atk, button_normal_atk,
                                            button_light_atk, button_heal, button_def, button_pers, nubert);

                    } else if (button == LIGHT_ATTACK) {

                        button = NORMAL_ATTACK;
                        system("cls");
                        main.ResetLayout();

                        button_heavy_atk.AddText(2, 3, "            ");
                        button_normal_atk.AddText(2, 3, "************");
                        button_light_atk.AddText(2, 3, "            ");
                        button_heal.AddText(6, 3, "    ");
                        button_def.AddText(5, 3, "      ");
                        button_pers.AddText(4, 3, "        ");

                        GenerateMap_Buttons(main, menu_panel, enemy_panel, button_heavy_atk, button_normal_atk,
                                            button_light_atk, button_heal, button_def, button_pers, nubert);

                    } else if (button == HEAL) {

                        button = LIGHT_ATTACK;
                        system("cls");
                        main.ResetLayout();

                        button_heavy_atk.AddText(2, 3, "            ");
                        button_normal_atk.AddText(2, 3, "            ");
                        button_light_atk.AddText(2, 3, "************");
                        button_heal.AddText(6, 3, "    ");
                        button_def.AddText(5, 3, "      ");
                        button_pers.AddText(4, 3, "        ");

                        GenerateMap_Buttons(main, menu_panel, enemy_panel, button_heavy_atk, button_normal_atk,
                                            button_light_atk, button_heal, button_def, button_pers, nubert);

                    } else if (button == DEFEND) {

                        button = HEAL;
                        system("cls");
                        main.ResetLayout();

                        button_heavy_atk.AddText(2, 3, "            ");
                        button_normal_atk.AddText(2, 3, "            ");
                        button_light_atk.AddText(2, 3, "            ");
                        button_heal.AddText(6, 3, "****");
                        button_def.AddText(5, 3, "      ");
                        button_pers.AddText(4, 3, "        ");

                        GenerateMap_Buttons(main, menu_panel, enemy_panel, button_heavy_atk, button_normal_atk,
                                            button_light_atk, button_heal, button_def, button_pers, nubert);

                    } else if (button == PERSUADE) {

                        button = DEFEND;
                        system("cls");
                        main.ResetLayout();

                        button_heavy_atk.AddText(2, 3, "            ");
                        button_normal_atk.AddText(2, 3, "            ");
                        button_light_atk.AddText(2, 3, "            ");
                        button_heal.AddText(6, 3, "    ");
                        button_def.AddText(5, 3, "******");
                        button_pers.AddText(4, 3, "        ");

                        GenerateMap_Buttons(main, menu_panel, enemy_panel, button_heavy_atk, button_normal_atk,
                                            button_light_atk, button_heal, button_def, button_pers, nubert);
                    }
                } else if (a == 'x' || a == 'X') break;
                else { continue; }
            } else { continue; }
        }

        // STATE: RESOLVING CHOSEN ACTION
        string result_1;
        string result_2;
        string result_3 = " ";

        switch (button) {
            case HEAVY_ATTACK: {
                int dice = RandomNumber(0, 100);
                if (heavy_attack_chance >= dice) {
                    nubert.SubHealth(heavy_attack_damage);
                    result_1 = "You made a powerful swing with your blade aiming perfectly at your enemy";
                    result_2 = "YOU DEALT " + to_string(heavy_attack_damage) + " DMG!";
                } else {
                    result_1 = "You made a powerful swing with blade missing your enemy by millimeters";
                    result_2 = "YOU MISSED!";
                }
                break;
            }
            case NORMAL_ATTACK: {
                int dice = RandomNumber(0, 100);
                if (basic_attack_chance >= dice) {
                    // You dealt
                    nubert.SubHealth(basic_attack_damage);
                    result_1 = "You made a swing with your blade cutting your enemy";
                    result_2 = "YOU DEALT " + to_string(basic_attack_damage) + " DMG!";
                } else {
                    // You missed
                    result_1 = "You made a swing with knife missing your enemy by millimeters";
                    result_2 = "YOU MISSED!";
                }
                break;
            }
            case LIGHT_ATTACK: {
                int dice = RandomNumber(0, 100);

                if (light_attack_chance >= dice) {
                    // You dealt
                    nubert.SubHealth(light_attack_damage);
                    result_1 = "You made a precise push with your blade right into your enemy's body";
                    result_2 = "YOU DEALT " + to_string(light_attack_damage) + " DMG!";
                } else {
                    // You missed
                    result_1 = "You made a careless push with your blade right into your enemy's body";
                    result_2 = "YOU MISSED!";
                }
                break;
            }
            case HEAL: {
                result_1 = "You used herbs found in your pockets to tend your battle wounds";

                if (player_hp == player_hp_max) {
                    result_2 = "You did not need to do that but why not";
                    result_3 = "YOU ARE ALREADY ON FULL HP!";
                } else if (player_hp >= (player_hp_max - player_heal) && player_hp < player_hp_max) {
                    player_hp = player_hp_max;

                    result_2 = "You treated all your wounds for now and are ready for another strike";
                    result_3 = "YOU ARE ON FULL HP!";
                } else {
                    player_hp += player_heal;

                    result_2 = "You still are a bit bruised but you feel a lot better now";
                    result_3 = "YOU HEALED " + to_string(player_heal) + " HP!";
                }
                break;
            }
            case DEFEND: {
                result_1 = "You decided not to attack right this time";
                result_2 = "Your body stiffens ready for enemy's strike";
                result_3 = "THE ENEMY WILL HAVE A LOWER CHANCE TO HIT YOU THIS TIME";
                player_def = 80;
                break;
            }
            case PERSUADE: {

                int dice = RandomNumber(0, 100);
                result_1 = "You tried to tell your enemy that you don't want to fight";
                if (player_persuasion_chance >= dice) {
                    if (nubert.GetPersuasion() != nubert.GetMaxPersuasion())
                        nubert.AddPersuasion(nubert.GetFactorPersuasion());
                    switch (nubert.GetPersuasion()) {
                        //
                        case enemy_persuasion_factor * 2: {
                            result_2 = "You can see them contemplating at what you've said";
                            break;
                        }
                        case enemy_persuasion_factor * 3: {
                            result_2 = "They shake their head as if they are fighting with their thoughts";
                            break;
                        }
                        case enemy_persuasion_factor * 4: {
                            result_2 = "They look at you with sadness on their face and stiffen a little";
                            break;
                        }
                        default: {
                            result_2 = "They heard what you've said and look at you";
                            break;
                        }
                    }
                    result_3 = "PERSUASION WENT SUCCESSFULLY!";
                } else {
                    if (nubert.GetPersuasion() != 0) nubert.SubPersuasion(nubert.GetFactorPersuasion() / 2);
                    result_2 = "They must have understood it wrongly because they look at you with anger";
                    result_3 = "PERSUASION WENT UNSUCCESSFULLY!";
                }
                break;
            }
        }

        system("cls");
        main.AddText((110 - (int) result_1.size()) / 2, 8, result_1);
        main.AddText((110 - (int) result_2.size()) / 2, 9, result_2);
        main.AddText((110 - (int) result_3.size()) / 2, 10, result_3);

        GenerateMap_Buttons(main, menu_panel, enemy_panel, button_heavy_atk, button_normal_atk, button_light_atk,
                            button_heal, button_def, button_pers, nubert);

        // SUBSTATE: CHECKING WIN CONDITIONS - PART 1
        if (nubert.GetPersuasion() >= nubert.GetMaxPersuasion()) game = WIN_PACIFIST;
        else if (nubert.GetHealth() <= 0) game = WIN_ATTACK;

        // SUBSTATE: ENEMY ATTACK
        if (game == NEITHER) {
            int dice = RandomNumber(0, enemy_dice);
            if (dice <= enemy_chance_for_heal && nubert.GetHealth() <= nubert.GetMaxHealth() / 2) { // Healing
                result_1 = "The enemy stops moving suddenly";
                result_2 = "You can see some of his wounds regenerating simultaneously";
                result_3 = "THE ENEMY HEALED " + to_string(enemy_heal) + "HP!";
                nubert.AddHealth(enemy_heal);
            } else if (dice <= enemy_chance_for_heavy && dice > enemy_chance_for_heal) { // Heavy attack

                int dice_2 = RandomNumber(0, enemy_dice);
                result_1 = "The enemy summons glowing orbs around himself";

                if (dice_2 <= enemy_heavy_attack_chance) {
                    if (player_def != 0) {
                        if (dice_2 >= player_def) {
                            result_2 = "Suddenly, they shot them in your direction, painfully piercing through your body and defense";
                            result_3 = "THE ENEMY DEALT " + to_string(enemy_heavy_attack_damage) + " DMG!";
                            player_hp -= enemy_heavy_attack_damage;
                        } else { // Attack is unsuccessful
                            result_2 = "Suddenly, the orbs are heading towards you, fortunately missing";
                            result_3 = "THE ENEMY MISSED!";
                        }
                    } else {

                        result_2 = "Suddenly, they shot them in your direction, piercing through your body";
                        result_3 = "THE ENEMY DEALT " + to_string(enemy_heavy_attack_damage) + " DMG!";
                        player_hp -= enemy_heavy_attack_damage;
                    }
                } else {
                    result_2 = "Suddenly, the orbs are heading towards you, fortunately missing";
                    result_3 = "THE ENEMY MISSED!";
                }
            } else {

                int dice_2 = RandomNumber(0, enemy_dice);
                result_1 = "The eye of the enemy starts glowing stronger and stronger";
                if (dice_2 <= enemy_basic_attack_chance) {
                    if (player_def != 0) {

                        if (dice_2 >= player_def) {
                            result_2 = "It shots a single light beam aiming towards you, piercing through defense and burning you up a little";
                            result_3 = "THE ENEMY DEALT " + to_string(enemy_basic_attack_damage) + " DMG!";
                            player_hp -= enemy_basic_attack_damage;
                        } else {
                            result_2 = "It shots a single light beam aiming towards you, directly above your head";
                            result_3 = "THE ENEMY MISSED!";
                        }
                    } else {
                        result_2 = "It shots a single light beam aiming towards you, burning you up a bit";
                        result_3 = "THE ENEMY DEALT " + to_string(enemy_basic_attack_damage) + " DMG!";
                        player_hp -= enemy_basic_attack_damage;
                    }
                } else {
                    result_2 = "It shots a single light beam aiming towards you, directly above your head";
                    result_3 = "THE ENEMY MISSED!";
                }
            }

            GameGetch();
            main.ResetLayout();

            main.AddText((110 - (int) result_1.size()) / 2, 8, result_1);
            main.AddText((110 - (int) result_2.size()) / 2, 9, result_2);
            main.AddText((110 - (int) result_3.size()) / 2, 10, result_3);

            GenerateMap_Buttons(main, menu_panel, enemy_panel, button_heavy_atk, button_normal_atk, button_light_atk,
                                button_heal, button_def, button_pers, nubert);
        }
            // SUBSTATE: CHECKING WIN CONDITIONS - PART 2
        else if (game == WIN_ATTACK)
            for (int a = 23; a < 36; a++)
                GenerateMap_Dialog(main, menu_panel, enemy_panel, nubert, a);
        else if (game == WIN_PACIFIST)
            for (int a = 36; a < 48; a++)
                GenerateMap_Dialog(main, menu_panel, enemy_panel, nubert, a);

        // SUBSTATE: CHECKING LOSE CONDITIONS
        if (player_hp <= 0) game = LOSE;
    }
    // STATE: ENDING
    if (game == LOSE) {

        main.ResetLayout();
        string lose_text_1 = "The enemy strikes the final blow, hitting you right in the chest";
        string lose_text_2 = "Your weaken, almost lifeless body, falls on the ground";
        string lose_text_3 = "As you are losing consciousness, you wish you could go back in time and try again";

        main.AddText((110 - (int) lose_text_1.size()) / 2, 8, lose_text_1);
        main.AddText((110 - (int) lose_text_2.size()) / 2, 9, lose_text_2);
        main.AddText((110 - (int) lose_text_3.size()) / 2, 10, lose_text_3);

        main.PrintLayout();
    } else if (game == WIN_ATTACK || game == WIN_PACIFIST) {
        nubert.ClearEnemy();
        for (int a = 60; a < 70; a++) GenerateMap_Dialog(main, menu_panel, enemy_panel, nubert, a);
    }

    GameGetch();
    return 0;
}
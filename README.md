# Console_game
This is my first project - turn-based game made on Windows Console inspired by Undertale and Earthbound mechanics.
As Windows does not have its own version of Unix's ncurses library (aside from PDCurses), I decided to make use of available functions such as system("cls) and getch().
The game uses char vector which is a layout of points on which other elements of menu are drawn and loaded. After a step the layout is resetted, elements are drawn on it again, the console is cleared, the layout is printed and so on. The player go to next dialogue line or action by pressing *space*. When action buttons pops up, the player can move between them using *right and left arrow* and confirming its choice by clicking *x*.

## Game mechanics
After a enemy's dialogue, player can choose one of actions they can do on their turn. Each action has a precentage chance of succeeding (**bolded values can be mostly changed in game_config.h**):
1. HEAVY ATTACK - deals **30** health points to enemy (**20% of success**)
2. BASIC ATTACK - deals **15** health points to enemy (**70% of success**)
3. LIGHT ATTACK - deals **7** health points to enemy (**90% of success**)
4. HEAL - heals player for **15** health points (**100% of success**)
5. DEFEND - enemy's attack now have **20%** of success (**100% of success**)
6. PERSUADE - if succeed, increase Persuasion Meter by **25%**, if fails, decrease Persuasion Meter by **13%** (half of success' %) (**65% of success**)

Next, the program checks if winning conditions are met:
1. WIN_ATTACK - enemy's health dropped (or below) to 0
2. WIN_PACIFIST - enemy's Persuation Meter is at 100%

After that, it's enemy's turn. The enemy can make one of 3 choices, they have fixed chance that they will be chosen and have precentage chance of succeeding (**bolded values can be mostly changed in game_config.h**):
1. HEAL - enemy heals for **15** health points (**10% for happening, 100% of success**)
2. HEAVY ATTACK - deals **30** health points to player (**30% for happening, 20% of success**)
3. BASIC ATTACK - deals **15** health points to player (**60% for happening, 60% of success**)

Next, the program again checks if winning conditions are met and the type of victory or if player's health has dropped to 0 (LOSE). If player wins, the enemy says its last dialogue, the ending is generated and game closes. If player lost, the ending screen is generated and game closes. If neither of conditions are met, the game still runs and new turn begins.

## Enemy's model and dialogue
Enemy's model is a .txt file **32x16 pixels** which starts with letter **x** for loading purposes and can be changed. The .txt file is located in the same folder as .exe file (in this case `cmake-build-debug`)
```
x             XXXXX              
        XXXXXXXXXXXXXX          
      XXXXXXXXXXXXXXXXXX        
     XXXXXXXXXXXXXXXXXXXX       
    XXXXXXX       XXXXXXXXX     
   XXXXXXX         XX XXXXXX    
   XXXXXXX           XXXXXXX    
  XXXXXXX             XXXXXX    
  XXXXXXXX           XXXXXXX    
  XXXXXX XX         XXXXXXXX    
 XXXXXXXXXXXX  X   XXXXXXXXXX   
 XXXXXXXXXX  XXXXXXXXXXXXXXXX   
 XXXXXX  XXXXXXXXXXX  XXXXXX    
  XXXXX   XXXXXXXXX X  XXXX     
   XX      X XXXXX      X   X   
  X   X    X X XX     X         
```
The game's dialogue cannot really be changed (like adding or deleting lines) as it would require adding new states to `enum dialog_state` and new dialogue lines in `char game_dialog[][150]`. The lines are displayed on screen with for loops which are set to stop at exact indexes: 
```
case DIALOG_3: {
                for (int a = 11; a < 15; a++) GenerateMap_Dialog(main, menu_panel, enemy_panel, nubert, a);
                dialog = DIALOG_4;
                break;
}
```
## Potential future fixes
Here's the list of things that can be improved if given more time or had more experience. I do not intend to fully commit to changing anything stated below as the game is somewhat playable, except for balance.

- [ ] Balance the chance of success
- [ ] Balance damage statistics, presuasion statictics
- [ ] Reading dialogue from file
- [ ] Possibility to dynamically add and delete lines for dialogue phases
- [ ] Dialogue lines change automatically after 3 seconds, the waiting can be skipped with pressing *space*
- [ ] Chance of success are displayed above buttons

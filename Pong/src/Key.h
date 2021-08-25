#pragma once
extern int menuIndex;
extern int gameOver;
extern int players;

void initKeyboard();
//this method detects the keyboard and mouse, and updates the action of a determined key of Pause menu
void detectKeyPause();
//this method detects the keyboard, mouse, and updates the action of a determined key of the Game menu with 1 player
void detectKeyGame_1();
//this method detects the keyboard, mouse, and updates the action of a determined key of the Game menu with 2 players
void detectKeyGame_2();
//this method detects the keyboard, mouse, and updates the action of a determined key of the Start menu
void detectKeyStart();
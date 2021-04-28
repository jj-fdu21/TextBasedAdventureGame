
#pragma once
#include <iostream>
#include <string>
#include <cstdlib>


using namespace std;


void mainMenu();
int inputValidation(int, int, int);
void gameIntro(int);
int convertToInt(string);
void playerOne();
void getHealth();
void getInventory();
void setDamage(int);
void setHeal(int);
void gameScenarioSelections();
void gameScenarioSouth();
void gameScenarioEast();
void gameScenarioWest();
void gameScenarioNorth();
void enemyEncounter();
void enemyDamage();
void getHelp();
void timeProgress();
void durabilityDecrease();
void durabilityIncrease();
void findFlashlight();
void findJetpack();
void findBatteries();
void findFuel();
void checkMap();
void collapsedCave();
void findTrailMix();
void useTrailMix();
void soggySinkhole();
void fatalForest();
void monkeyCombat();
void elephantCombat();
void camoCave();
//commented out due to error in trailmix branch can be placed back afterwards 
void mapDisplay();


#pragma once
#include <iostream>
#include <string>
#include <cstdlib>


using namespace std;

//player class needs o be expanded upon with ways to immplement the health to be shown and affected
class Player
{
private:
	int health;
public:
	Player()
	{
		health = 50;
	}
};
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
void checkMap();
void durabilityDecrease();
void durabilityIncrease();
void findFlashlight();
void findJetpack();
void findBatteries();
void findFuel();
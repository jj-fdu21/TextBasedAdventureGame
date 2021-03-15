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
void setDamage(int);
void setHeal(int);



#include "txtGameHeader.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <Windows.h>
#include <limits>
#include <math.h>
using namespace std;

string version = "1.0.0";
int health = 90;

void mainMenu() {
	//starting menu of choices
	string menuChoice;

	cout << "\t\t\t\t\t     ESCAPE FROM THE JUNGLE " << endl;
	cout << "\t\t\t\t\t        Version " + version << endl;
	cout << "\t\t\t\t\t-----------------------------\n" << endl;
	cout << "\t\t\t\t\t      (1) Start New Game" << endl;

	cout << "\t\t\t\t\t      (0) Quit" << endl;

	cin >> menuChoice;

	int input = convertToInt(menuChoice); //input validation
	input = trunc(input);
	input = inputValidation(input, 0, 1);
	if(input==1){
		cout << "Player chosen to start new game" << endl;
	}
	else if (input == 0) {
		cout << "\nGood Bye come again!!\n" << endl;		//end game
		Sleep(3000);
		_Exit(10);
	}
}
void gameIntro(int startingMode) {
	if (startingMode == 1) {		//intro
		cout << "Greetings Survivor, ";
		Sleep(1000);
		cout << "You are the only Survivor of a plane crash and the environment around you is a jungle.\nYou managed to recover some items from the plane's wreckage.\n";
		Sleep(1000);
		cout << "One of the items being a map showing the nearest settlement\nbeing about 500 miles from your location and a backpack to carry some items.\n";
		Sleep(1000);
		cout << "Unfortunately, some important items to your survival were\nscattered across the jungle during the crash. The jungle is a dangerous place to travel,\nbeware of day and night creatures lurking.";
		Sleep(1000);
		cout << " You need to recover most of the scattered items to make the journey to safety\nApproximately 3 days to get to your destination.";
		Sleep(1000);
		cout << "\nChoose your items and path wisely, Survivor, and good luck." << endl << endl;
		system("pause");
	}
}

	int convertToInt(string input) 
	{
		/* checks if input is a number, and converts it to an int */

		int stringCounter = 1;

		while (stringCounter != 0) {
			stringCounter = 0;

			for (int i = 0; i < input.length(); i++) {
				if (!isdigit(input[i]) && input[i] != '.') {
					stringCounter++;
				}
			}

			if (stringCounter != 0) {
				cout << "Invalid Input. Please Re-Enter your Selection" << endl;
				cin.ignore();
				cin >> input;
			}
		}
		int choice = stoi(input);
		return choice;
	}
	void playerOne() {
		cout << "\n-----------------------------" << endl;
		cout << " PLAYER ONE HAS STARTED GAME" << endl;
		cout << "-----------------------------\n" << endl;

		gameIntro(1);

	}
	int inputValidation(int input, int min, int max) {
		/* checks if input is within valid range */

		while (input < min || input > max) {
			string menuChoice;

			cout << "Invalid Input." << endl;
			cout << "Please enter a number between " << min << " and " << max << endl;

			cin.ignore();
			cin >> menuChoice;
			input = convertToInt(menuChoice);
		}
		return input;
	}
	void setDamage(int damage)
	{
		health = health - damage;
	}
	void setHeal(int heal)
	{
		health = health + heal;
	}
	bool checkDeath()
	{
		if (health <= 0)
		{
			return true;
		}
		return false;
	}
	void getHealth()
	{
		checkDeath();
		if (100 >= health && health >= 76)
		{
			system("CLS");
			system("Color 0A");
			cout << "Health: Excellent || Current Percentage: " << health << "%" <<endl;
			system("pause");
			system("Color 0F");
		}
		if (56 <= health && health <= 75)
		{
			system("CLS");
			system("Color 0E");
			cout << "Health: Lethargic || Current Percentage: " << health << "%" << endl;	
			system("pause");
			system("Color 0F");
		}
		if (1 <= health && health <= 55)
		{
			system("CLS");
			system("Color 0C");
			cout << "Health: Critical || Current Percentage: " << health << "%" << endl;		
			system("pause");
			system("Color 0F");
			
		}
		if (checkDeath())
		{
			system("CLS");
			cout << "You have died! Please play again!" << endl;
			system("pause");
		}
	}
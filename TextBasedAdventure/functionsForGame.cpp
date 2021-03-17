#include "txtGameHeader.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <Windows.h>
#include <limits>
#include <math.h>
#include <algorithm>
using namespace std;

string version = "1.0.0", input, input1;
int health = 90;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
int k;
enum direction { N, S, E, W, I, H ,n,s,e,w,h,i};
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
void gameScenarioSelections()
{
	cout << "Enter The Direction you would like to explore (N, S, E, W) or Input H to view Health or I to view Inventory: " << endl;
	cin >> input;
	if (input == "S" || input == "s")
	{
		cout << "You have selected South" << endl;
		gameScenarioSouth();
	}
	if (input == "W" || input == "w")
	{
		cout << "You have selected West" << endl;
		gameScenarioSouth();
	}
	if (input == "E" || input == "e")
	{
		cout << "You have selected East" << endl;
		gameScenarioSouth();
	}
	if (input == "N" || input == "n")
	{
		cout << "You have selected North" << endl;
		gameScenarioSouth();
	}
	if (input == "H" || input == "h")
	{
		getHealth();
	}
	if (input == "I" || input == "i")
	{
		getInventory();
	}
	else
	{
		cout << "You didn't enter a valid selection, please select again." << endl;
		gameScenarioSelections();
	}
}

void gameScenarioSouth()
{
	cout << "This Function is further being worked on and isn't fully implemeted." << endl;
	system("pause");
}
void gameScenarioWest()
{
	cout << "This Function is further being worked on and isn't fully implemeted." << endl;
	system("pause");
}
void gameScenarioEast()
{
	cout << "This Function is further being worked on and isn't fully implemeted." << endl;
	system("pause");
}
void gameScenarioNorth()
{
	cout << "This Function is further being worked on and isn't fully implemeted." << endl;
	system("pause");
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
			SetConsoleTextAttribute(hConsole, 2);
			cout << "Health: Excellent || Current Percentage: " << health << "%" <<endl;
			SetConsoleTextAttribute(hConsole, 7);
			system("pause");
		}
		if (56 <= health && health <= 75)
		{
			SetConsoleTextAttribute(hConsole, 6);
			cout << "Health: Lethargic || Current Percentage: " << health << "%" << endl;	
			SetConsoleTextAttribute(hConsole, 7);
			system("pause");
		}
		if (1 <= health && health <= 55)
		{
			SetConsoleTextAttribute(hConsole, 4);
			cout << "Health: Critical || Current Percentage: " << health << "%" << endl;		
			SetConsoleTextAttribute(hConsole, 7);
			system("pause");
		}
		if (checkDeath())
		{
			SetConsoleTextAttribute(hConsole, 4);
			cout << "You have died! Please play again!" << endl;
			SetConsoleTextAttribute(hConsole, 7);
			system("pause");
		}
	}
	void getInventory()
	{
		cout << "Your Inventory: Flashlight , Pocket Knife , Water Canteen" << endl;
		system("pause");
	}
#include "txtGameHeader.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <limits>
#include <math.h>
#include <time.h>
#include <algorithm>
#define NOMINMAX
#include <Windows.h>
using namespace std;

string version = "2.0.0", input, input1;
int health = 90, temp;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
enum direction { N, S, E, W, I, H, Q, n, s, e, w, h, i, q, R, r, D, d, Help, help };
int selections = 0;

int a[5][5] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24 };
int xmap = 1; int ymap = 3; int maplocation = a[ymap][xmap];//map coordination creation
string items[] = { "Water Canteen", "Pocket Knife", "Flashlight", "Jetpack", "Map", "Batteries", "Fuel" };
int itemChecks[] = { 0,0,0,0,0,0,0 };
int durabilities[] = { 0,0,0,0 };
void mainMenu() {
	//starting menu of choices
	string menuChoice;

	cout << "\t\t\t\t\t     ESCAPE FROM THE JUNGLE " << endl;
	cout << "\t\t\t\t\t        Version " + version << endl;
	cout << "\t\t\t\t\t-----------------------------\n" << endl;
	cout << "\t\t\t\t\t      (1) Start New Game" << endl;

	cout << "\t\t\t\t\t      (0) Quit" << endl;
	cout << "Enter choice here: ";
	cin >> menuChoice;

	int input = convertToInt(menuChoice); //input validation
	input = trunc(input);
	input = inputValidation(input, 0, 1);
	if (input == 1) {
		cout << "Player chosen to start new game" << endl;
	}
	else if (input == 0) {
		cout << "\nGood Bye come again!!\n" << endl;		//end game
		Sleep(3000);
		_Exit(10);
	}
}
void gameStartInventory()
{
	itemChecks[0] = 1;
	itemChecks[1] = 1;
	itemChecks[4] = 1;
	durabilities[0] = 50;
	durabilities[1] = 100;
	getInventory();
}
void gameIntro(int startingMode) {
	if (startingMode == 1) {		//intro
		cout << "Greetings Survivor, ";
		Sleep(1000);
		cout << "You are the only Survivor of a plane crash and \nthe environment around you is a jungle. You managed to recover some\nitems from the plane's wreckage. ";
		Sleep(1000);
		cout << "One of the items being a map showing\nthe nearest settlement being about 500 miles from your location\nand a backpack to carry some items.";
		Sleep(1000);
		cout << "Unfortunately, Your Batteries, Flashlight, Fuel and Jetpack\nwere scattered across the jungle during the crash.\nThe jungle is a dangerous place to travel, beware of day and night\ncreatures lurking.";
		Sleep(1000);
		cout << "You need to recover most of the scattered items\nto make the journey to safety. \nApproximately 3 days to get to your destination.";
		Sleep(1000);
		cout << "\nGood Luck Survivor! You'll need it.\n(Type help for assistance)" << endl << endl;
		gameStartInventory();
	}
}
//intro game selction inquery to user
void gameScenarioSelections()
{
	cout << "\nEnter The Direction you would like to explore (N, S, E, W), \nInput (H) to view Health, or (I) to view Inventory items: " << endl;
	cin >> input;
	if (input == "Q" || input == "q") {
		cout << "\nGood Bye come again!!\n" << endl;		//end game
		Sleep(3000);
		_Exit(10);
	}
	if (input == "S" || input == "s")
	{
		//cout << "You have selected South" << endl;
		if (ymap <= 0)
		{
			cout << "Towards the South is a dense fog, whispers surrounding you pray that you don't head in," << endl << "taking this as a sign you choose to tread another direction." << endl;
			gameScenarioSelections();
		}
		else
		{
			gameScenarioSouth();
			selections++;
			timeProgress();
			gameScenarioSelections();
		}
	}
	if (input == "R" || input == "r")
	{
		cout << "You have selected Restore Durability" << endl;
		durabilityIncrease();
		gameScenarioSelections();
	}
	if (input == "D" || input == "d")
	{
		cout << "You have selected Decrease Durability" << endl;
		durabilityDecrease();
		gameScenarioSelections();
	}
	if (input == "W" || input == "w")
	{
		//cout << "You have selected West" << endl;
		if (xmap <= 0)
		{
			cout << "Towards the West there is a very steep gigantic mountain," << endl << "it seems impossible to climb, you must choose another direction." << endl;
			gameScenarioSelections();
		}
		else
		{
			gameScenarioWest();
			selections++;
			timeProgress();
			gameScenarioSelections();
		}
	}
	if (input == "E" || input == "e")
	{
		//cout << "You have selected East" << endl;
		if (xmap >= 4)
		{
			cout << "Towards the East there is what seems to be a never ending ocean," << endl << "not too far you can see shark's fins as they circle around the coast," << endl << "you have chosen to stay in one piece and choose another direction." << endl;
			gameScenarioSelections();
		}
		else
		{
			gameScenarioEast();
			selections++;
			timeProgress();
			gameScenarioSelections();
		}
	}
	if (input == "N" || input == "n")
	{
		//cout << "You have selected North" << endl;
		if (ymap >= 4)
		{
			cout << "Towards the North there is a giant ravine that looks impossible to cross," << endl << "you have to choose another direction to head." << endl;
			gameScenarioSelections();
		}
		else
		{
			gameScenarioNorth();
			selections++;
			timeProgress();
			gameScenarioSelections();
		}
	}
	if (input == "H" || input == "h")
	{
		getHealth();
		gameScenarioSelections();
	}
	if (input == "I" || input == "i")
	{
		getInventory();
		gameScenarioSelections();
	}
	if (input == "X" || input == "x")
	{
		enemyEncounter();
		gameScenarioSelections();
	}
	if (input == "Help" || input == "help")
	{
		getHelp();
	}
	else
	{
		cout << "You didn't enter a valid selection, please select again. Or to quit game select (Q)" << endl;
		gameScenarioSelections();
	}
}

//these gameScenarios are to be implmented with scences upon the users selection of which direction to head for safety.
void gameScenarioSouth()
{
	ymap--;
	cout << "\nYou have chosen to head South," << endl;
	checkMap();
	system("pause");
}
void gameScenarioWest()
{
	xmap--;
	cout << "\nYou have chosen to head West," << endl;
	checkMap();
	system("pause");
}
void gameScenarioEast()
{
	xmap++;
	cout << "\nYou have chosen to head East," << endl;
	checkMap();
	system("pause");
}
void gameScenarioNorth()
{
	ymap++;
	cout << "\nYou have chosen to head North," << endl;
	checkMap();
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
//intro screen of game when user has selected to start game
void playerOne() {
	cout << "\n-----------------------------" << endl;
	cout << " PLAYER ONE HAS STARTED GAME" << endl;
	cout << "-----------------------------\n" << endl;

	gameIntro(1);

}
int inputValidation(int input, int min, int max) {
	/* checks if input is within valid range  for starting menu*/

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
//fcn seves to calculate th dammage to health inflicted by an enemy
void setDamage(int damage)
{
	health = health - damage;
}
//fcn if user encounters some food or water their health will increase
void setHeal(int heal)
{
	health = health + heal;
}
//fcn serves to show user dead or not
bool checkDeath()
{
	if (health <= 0)
	{
		SetConsoleTextAttribute(hConsole, 4);
		cout << "You have died! Please play again!" << endl;
		SetConsoleTextAttribute(hConsole, 7);
		Sleep(2000);
		_Exit(0);
	}
	return false;
}
/*
* Functionality is to verify the users health bar and to
later be used to tell if user is alive or not
*/
void getHealth()
{
	if (health > 100)
	{
		health = 100;
	}
	if (100 >= health && health >= 76)
	{
		SetConsoleTextAttribute(hConsole, 2);
		cout << "Health: Excellent || Current Percentage: " << health << "%" << endl;
		SetConsoleTextAttribute(hConsole, 7);
		system("pause");
	}
	if (56 <= health && health <= 75)
	{
		SetConsoleTextAttribute(hConsole, 6);//color changing 
		cout << "Health: Lethargic || Current Percentage: " << health << "%" << endl;
		SetConsoleTextAttribute(hConsole, 7);
		system("pause");
	}
	if (1 <= health && health <= 55)
	{
		SetConsoleTextAttribute(hConsole, 4);//color changing 
		cout << "Health: Critical || Current Percentage: " << health << "%" << endl;
		SetConsoleTextAttribute(hConsole, 7);
		system("pause");
	}
}
//this function serves as a way to give a help section to the user.
void getHelp()
{
	int selection;
	SetConsoleTextAttribute(hConsole, 11);
	cout << "======================================================================================================================" << endl;
	cout << "\t\t\t\t\t HELP MENU" << endl;
	cout << "======================================================================================================================" << endl;
	cout << "\t\t\t\t\t Select which aspect of the game you need help with:" << endl;
	cout << "\t\t\t\t\t 1. How to Move." << endl;
	cout << "\t\t\t\t\t 2. How to see Health." << endl;
	cout << "\t\t\t\t\t 3. How to see Inventory." << endl;
	cout << "\t\t\t\t\t 4. Any Advice?" << endl;
	cout << "\t\t\t\t\t 0. Quit Help" << endl;
	cout << "\t\t\t\t\t Enter Selection: ";
	cin >> selection;
	if (cin.fail())
	{
		SetConsoleTextAttribute(hConsole, 7);
		cout << "\t\t\t Invalid input for Help Selection, please try again." << endl;
		system("pause");
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		getHelp();
	}
	if (selection == 0)
	{
		cout << endl;
		cout << "\t\t\t Selected Exit." << endl;
		cout << "\t\t\t Use Help to come back if you ever need!" << endl;
		SetConsoleTextAttribute(hConsole, 7);
		system("pause");
		gameScenarioSelections();
	}
	if (selection == 1)
	{
		cout << endl;
		cout << "\t\t\t Selected Movement Help." << endl;
		cout << "\t\t\t To move in game use N , S , E , W corresponding to the direction you want to travel." << endl;
		cout << "\t\t\t Going too far in one direction will cause you to eventually turn back so be careful." << endl;
		cout << "\t\t\t To be able to travel during the night, you will need a Flashlight and some Batteries." << endl;
		SetConsoleTextAttribute(hConsole, 7);
		system("pause");
		getHelp();
	}
	if (selection == 2)
	{
		cout << endl;
		cout << "\t\t\t Selected Health Help." << endl;
		cout << "\t\t\t To view your health , simply type H to be able to view it." << endl;
		SetConsoleTextAttribute(hConsole, 7);
		system("pause");
		getHelp();
	}
	if (selection == 3)
	{
		cout << endl;
		cout << "\t\t\t Selected Inventory Help." << endl;
		cout << "\t\t\t To view your inventory , simply type I to be able to view it." << endl;
		SetConsoleTextAttribute(hConsole, 7);
		system("pause");
		getHelp();
	}
	if (selection == 4)
	{
		cout << endl;
		cout << "\t\t\t Selected Advice." << endl;
		cout << "\t\t\t Survivor, there are creatures lurking in the jungle. Tread carefully." << endl;
		cout << "\t\t\t Be on the lookout for possible item pickups that may be handy later." << endl;
		SetConsoleTextAttribute(hConsole, 7);
		system("pause");
		getHelp();
	}
	else
	{
		SetConsoleTextAttribute(hConsole, 7);
		cout << "\t\t\t Invalid input for Help Selection, please try again." << endl;
		system("pause");
		getHelp();
	}
}
void durabilityDecrease()
{
	int durabilityDecreaseValue, durability;
	cout << "Enter the amount you would like to decrease the Pocket Knife's durability by: ";
	cin >> durabilityDecreaseValue;
	if (cin.fail() || durabilityDecreaseValue < 0)
	{
		SetConsoleTextAttribute(hConsole, 7);
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Invalid input for durability decrease, please re-enter your value." << endl;
		system("pause");
		durabilityIncrease();
	}
	durability = durabilities[1] - durabilityDecreaseValue;
	durabilities[1] = durability;
}
void durabilityIncrease()
{
	int durabilityIncreaseValue, durability;
	cout << "Enter the amount you would like to increase the Pocket Knife's durability by: ";
	cin >> durabilityIncreaseValue;
	if (cin.fail() || durabilityIncreaseValue < 0)
	{
		SetConsoleTextAttribute(hConsole, 7);
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Invalid input for durability decrease, please re-enter your value." << endl;
		system("pause");
		durabilityIncrease();
	}
	durability = durabilities[1] + durabilityIncreaseValue;
	durabilities[1] = durability;
}
//this function serves as a way to access the inventory 
void getInventory()
{
	cout << "======================================================================================================================" << endl;
	cout << "\t\t\t\t\t\t INVENTORY" << endl;
	cout << "======================================================================================================================" << endl;
	for (int i = 0; i < sizeof(itemChecks); i++)
	{
		if (itemChecks[i] == 1)
		{
			cout << "\t\t\t\t\t\t" << items[i];
			if (i < 4)
			{
				if (durabilities[i] > 100)
				{
					durabilities[i] = 100;
				}
				if (100 >= durabilities[i] && durabilities[i] >= 76)
				{
					SetConsoleTextAttribute(hConsole, 2);
					cout << " [" << durabilities[i] << "]" << endl;
					SetConsoleTextAttribute(hConsole, 7);
				}
				if (56 <= durabilities[i] && durabilities[i] <= 75)
				{
					SetConsoleTextAttribute(hConsole, 6);//color changing 
					cout << " [" << durabilities[i] << "]" << endl;
					SetConsoleTextAttribute(hConsole, 7);
				}
				if (1 <= durabilities[i] && durabilities[i] <= 55)
				{
					SetConsoleTextAttribute(hConsole, 4);//color changing 
					cout << " [" << durabilities[i] << "]" << endl;
					SetConsoleTextAttribute(hConsole, 7);
				}
				if (durabilities[i] < 1)
				{
					SetConsoleTextAttribute(hConsole, 15);
					cout << " [Destroyed]" << endl;
					SetConsoleTextAttribute(hConsole, 7);
					durabilities[i] = 0;
				}
			}
		}
	}
	cout << endl;
	//SetConsoleTextAttribute(hConsole, 11);//color changing 
	//cout << "Your Inventory: (1) Pocket Knife , (2) Water Canteen , (3) Map" << endl;
	//SetConsoleTextAttribute(hConsole, 7);
	//system("pause");
}
//This fcn serves to randomly give a user an enemy to face after every game 
void enemyEncounter()
{
	string enemies[] = { "Poison Frog", "Snake", "Monkey", "Gorilla", "Elephant" };
	srand(time(0));
	int enemySelected = rand() % 2;
	cout << "You have encounted a " << enemies[enemySelected] << "!" << endl;
	cout << "You don't defend yourself and it attacks you!" << endl;
	enemyDamage();
}
// this funcion is used to determine the about of damage an enemy can inflict on health
void enemyDamage()
{
	srand(time(0));
	int damageAmount = rand() % 25 + 1;
	health = health - damageAmount;
	cout << "You have taken " << damageAmount << " damage to your health" << endl << endl;
	checkDeath();
}

void timeProgress()
{
	if (selections == 4)
	{
		cout << endl;
		cout << "The sun is high in the sky... Morning has arrived" << endl;
		cout << endl;
	}
	else if (selections == 8)
	{
		cout << endl;
		cout << "The sun is starting to set... Nighttime will soon come" << endl;
		cout << endl;
	}
	else if (selections == 12)
	{
		cout << endl;
		cout << "The darkness has covered the sky... It is Nighttime." << endl;
		cout << endl;
	}
	else if (selections == 16)
	{
		cout << endl;
		cout << "The sun is beginning to rise... Morning will soon come" << endl;
		cout << endl;
		selections = 0;
	}
}

void checkMap()
{
	//int maplocation = a[ymap][xmap];
	if (maplocation = 0)
	{
		cout << "You have arrived at the _, what will you do?" << endl;
		findFlashlight();
	}
	else if (maplocation = 1)
	{
		cout << "You have arrived at the _, what will you do?" << endl;
		findBatteries();

	}
	else if (maplocation = 2)
	{
		cout << "You have arrived at the _, what will you do?" << endl;
		findJetpack();

	}
	else if (maplocation = 3)
	{
		cout << "You have arrived at the _, what will you do?" << endl;
		findFuel();

	}
	else if (maplocation = 4)
	{
		cout << "You have arrived at the _, what will you do?" << endl;
		cout << "WHAT THE FUCK?????? :)" << endl;

	}
	else if (maplocation = 5)
	{
		cout << "You have arrived at the _, what will you do?" << endl;
		
	}
	else if (maplocation = 6)
	{
		cout << "You have arrived at the Camouflaged Cove," << "almost impossible to spot at first glance you distinguish" << endl << "the different fauna covering the opening from the cavern itself," << endl << "what will you do?" << endl;
		
	}
	else if (maplocation = 7)
	{
		cout << "You have arrived at the _, what will you do?" << endl;
		findJetpack();
	}
	else if (maplocation = 8)
	{
		cout << "You have arrived at the Soggy Sinkhole, what will you do?" << endl;
		
	}
	else if (maplocation = 9)
	{
		cout << "You have arrived at the Rugged River, what will you do?" << endl;
		
	}
	else if (maplocation = 10)
	{
		cout << "You have arrived at the _, what will you do?" << endl;
		
	}
	else if (maplocation = 11)
	{
		cout << "You have arrived at the _, what will you do?" << endl;
		
	}
	else if (maplocation = 12)
	{
		cout << "You have arrived at the _, what will you do?" << endl;
		
	}
	else if (maplocation = 13)
	{
		cout << "You have arrived at the Treasure Chest, what will you do?" << endl;
		
	}
	else if (maplocation = 14)
	{
		cout << "You have arrived at the _, what will you do?" << endl;
		
	}
	else if (maplocation = 15)
	{
		cout << "You have arrived at the _, what will you do?" << endl;
		findJetpack();
	}
	else if (maplocation = 16)
	{
		cout << "You have arrived at the Crash Site," << endl << "reminants of machines as well as the hole are laid before you," << endl << "what will you do?" << endl;
		findJetpack();
	}
	else if (maplocation = 17)
	{
		cout << "You have arrived at the _, what will you do?" << endl;
		findJetpack();
	}
	else if (maplocation = 18)
	{
		cout << "You have arrived at the _, what will you do?" << endl;
		findJetpack();
	}
	else if (maplocation = 19)
	{
		cout << "You have arrived at the _, what will you do?" << endl;
		findJetpack();
	}
	else if (maplocation = 20)
	{
		cout << "You have arrived at the Cosmic Cave, what will you do?" << endl;
		findFuel();
	}
	else if (maplocation = 21)
	{
		cout << "You have arrived at the _, what will you do?" << endl;
		findFuel();
	}
	else if (maplocation = 22)
	{
		cout << "You have arrived at the _, what will you do?" << endl;
		findFuel();
	}
	else if (maplocation = 23)
	{
		cout << "You have arrived at the Fatal Forest, what will you do?" << endl;
		findFuel();
	}
	else if (maplocation = 24)
	{
		cout << "You have arrived at the _, what will you do?" << endl;
		findFuel();
	}
	else
	{
		cout << "Location cannot be found, location reseting to crash site, please wait..." << endl;
		xmap = 1; ymap = 3; maplocation = a[ymap][xmap];
		checkMap();
	}
}

void findFlashlight()
{
	cout << "You have found a flashlight on the ground." << endl;
	itemChecks[2] = 1;
	durabilities[2] = 100;
	cout << "Flashlight has been added to your inventory." << endl;
}
void findJetpack()
{
	cout << "You have found a jetpack on the ground." << endl;
	itemChecks[3] = 1;
	durabilities[3] = 100;
	cout << "Jetpack has been added to your inventory." << endl;
}
void findBatteries()
{
	cout << "You have found batteries for a flashlight on the ground." << endl;
	itemChecks[5] = 1;
	cout << "Flashlight batteries has been added to your inventory." << endl;
}
void findFuel()
{
	cout << "You have found some jetpack fuel." << endl;
	itemChecks[6] = 1;
	cout << "Jetpack fuel has been added to your inventory." << endl;
}
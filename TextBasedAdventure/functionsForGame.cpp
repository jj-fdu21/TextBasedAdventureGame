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


string version = "4.0.0", input, username;
int a[5][5] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24 };
int health = 90, amountOfMix = 0, flashlightOnOffCheck = -1, selections = 0, xmap = 1, ymap = 3, maplocation = a[ymap][xmap];;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
enum direction { N, S, E, W, I, H, Q, n, s, e, w, h, i, q, R, r, D, d, Help, help };
string items[] = { "Water Canteen", "Pocket Knife", "Flashlight", "Jetpack", "Map", "Batteries", "Fuel", "Trail Mix" };
int itemChecks[] = { 0,0,0,0,0,0,0,0 };
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
		cout << "Player enter Username: ";
		cin >> username;
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
	system("pause");
}
void gameIntro(int startingMode) {
	if (startingMode == 1) {		//intro
		cout << "Greetings " << username << ", ";
		Sleep(1000);
		cout << "You are the only Survivor of a plane crash and \nthe environment around you is a jungle. You managed to recover some\nitems from the plane's wreckage. ";
		Sleep(1000);
		cout << "One of the items being a map showing\nthe nearest settlement being about 500 miles from your location\nand a backpack to carry some items.";
		Sleep(1000);
		cout << " Unfortunately, Your Batteries, Flashlight, Fuel and Jetpack\nwere scattered across the jungle during the crash.\nThe jungle is a dangerous place to travel, beware of day and night\ncreatures lurking.";
		Sleep(1000);
		cout << "You need to recover most of the scattered items\nto make the journey to safety. \nApproximately 3 days to get to your destination.";
		Sleep(1000);

		cout << "\nGood Luck " << username << "!" << " You'll need it.\n(Type help for assistance)" << endl << endl;

		gameStartInventory();
		checkMap();
	}
}
//intro game selction inquery to user
void gameScenarioSelections()
{
	cout << "\nEnter The Direction you would like to explore (N, S, E, W), \nInput (H) to view Health, (M) to display your Map \nor (I) to view Inventory items: " << endl;
	cin >> input;
	if (input == "Q" || input == "q") {
		cout << "\nGood Bye come again!!\n" << endl;		//end game
		Sleep(3000);
		_Exit(10);
	}
	if (input == "S" || input == "s")
	{
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
	if (input == "M" || input == "m")
	{
		mapDisplay();
		gameScenarioSelections();
	}
	if (input == "W" || input == "w")
	{
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
	if (input == "On" || input == "on")
	{
		if (durabilities[2] >= 1)
		{
			cout << "The Flashlight has been turned on" << endl;
		}
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
void flashlightOnOff()
{
	if (durabilities[2] >= 1 && flashlightOnOffCheck == 0)
	{
		cout << "The Flashlight is now turned on" << endl;
		flashlightOnOffCheck = 1;
		gameScenarioSelections();
	}
	if (durabilities[2] >= 1 && flashlightOnOffCheck == 1)
	{
		cout << "The Flashlight is now turned off" << endl;
		durabilities[2] = durabilities[2] - 5;
		flashlightOnOffCheck = 0;
		gameScenarioSelections();
	}
	if (durabilities[2] <= 1)
	{
		cout << "Unfortunately, the flashlight doesn't seem to have enough battery power" << endl;
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
		cout << "\t\t\t " << username << ", there are creatures lurking in the jungle. Tread carefully." << endl;
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
//This function is used to decrease the durability of items
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
//This function is used to increase durability of items
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
//this function serves as a way to access the inventory and checks for certain actions
void getInventory()
{

	cout << "======================================================================================================================" << endl;
	cout << "\t\t\t\t\t\t INVENTORY" << endl;
	cout << "======================================================================================================================" << endl;
	for (int i = 0; i < sizeof(itemChecks); i++)
	{
		if (itemChecks[i] == 1)
		{
			cout << endl;
			cout << "\t\t\t\t\t\t" << items[i];
			if (items[i] == "Trail Mix")
			{
				cout << " [" << amountOfMix << "]";
			}
			if (i < 4)
			{
				if (durabilities[i] > 100)
				{
					durabilities[i] = 100;
				}
				if (100 >= durabilities[i] && durabilities[i] >= 76)
				{
					SetConsoleTextAttribute(hConsole, 2);
					cout << " [" << durabilities[i] << "%]";
					SetConsoleTextAttribute(hConsole, 7);
				}
				if (56 <= durabilities[i] && durabilities[i] <= 75)
				{
					SetConsoleTextAttribute(hConsole, 6);//color changing 
					cout << " [" << durabilities[i] << "%]";
					SetConsoleTextAttribute(hConsole, 7);
				}
				if (1 <= durabilities[i] && durabilities[i] <= 55)
				{
					SetConsoleTextAttribute(hConsole, 4);//color changing 
					cout << " [" << durabilities[i] << "%]";
					SetConsoleTextAttribute(hConsole, 7);
				}
				if (durabilities[i] < 1 && (items[i] == "Flashlight" || items[i] == "Jetpack"))
				{
					SetConsoleTextAttribute(hConsole, 15);
					cout << " [Missing Component]";
					SetConsoleTextAttribute(hConsole, 7);
					durabilities[i] = 0;
				}
				if (durabilities[i] < 1 && (items[i] == "Water Canteen" || items[i] == "Pocket Knife"))
				{
					SetConsoleTextAttribute(hConsole, 15);
					cout << " [Destroyed]";
					SetConsoleTextAttribute(hConsole, 7);
					durabilities[i] = 0;
				}
				//if (durabilities[4] > -1 && items[i] == "Trail Mix")
				//{
				//	SetConsoleTextAttribute(hConsole, 2);
				//	cout << " [" << durabilities[4] << "]";
				//	SetConsoleTextAttribute(hConsole, 7);
				//}

			}
		}
	}

	cout << endl;
	if (itemChecks[2] == 1 && itemChecks[5] == 1)
	{
		string selection;
		cout << endl << "It seems you have Batteries for that Flashlight, Would you like to put them in the Flashlight? (Yes/No)" << endl;
		cin >> selection;
		if (selection == "yes" || selection == "Yes")
		{
			cout << "Batteries have been inserted into the Flashlight. It seems to be able to give off light now." << endl;
			durabilities[2] = 100;
			itemChecks[5] = 0;
			flashlightOnOffCheck = 0;
		}
	}
	if (itemChecks[3] == 1 && itemChecks[6] == 1)
	{
		string selection;
		cout << "It seems you have Fuel for that Jetpack, Would you like to put it in the Jetpack? (Yes/No)" << endl;
		cin >> selection;
		if (selection == "yes" || selection == "Yes")
		{
			cout << "Fuel have been inserted into the Jetpack. It seems to be able to be used now" << endl;
			durabilities[3] = 100;
			itemChecks[6] = 0;
		}
	}
	if (amountOfMix > 0)
	{
		string selection;
		cout << "Would you like to eat some trail mix to regenerate some health? (Yes/No)" << endl;
		cin >> selection;
		if (selection == "yes" || selection == "Yes")
		{
			useTrailMix();
		}
	}
	if (itemChecks[2] == 1 && itemChecks[5] == 0 && flashlightOnOffCheck == 0)
	{
		string selection;
		cout << "Would you like to turn On your Flashlight? (Yes/No)" << endl;
		cin >> selection;
		if (selection == "yes" || selection == "Yes")
		{
			flashlightOnOff();
		}
	}
	if (itemChecks[2] == 1 && itemChecks[5] == 0 && flashlightOnOffCheck == 1)
	{
		string selection;
		cout << "Would you like to turn Off your Flashlight? (Yes/No)" << endl;
		cin >> selection;
		if (selection == "yes" || selection == "Yes")
		{
			flashlightOnOff();
		}
	}
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
//Function to progress time in game, used for day and nightcycles.
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
void camoCave() //built in choices for camoflauge cove
{
	char choice;
	cin >> choice;
	if (choice == '1')
	{
		cout << endl << "After entering the cave, there is just enough sunlight for you to see a puddle of fresh water," << endl << " likely from the last big rain."
			<< endl << "Do you wish to drink it? 1 for yes, 2 for no." << endl;
		cin >> choice;
		if (choice == '1')
		{
			cout << endl << "You begin to drink the water and then continue to look around the cove." << endl;
			health =+ 10;
		}
		else if (choice == '2')
		{
			cout << endl << "You have chosen not to drink the water, you continue to look around the cove." << endl;
		}
		else
		{
			cout << endl << "A invalid input was given, you have decided not to drink the water, you continue to look around the cove." << endl;
		}
		cout << endl << "As the cove continues deeper in, it gets to dark to continue, a flashlight would be perfect for the situation" << endl;
		cout << "Press 1 to try to use a flashlight, and press 2 to rather leave." << endl; cin >> choice;
		if (choice == '1')
		{
			if (choice == '1' && itemChecks[2] == 1 && durabilities[2] >= 5)
			{
				durabilities[2] =- 5;
				cout << endl << "Your flashlight has proven to be valuable because as you shine it towards the back of the cave," << endl << " you see a small natural waterfall." << endl;
				if (itemChecks[1] == 1)
				{
					durabilities[1] = 100;
					cout << endl << "You refilled your waterbottle using the waterfall." << endl;
				}
			}
			if (choice == '1' && itemChecks[2] == 1 && durabilities[2] < 5)
			{
				cout << endl << "Although you have a flashlight, you do not have enough" << endl << " power to continue down the cove, you turn back.";
			}
			if (choice == '1' && itemChecks[2] == 0)
			{
				cout << endl << "Missing a flashlight, you are unable to proceed further" << endl << " so you leave the cove.";
			}
			if (choice == '2')
			{
				cout << endl << "Being unable to see, you stumble back out, scraping your legs as you continue." << endl;
				health =- 10;
				checkDeath();
			}
			else
			{
				cout << endl << "Being unable to see, you stumble back out, scraping your legs as you continue." << endl;
				health =- 15;
				checkDeath();
			}
		}
		if (choice == '2')
		{
			cout << endl << "You chose not to continue further in, going back out you choose where to go next." << endl;
			health =- 10;
			checkDeath();
		}
		else
		{
			cout << endl << "You did not go further in, going back out you choose where to go next." << endl;
			health =- 15;
			checkDeath();
		}
	}
	else if (choice == '2')
	{
		cout << endl << "Although searching the cave could have been dangerous, it may have had much needed supplies. Just remember that where there is risk there is reward." << endl;
		//health =- 15;
	}
	else
	{
		cout << endl << "a invalid input was given, please try again." << endl;
		camoCave();
	}
}
//This function is used to check the map and see where the player is and display it to them.
void checkMap()
{
	int maplocation = a[ymap][xmap];
	if (maplocation == 0)
	{

		cout << "You have arrived at the 0, what will you do?" << endl;

		static bool itemFlag = false;
		if (!itemFlag)
		{
			findBatteries();
			itemFlag = true;
		}
	}
	else if (maplocation == 1)
	{
		snakeCombat();
	}
	else if (maplocation == 2)
	{
		static bool itemFlag = false;
		if (!itemFlag)
		{
			findTrailMix();
		}		
	}
	else if (maplocation == 3)
	{
		cout << "You have arrived at the Soggy Sinkhole" << endl;
		soggySinkhole();
	}
	else if (maplocation == 4)
	{
		victoryScenario();
	}
	else if (maplocation == 5)
	{
		static bool itemFlag = false;
		if (!itemFlag)
		{
			findFuel();
			itemFlag = true;
		}
	}
	else if (maplocation == 6)
	{
	   cout << endl << "After walking in the jungle, your feet begin to drag and you are thirsty."
			<< endl << "As you begin to hallucinate you trip over a large green vine,"
			<< endl << "and your head smashes against the moist dirt."
			<< endl << "As you pick your head up you see that there is a small hole,"
			<< endl << "slightly bigger than your body length that you would be able to fit in."
			<< endl << "You are now sitting at the entrance to the Camouflaged Cove."
			<< endl << "Entering the cove may prove to be deadly,"
			<< endl << "but may also provide you with various survival necessities."
			<< endl << "Don't forget to check you inventory for items to help you."
			<< endl << "Press 1 to enter the cove or press 2 to keep moving." << endl;
		camoCave();
		
	}
	else if (maplocation == 7)
	{
		static bool itemFlag = false;
		if (!itemFlag)
		{
			findBatteries();
			itemFlag = true;
		}
	}
	else if (maplocation == 8)
	{
		gorillaCombat();
	}
	else if (maplocation == 9)
	{
		ruggedRiver();
	}
	else if (maplocation == 10)
	{
		static bool itemFlag = false;
		if (!itemFlag)
		{
			findTrailMix();
		}
	}
	else if (maplocation == 11)
	{
		static bool itemFlag = false;
		if (!itemFlag)
		{
			findFlashlight();
			itemFlag = true;
		}
	}
	else if (maplocation == 12)
	{
		cout << "You have arrived at the 12, what will you do?" << endl;
		
	}
	else if (maplocation == 13)
	{
		cout << "You have arrived at the Treasure Chest, what will you do?" << endl;
	}
	else if (maplocation == 14)
	{
		static bool itemFlag = false;
		if (!itemFlag)
		{
			findTrailMix();
		}
	}
	else if (maplocation == 15)
	{
	static bool itemFlag = false;
		if (!itemFlag)
		{
			findBatteries();
			itemFlag = true;
		}
	}
	else if (maplocation == 16)
	{
		cout << "You have arrived at the Crash Site," << endl << "reminants of machines as well as the hole are laid before you," << endl << "what will you do?" << endl;
	}
	else if (maplocation == 17)
	{
		static bool combatFlag = false;
		if (!combatFlag)
		{
			combatFlag = true;
			elephantCombat();			
		}
	}
	else if (maplocation == 18)
	{
		static bool itemFlag = false;
    
		cout << "You have arrived at the 19, what will you do?" << endl;

		if (!itemFlag)
		{
			findFuel();
			itemFlag = true;
		}
	}
	else if (maplocation == 19)
	{
		static bool combatFlag = false;
		cout << "You have arrived at the 24, what will you do?" << endl;

		if (!combatFlag)
		{
			combatFlag = true;
			monkeyCombat();
		}
	}
	else if (maplocation == 20)
	{
		cout << "You have arrived at the Collapsed Cave, It seems to be a huge gap that perhaps you can fly over with something." << endl;
		cout << "However, You also see a path that leads around the gap. It seems long and will probably take a toll on your health." << endl;
		cout << "Which option would you like to take?" << endl;
		collapsedCave();
	}
	else if (maplocation == 21)
	{
		poisonFrogCombat();
	}
	else if (maplocation == 22)
	{
		static bool itemFlag = false;
		if (!itemFlag)
		{
			findFuel();
			itemFlag = true;
		}

	}
	else if (maplocation == 23)
	{
		cout << "You have arrived at the Fatal Forest, It seems to be a huge forest with a dreaded storm over top." << endl;
		cout << "You could trek through the storm all the way through or attempt to find some shelter deep in the forest" << endl;
		cout << "What would you like to do? " << endl;
		fatalForest();
	}
	else if (maplocation == 24)
	{
		static bool itemFlag = false;

		cout << "You have arrived at the 18, what will you do?" << endl;

		if (!itemFlag)
		{
			findJetpack();
			itemFlag = true;
		}
	}
	else
	{
		cout << "Location cannot be found, location reseting to crash site, please wait..." << endl;
		xmap = 1; ymap = 3; maplocation = a[ymap][xmap];
		checkMap();
	}
}
//This function allows the player to find the flashlight and add it to their inventory
void findFlashlight()
{
	cout << "You have found a flashlight on the ground." << endl;
	itemChecks[2] = 1;
	cout << "Flashlight has been added to your inventory." << endl;
}
//This function allows the player to find the jetpack and add it to their inventory
void findJetpack()
{
	cout << "You have found a jetpack on the ground." << endl;
	itemChecks[3] = 1;
	cout << "Jetpack has been added to your inventory." << endl;
}
void findTrailMix()
{
	cout << "You have found some trail mix on the ground." << endl;
	itemChecks[7] = 1;
	amountOfMix += 1;
	//itemChecks[4] =  1;
	//durabilities[4] = durabilities[4] + 1;
	cout << "Trail Mix has been added to your inventory." << endl;
}
//This function allows the player to find the flashlight batteries and add it to their inventory.
void findBatteries()
{
	cout << "You have found batteries for a flashlight on the ground." << endl;
	itemChecks[5] = 1;
	cout << "Flashlight batteries has been added to your inventory." << endl;
}
//This function allows the player to find the jetpack fuel and add it to their inventory.
void findFuel()
{
	cout << "You have found some jetpack fuel." << endl;
	itemChecks[6] = 1;
	cout << "Jetpack fuel has been added to your inventory." << endl;
}
void useTrailMix()
{
	if (health == 100)
	{
		cout << "Your health is already full, eating the trail mix will serve no purpose." << endl;
		gameScenarioSelections();
	}
	cout << "You have consumed some trail mix. " << endl;
	health = health + 15;
	cout << "You have lost a trail mix in your inventory. " << endl;
	amountOfMix -= 1;

}
void elephantCombat()
{
	int selection;
	cout << "You have encountered an Elephant!!! What are you going to do?" << endl;
	cout << "It doesn't seem to be hostile (at first)" << endl;
	cout << "1. Threaten the Elephant To Have It Leave" << endl;
	cout << "2. Walk Away" << endl;
	cin >> selection;
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Invalid input for Combat Selection, the game will re-prompt you." << endl;
		system("pause");
		elephantCombat();
	}
	if (selection == 1)
	{
		int damage = rand() % 25 + 30;
		cout << "The Elephant seems unthreatened but is now angry, it decides to hurl a tree at you." << endl;
		cout << "The Elephant deals " << damage << " damage to you" << endl;
		health -= damage;
		checkDeath();
		gameScenarioSelections();
	}
	if (selection == 2)
	{
		int outcome = rand() % 2 + 1;
		if (outcome == 1)
		{
			cout << "You decide to walk around away from the Elephant, was probably the best decision since it didn't notice" << endl;
			gameScenarioSelections();
		}
		if (outcome == 2)
		{
			cout << "The Elephant notices you trying to sneak around, and it doesn't like that." << endl;
			cout << "The Elephant rages into a stomping tantrum, you have been crushed." << endl;
			health = 0;
			Sleep(2000);
			checkDeath();
		}
		if (outcome != 1 && outcome != 2)
		{
			cout << "Invalid input for Combat Selection, the game will re-prompt you." << endl;
			system("pause");
			elephantCombat();
		}
	}
	if (selection != 1 && selection != 2)
	{
		cout << "Invalid input for Combat Selection, the game will re-prompt you." << endl;
		system("pause");
		elephantCombat();
	}
}

void fatalForest()
{
	cout << "1. Seek shelter" << endl;
	cout << "2. Continue walking" << endl;
	int selection;
  	cin >> selection;
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  cout << "Invalid input for Scenario Selection, the game will re-prompt you." << endl;
		system("pause");
		fatalForest();
	}
	if (selection == 1)
	{
		cout << "You have chosen to seek shelter." << endl;
		cout << "You found a small cave that gives you enough shelter from the coming storm. You decide to rest here. This will give you the strength to move forward." << endl;
		if (health < 50 && amountOfMix > 0)
		{
			string selection;
			cout << "Your health seems to be low, would you like to consume some trail mix? (Yes/No)" << endl;
			cin >> selection;
			if (selection == "Yes" || selection == "yes")
			{
				useTrailMix();
			}
			if (selection != "Yes" && selection != "yes")
			{
				cout << "You decide to save your trail mix for later, but your health is looking dangerous." << endl;
			}
			gameScenarioSelections();
		}
		gameScenarioSelections();
	}
	else if (selection == 2)
	{
		cout << "You have decided to continue walking." << endl;
		cout << "The storm is very heavy and the inclimate weather has a very bad effect on your health." << endl;
		health -= 15;
		checkDeath();
		gameScenarioSelections();
	}
	if (selection != 1 && selection != 2)
	{
		cout << "Invalid input for Scenario Selection, the game will re-prompt you." << endl;
		system("pause");
		fatalForest();
	}
}


void monkeyCombat()
{
	int selection;
	cout << "You have encountered a Monkey!!!" << endl;
	cout << "It seems like it wants to steal your backpack. What are you going to do?" << endl;
	cout << "1. Splash the Monkey with water to scare him off" << endl;
	cout << "2. Sneak past" << endl;

	cin >> selection;
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Invalid input for Combat Selection, the game will re-prompt you." << endl;
		system("pause");
		monkeyCombat();
	}
	if (selection == 1 && durabilities[0] >= 10)
	{
		cout << "You have splashed the Monkey with water from your canteen. It ran away back into the trees." << endl;
		cout << "You suffered no damage, but you did lose some of your remaining water." << endl;
		durabilities[0] -= 10;
		gameScenarioSelections();
	}
	if (selection == 1 && durabilities[0] <= 10)
	{
		cout << "You look into your canteen and it seems like you don't have enough water to pose any threat." << endl;
		cout << "It leaves you with no other option except sneaking around." << endl;
		cout << "You decide to try and sneak by the monkey carefully navigating through leaves and twigs." << endl;
		cout << "A twig snaps and the Monkey notices you, and it aggressively attacks you" << endl;
		cout << "You sprint but the Monkey is too fast and it grabs your water canteen during your fight and runs off." << endl;
		cout << "You have lost your water canteen and also have taken some damage to your health." << endl;
		itemChecks[0] = 0;
		health -= 10;
		checkDeath();
		gameScenarioSelections();
	}
	if (selection == 2)
	{
			cout << "You decide to try and sneak by the monkey carefully navigating through leaves and twigs." << endl;
			cout << "A twig snaps and the Monkey notices you, and it aggressively attacks you" << endl;
			cout << "You sprint but the Monkey is too fast and it grabs your water canteen during your fight and runs off." << endl;
			cout << "You have lost your water canteen and also have taken some damage to your health." << endl;
			itemChecks[0] = 0;
			health -= 10;
			checkDeath();
			gameScenarioSelections();
	}
	if (selection != 1 && selection != 2)
	{
		cout << "Invalid input for Combat Selection, the game will re-prompt you." << endl;
		system("pause");
		monkeyCombat();
	}

}
void gorillaCombat()
{
	int selection;
	cout << "You keep moving and all of a sudden you hear banging and agressively yelling." << endl;
	cout << "You wonder what it could possibly be and so you quietly advance towards the noise" << endl;
	cout << "Upon getting closer you realize that it's a huge Gorilla and he notices you" << endl;
	cout << "The Gorilla doesn't seem happy to see you and you couldn't be more scared" << endl; 
	cout << "What action are you going to take against the Gorilla" << endl;
	cout << "1. Fight the Gorilla with your Pocket Knife." << endl;
	cout << "2. Play Dead" << endl;
	cout << "What do you choose?: ";
	cin >> selection;
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Invalid input for Combat Selection, the game will re-prompt you." << endl;
		system("pause");
		gorillaCombat();
	}
	if (selection == 1)
	{
		cout << "You've decided to fight the Gorilla with your knife" << endl;
		cout << "Not a very good idea...." << endl;
		cout << "After a long intense fight, the Gorilla wins and deals some hefty damage to you." << endl;
		cout << "Your Pocket Knife also suffers from the battle." << endl;
		health -= 30;
		durabilities[1] -= 40;
		checkDeath();
		gameScenarioSelections();
	}
	if (selection == 2)
	{
		int selectiontoo;
		cout << "You decided to play dead, you lie down and the Gorilla moves towards you." << endl;
		cout << "It slightly wacks you because it doesn't buy your act, you lose some health." << endl;
		cout << "What will you do now?" << endl;
		health -= 15;
		checkDeath();

		cout << "1. Continue playing dead" << endl;
		cout << "2. Get up and attempt to run" << endl;;

		cout << "What do you choose?: ";
		cin >> selectiontoo;
		if (selectiontoo == 1)
		{
			cout << "Smart choice, since you didn't react to getting hit the Gorilla buys it." << endl;
			cout << "The Gorilla goes away and you then make your escape." << endl;
			gameScenarioSelections();
		}
		if (selectiontoo == 2)
		{
			cout << "You decide to get up and attempt to run." << endl;
			cout << "The Gorilla easily catches you without challenge and throws you into a river." << endl;
			cout << "You take hefty health damage, but at least the Gorilla is gone." << endl;
			health -= 25;
			checkDeath();
			gameScenarioSelections();
		}
		if (selectiontoo != 1 && selectiontoo != 2)
		{
			cout << "You entered an invalid selection. The game will re-prompt you." << endl;
			system("pause");
			gorillaCombat();
		}
	}
	if (selection != 1 && selection != 2)
	{
		cout << "You entered an invalid selection. The game will re-prompt you." << endl;
		system("pause");
		gorillaCombat();
	}
}
void snakeCombat()
{
	int selection;
	cout << "You are walking when all of a sudden you hear the movement of leaves very close" << endl;
	cout << "You look down and you see a venomous snake, you gotta act fast" << endl;
	cout << "What action will you take against the snake?" << endl;
	cout << "1. Attack the Snake" << endl;
	cout << "2. Run away from the Snake" << endl;
	cin >> selection;
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Invalid input for Combat Selection, the game will re-prompt you." << endl;
		system("pause");
		snakeCombat();
	}
	if (selection == 1)
	{
		cout << "You decide to pull out your Pocket Knife and lunge at the snake" << endl;
		cout << "You manuver very carefully to avoid possible danger, but you get bit anyways." << endl;
		cout << "You stab the snake in the head seizing it's movement, and luckily the bite wasn't all too bad" << endl;
		cout << "The Pocket Knife seems fine, but it seems you took a bit a damage." << endl;
		health -= 15;
		checkDeath();
		gameScenarioSelections();
	}
	if (selection == 2)
	{
		cout << "You try to escape the snake, but something you may not know." << endl;
		cout << "Snakes are pretty fast, and so you barely get anywhere before you are caught and bit bad on your leg" << endl;
		cout << "You are poisoned and are required to rest for a bit, taking major health damage from the venom before it" << endl;
		cout << "wears off you." << endl;
		health -= 75;
		checkDeath();
		gameScenarioSelections();
	}
	if (selection != 1 && selection != 2)
	{
		cout << "You entered an invalid selection. The game will re-prompt you." << endl;
		system("pause");
		snakeCombat();
	}
}
void poisonFrogCombat()
{
	int selection;
	cout << "You come across a small outcove of water that seems good to rest at" << endl;
	cout << "However in the distance you notice a bright colorful frog, and on a closer look" << endl;
	cout << "you see many more of these frogs. You know that they are poisonous and will not be fun" << endl;
	cout << "One ends up directly next to you on a leaf. Act fast or else it's not gonna be good." << endl;
	cout << "What action will you take against the Poisonous Frog? " << endl;
	cout << "1. Choose to attack the Frog" << endl;
	cout << "2. Run Away from the area" << endl;
	cin >> selection;
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Invalid input for Combat Selection, the game will re-prompt you." << endl;
		system("pause");
		poisonFrogCombat();

	}
	if (selection == 1)
	{
		cout << "You decided to lunge at the frog with your knife, but the frog was too fast." << endl;
		cout << "The Frog jumps onto your arm and poisons you very fast without any time to do anything." << endl;
		cout << "Poisoned, you get away from the area but suffer lots of damage from the lasting effects." << endl;
		health -= 35;
		checkDeath();
		gameScenarioSelections();
	}
	if (selection == 2)
	{
		cout << "You decide to run away from the poisonous frog infested area" << endl;
		cout << "Luckily you get away unscathed, but you should avoid going back there" << endl;
		gameScenarioSelections();
	}
	if (selection != 1 && selection != 2)
	{
		cout << "You entered an invalid selection. The game will re-prompt you." << endl;
		system("pause");
		poisonFrogCombat();
	}
}
//This function simulates the collapsed cave scenario
void collapsedCave()
{
	int selection;
	cout << "1. Fly across the gap with a jetpack" << endl;
	cout << "2. Take the long path around." << endl;
	cin >> selection;
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Invalid input for Scenario Selection, the game will re-prompt you." << endl;
		system("pause");
		collapsedCave();
	}
	if ((selection == 1 && itemChecks[3] == 1) && durabilities[3] > 15)
	{
		cout << "You have decided to fly over the gap. Although, you have used 15% of your Jetpacks fuel" << endl;
		durabilities[3] = durabilities[3] - 15;
	}
	if ((selection == 1 && itemChecks[3] == 1) && durabilities[3] < 15)
	{
		cout << "You have decided to fly over the gap. However, you don't have enough fuel to fully cross." << endl;
		cout << "You fall into the gap and die tragically." << endl;
		health = 0;
		checkDeath();
	}
	if (selection == 1 && itemChecks[3] == 0)
	{
		cout << "You don't have a way to fly across. You'll have to walk around." << endl;
		system("pause");
		collapsedCave();
	}
	if (selection == 1 && itemChecks[3] == 1 && durabilities[3] == 0)
	{
		cout << "You seem to have a Jetpack but no fuel in it. You're going to have to go around." << endl;
		system("pause");
		collapsedCave();
	}
	if (selection == 2)
	{
		cout << "You have decided to walk the path around the gap. Although safer than flying across, you have lost 15%" << endl << " of your health due to the longevity of the path." << endl;
		health = health - 15;
		if (health < 50 && amountOfMix > 0)
		{
			string selection;
			cout << "Your health seems to be low, would you like to consume some trail mix? (Yes/No)" << endl;
			cin >> selection;
			if (selection == "Yes" || selection == "yes")
			{
				useTrailMix();
			}
			if (selection == "No" || selection == "no")
			{
				cout << "You decide to save your trail mix for later, but your health is looking dangerous." << endl;
			}
			gameScenarioSelections();
		}
		if (health < 50)
		{
			cout << "Your health seems to be low, but you have no food. You should search for some so you can stay alive." << endl;
			gameScenarioSelections();
		}
		else
		{
			cout << "Your health is in good shape, you'll be safe for a while longer." << endl;
			gameScenarioSelections();
		}
	}
	if (selection != 1 && selection != 2)
	{
		cout << "You entered an invalid selection. The game will re-prompt you." << endl;
		system("pause");
		collapsedCave();
	}

}
void soggySinkhole()
{
	int selection;
	cout << "You come across a large area with bubbling sand that looks crossable, " << endl << "however, you also see a thick brush filled with mud" << endl;
	cout << "Your options are thin, and consist of either attempting to cross the hole of bubbling sand " << endl << "or walk through the thick brush." << endl;
	cout << "Choose your Way: " << endl;
	cout << "1. Cross the Sinkhole" << endl;
	cout << "2. Walk towards the thick brush" << endl;
	cin >> selection;
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Invalid input for Scenario Selection, the game will re-prompt you." << endl;
		system("pause");
		soggySinkhole();
	}
	if (selection == 1)
	{
		cout << "You've decided to cross the sinkhole." << endl;
		if (itemChecks[3] == 1 && durabilities[3] >= 0)
		{
			string selection;
			cout << "Seems like you have fuel in your jetpack, would you like to do that? (Yes/No)" << endl;
			cin >> selection;
			if ((selection == "yes" || selection == "Yes") && durabilities[3] > 15)
			{
				cout << "You have decided to safely fly over the sinkhole, avoiding all possible dangers. However, you lost some jetpack fuel." << endl;
				cout << "You did also find some trail mix on the other side." << endl;
				durabilities[3] -= 15;
				findTrailMix();
				gameScenarioSelections();
			}
			if ((selection == "yes" || selection == "Yes") && durabilities[3] < 15)
			{
				cout << "You have decided to safely fly over the sinkhole, avoiding all possible dangers. " << endl << "However, you didn't have enough fuel to cross." << endl;
				cout << "About halfway to cross over the sinkhole you fell and were consumed by the sinkhole becoming the 6th victim of it." << endl;
				cout << "Your journey comes to an end as you failed to escape the jungle." << endl;
				health = 0;
				checkDeath();
			}
			else
			{
				cout << "You have opted not to use the Jetpack, a fatal mistake." << endl;
				cout << "About halfway to cross over the sinkhole you tripped and were consumed by the sinkhole becoming the 6th victim of it." << endl;
				cout << "Your journey comes to an end as you failed to escape the jungle." << endl;
				health = 0;
				checkDeath();
			}
		}
		cout << "You have opted not to use the Jetpack, a fatal mistake." << endl;
		cout << "About halfway to cross over the sinkhole you tripped and were consumed by the sinkhole becoming the 6th victim of it." << endl;
		cout << "Your journey comes to an end as you failed to escape the jungle." << endl;
		health = 0;
		checkDeath();
	}
	if (selection == 2)
	{
		selection = 0;
		cout << "You have decided to walk around towards the thick brush to the side." << endl;
		cout << "You begin to hear trees swaying and twigs breaking, and emerging from the brushes is a Zebra" << endl;
		cout << "Your terrified and your fight or flight response kicks in, what is your decision?" << endl;
		cout << "1. Fight the Zebra with your Pocket Knife." << endl;
		cout << "2. Toss some Trail Mix to distract it while you run away." << endl;
		cin >> selection;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Invalid input for Scenario Selection, the game will re-prompt you." << endl;
			system("pause");
			soggySinkhole();
		}
		if (selection == 1)
		{
			cout << "You fight the Zebra and overcome it after a long battle , however , you have taken some damage and your Pocket Knife suffered severe damage." << endl;
			health -= 15;
			checkDeath();
			durabilities[1] -= 50;
			gameScenarioSelections();
		}
		if (selection == 2 && amountOfMix > 0)
		{
			cout << "You've thrown trail mix into the brushes and run away as fast as you can, this costed minor health damages" << endl;
			cout << "and of course the used trail mix." << endl;
			health -= 5;
			amountOfMix -= 1;
			checkDeath();
			gameScenarioSelections();
		}
		if (selection == 2 && amountOfMix == 0)
		{
			cout << "You've gone to throw trail mix to distract the Zebra, but you notice that you have none." << endl;
			cout << "You are left with the decision to attempt to scare it off, and you yell as loud as you can at it." << endl;
			cout << "The Zebra runs off back into the brushes and you continue off into the jungle with no damages or losses." << endl;
			gameScenarioSelections();
		}
		else
		{
			cout << "Invalid input for Scenario Selection, the game will re-prompt you." << endl;
			system("pause");
			soggySinkhole();
		}
	}
}
void ruggedRiver()
{
	int selection;
	cout << "As you continue on your journey you stumble across a large river with an unstable bridge" << endl;
	cout << "It seems like it's the only way to cross, you decide whether to cross the bridge or create another way" << endl;
	cout << "What would you like to do?: " << endl;
	cout << "1. Use some nearby trees and twigs to create a raft." << endl;
	cout << "2. Attempt to cross the bridge" << endl;
	cout << "Choose your decision: ";
	cin >> selection;
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Invalid input for Scenario Selection, the game will re-prompt you." << endl;
		system("pause");
		ruggedRiver();
	}
	if (selection == 1)
	{
		cout << "You spend a long time building a raft and it takes some Pocket Knife Durability and some Health." << endl;
		cout << "You spent your time well since you were able to cross the river safely and without any real issues." << endl;
		health -= 15;
		checkDeath();
		durabilities[1] -= 25;
		gameScenarioSelections();
	}
	if (selection == 2)
	{
		cout << "You decide to cross the bridge, about halfway across the bridge snaps and breaks." << endl;
		cout << "You begin falling down and you think to yourself this is the end." << endl;
		if (durabilities[3] > 15)
		{
			cout << "You reach for your back and you remember your Jetpack, you use it and manage to fly back up." << endl;
			cout << "You had a huge scare but you managed to make it through suffering no injuries... Except for some mental damage." << endl;
			durabilities[3] -= 25;
			gameScenarioSelections();
		}
		if (durabilities[3] < 15 && durabilities[3] > 0)
		{
			cout << "You reach for your back and you remember your Jetpack and use it to fly back up." << endl << "However, you didn't have enough fuel to get all the way up." << endl;
			cout << "About halfway back up your Jetpack runs out and you fall tragically into the Rugged River." << endl;
			cout << "Your journey comes to an end as you failed to escape the jungle." << endl;
			health = 0;
			checkDeath();
		}
		if (durabilities[3] == 0)
		{
			cout << "You fall down and you have nothing to save you, you realize this is the end and nothing can stop it." << endl;
			cout << "You fall into the Rugged River as it drifts along with your body." << endl;
			cout << "Your journey comes to an end as you failed to escape the jungle." << endl;
			health = 0;
			checkDeath();
		}
	}
	if (selection != 1 && selection != 2)
	{
		cout << "You entered an invalid selection. The game will re-prompt you." << endl;
		system("pause");
		ruggedRiver();
	}
}
void victoryScenario()
{
	cout << "You breakthrough all the pain and manage to find yourself in an open field at the edge of the Jungle" << endl;
	cout << "You see off into the distance but not too far a helicopter, must've heard of the crash." << endl;
	cout << "You try and think of something that could help you signal it and you remember the plane having flashlights." << endl;
	if (durabilities[2] > 0)
	{
		cout << "You reach into your bag and pull out the Flashlight you had, and shine it towards the helicopter." << endl;
		cout << "The Helicopter notices and begins move towards the island you are on to rescue you" << endl;
		cout << "The Helicopter lands in the open field and you run towards it to greet the pilot" << endl;
		cout << "You explain tragically that there are no other survivors and you take off back home." << endl;
		cout << "You are happy that you finally escaped the Jungle and that you can finally go back to your family." << endl;
		SetConsoleTextAttribute(hConsole, 2);
		cout << "CONGRATULATIONS YOU HAVE ESCAPED THE JUNGLE";
		SetConsoleTextAttribute(hConsole, 7);
		cout << endl << endl << "Be sure to play again!!!" << endl;
		cout << "Goodbye!!" << endl;
		Sleep(5000);
		_Exit(10);
	}
	if (durabilities[2] == 0)
	{
		cout << "You reach into your bag and you don't have a Flashlight" << endl;
		cout << "Your only choice is to trek back into the jungle to find it and some batteries." << endl;
		cout << "Better be careful!" << endl;
		gameScenarioSelections();
	}
}

//Map display 
void mapDisplay() {
	cout << "________________________________________________________________________" << endl;
	cout << "\t\t\t\tMAP" << endl;
	cout << "________________________________________________________________________	" << endl;
	cout << "|| \\  ^  ~\\  ^  ~\\  ^  ~\\  ^ ~\\ ^   ~\\ ^   ~\\  ^  ~\\ ^  ~\\ ^    ~\\ ||" << endl;
	cout << "||	                                                           ||" << endl;
	cout << "||            ------                                       ~^~^~^~^||" << endl;
	cout << "||  ^       /  -----  \\                                      ~^~^~^||" << endl;
	cout << "||^   ^    /  /      \\ \\                                   ~^~^~^~^||" << endl;
	cout << "||                                        ^ ^ ^   ^ ^ ^    ~^~^~^~^||" << endl;
	cout << "||                                       ^|^|^|^ ^|^|^|^   ~^~^~^~^||" << endl;
	cout << "||  ^                                                        ~^~^~^||" << endl;
	cout << "||^   ^                                                      ~^~^~^||" << endl;
	cout << "||  ^                   Crash Site                           ~^~^~^||" << endl;
	cout << "||^   ^                    \\`\\                             ~^~^~^~^||" << endl;
	cout << "||                   |\\ ____\\_\\__                          ~^~^~^~^||" << endl;
	cout << "||  ^                \\c`\"\"\"\"\"\"\" \"`)                          ~^~^~^||" << endl;
	cout << "||^   ^              `~~~~~/ /~~`                          ~^~^~^~^||" << endl;
	cout << "||                         -'                              ~^~^~^~^||" << endl;
	cout << "||          /=========\\                                      ~^~^~^||" << endl;
	cout << "||  ^      //~*~~*~~*~\\\\                                   ~^~^~^~^||" << endl;
	cout << "||^   ^    \\\\ *~~*~~* //                   ========          ~^~^~^||" << endl;
	cout << "||                                         //              ~^~^~^~^||" << endl;
	cout << "||              ---                                          ~^~^~^||" << endl;
	cout << "||  ^          ||*||                                       ~^~^~^~^||" << endl;
	cout << "||^    ^        ---                                          ~^~^~^||" << endl;
	cout << "||           (`  ).  (`  ).   (`  ).    (`  ).                     ||" << endl;
	cout << "||(   ).  .:(`  )`.(   ).  .:(`  )`.(   ).  .:(`  )`.(   ).  .:(`  ||" << endl;
	cout << "___________________________________________________________________" << endl;
	cout << "___________________________________________________________________" << endl;
	cout << "\t\tMAP KEY:" << endl;
	cout << "Cosmic Cave:   -------            Mountain:" << endl;
	cout << "             /  -----  \\                             ^" << endl;
	cout << "            /  /     \\  \\                          ^   ^" << endl;
	cout << "Rugged River:                     Fatal Forest: " << endl;
	cout<<  "\\ ~ ^ \\ ~                                 "<<"    ^ ^ ^" << endl;
	cout << "     \\ ~ ^ \\ ~                               ^|^|^|^"<<endl;
	cout<<"Camouflaged Cove:                   Fog:" << endl;
	cout << "     /=========\\                        (`  )." << endl;
	cout << "    //~*~~*~~*~\\\\                   (  ).  .:(`  )`." << endl;
	cout << "    \\\\ *~~*~~* //													" << endl;
	cout << "Ocean:                         Collapsing Cliff:		" << endl;
	cout << " ~^~^~^~^                          =====" << endl;
	cout << " ^~^~^~^                          //" << endl;
	cout << "Treasure Chest" << endl;
	cout << "    ___" << endl;
	cout << "   ||*||" << endl;
	cout << "    ---" << endl;
	cout << "______________________________________________________________________________" << endl;
}



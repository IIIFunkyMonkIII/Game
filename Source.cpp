#include <iostream>
#include <string>
#include <limits>
#include <Windows.h>
#include <chrono>
#include <thread>


//Globals
int currentRoom{ 0 };					//the room we are in
int currentRoomDialogSegment{ 1 };	// The dialog segment


//Structs
struct Character					//Oscar
{
	std::string name{ "Oscar Riverbranch" };

	bool weaponSlot{ true };			//you smited svante into oblivion with the power of love you get 1+ thaikub but loose the power of love ability
	std::string weaponName{ "Power of Love" };
	int weaponDamage{ 1000 };

	bool potionSlot{};
	std::string potionName{};
	int potionCount{};

	bool backpack{};
	std::string itemName{};
	std::string itemAbility{};

	int maxHealth{ 1 };
	int maxStamina{};

	bool firstTimeInCloset{ true };
};


using itemClass_t = std::string;	//Typ av item du håller eller vill plocka upp.

struct Item
{
	itemClass_t itemClass{};
	std::string itemName{};


};


struct Room					//Innehåll i rum
{
	std::string items[5]{}; // Dynamisk Array här sen **************************************************



};


//Global struct initalizations
Character oscar;

Room closetContent;


//Forward Declarations
void roomList();
void command();
void purge();
void closet();
void start();

//Namepaces
using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;


//Main
int main()
{
	start();

	return 0;
}



//Functions


void start()
{
	bool go{ false };
	std::string temp;

	do
	{
		std::cout << "Enter the word " << '"' << "start" << '"' << " to start the game: ";
		std::cin >> temp;

		if (std::cin.fail())
		{
			purge();
			std::cerr << "Erronious input! Read the instructions again. \n";
		}
		else
		{
			if (temp == "START" || temp == "start" || temp == "Start")
			{
				std::cout << "Welcome to Oscars Life!";
				go = true;
				sleep_for(3s);
				system("CLS");
			}
		}

	} while (go != true);



	roomList();

}

void command()
{
	std::string currentCommand{};
	std::cin.ignore(1000);
	getline(std::cin, currentCommand);

	if (currentCommand == "pick up")
	{
		std::cout << "You have picked up: ";

	}
}

void roomList() // rumLista för att navigera genom alla rum.
{
	switch (currentRoom)
	case(0):
	{
		closet();
	}



}

void closet()
{

	if (oscar.firstTimeInCloset == true)
	{
		switch (currentRoomDialogSegment)
		{
		case 1:
		{
			oscar.firstTimeInCloset = false;
			closetContent.items[0] = "boxers";

			std::cout << "You lie knocked out on the floor in a confined space under a pile of clothes" << '\n'
				<< "You see a pair of bamboo boxershorts that your uncle manufactures write pickup boxers to pick up the bamboo boxershorts that is lying besides you." << '\n'
				<< "This item is of type " << '\n' // continue
				<< "You only have one itemslot in your xxx olypics back pack if you wish to pick up another item write empty back pack and then pick up..." << '\n'
				<< "Now try pick upp and drop the boxers\n" << '\n';

		}

		}


	}

}

void purge()
{
	std::cin.clear();
	std::cin.ignore(1000);
}
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
struct Backpack
{
	bool itemSlotFull{};
	std::string itemName{};
	std::string itemAbility{};
};

struct Weapon
{
	bool weaponSlotFull{};			//you smited svante into oblivion with the power of love you get 1+ thaikub but loose the power of love ability
	std::string weaponName{};
	int weaponDamage{};
};

struct Potion
{
	bool potionSlotFull{};
	std::string potionName{};
	int potionCount{};
};


struct Character					//Oscar
{
	std::string name{ "Oscar Riverbranch" };

	Weapon weapon{true, "Power of Love", 1000};		//you smited svante into oblivion with the power of love you get 1+ thaikub but loose the power of love ability

	Backpack backpack;

	Potion potion;

	int maxHealth{ 1 };
	int maxStamina{};

	bool firstTimeInCloset{ true };
};


using itemClass_t = std::string;	//Typ av item du håller eller vill plocka upp.

struct Item
{
	bool itemAvailability{ true };
	itemClass_t itemClass{};
	std::string itemName{};


};


struct Room					//Innehåll i rum
{
	Item items[5]{}; // dynamisk Array här sen **************************************************

};


//Global struct initalizations
Character oscar;
Room closetContent;



//Forward Declarations
void roomList();
void command(Room x);
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

void command(Room roomContent)
{
	std::string currentCommand{};
	getline(std::cin, currentCommand);
	std::string wholeCommand{};
	int contentArraySize{ 5 };//gör till dynamisk array eller vector.

	// gör en if för om början på commando == pick up
	if (currentCommand.substr(0, 7) == "pick up")								// pick up command
	{
		for (int loop{ 0 }; loop < contentArraySize; loop++)					//Loop för att jämföra items
		{
			wholeCommand = ("pick up " + roomContent.items[loop].itemName);		//Gäller nu for saker av typ Item men behöver göras olika funktioner för vapen och trolldrycker

			if (currentCommand == wholeCommand && roomContent.items[loop].itemClass == "backpack")
			{																	//System för att kolla vilka items som är tillgängliga samt system för att plock upp skiten och sätta att den itne är tillgänglig längre.
				if (oscar.backpack.itemSlotFull == true)
				{
					std::cerr << "Your back pack is full. Empty the backpack and then try again! \n";
				}
				else if (roomContent.items[loop].itemAvailability == true && oscar.backpack.itemSlotFull == false)
				{				
					oscar.backpack.itemSlotFull = true;							//ryggsäck nu full
					oscar.backpack.itemName = roomContent.items[loop].itemName;	//den innehåller en item som heter 
					roomContent.items[loop].itemAvailability = false;				//itemet finns nu inte tillgängligt i rummet

					std::cout << "Your xxx olympics backpack now contains " << oscar.backpack.itemName << '\n';
				}
			}	

			if (currentCommand == wholeCommand && roomContent.items[loop].itemClass == "weapon")
			{																	//System för att kolla vilka items som är tillgängliga samt system för att plock upp skiten och sätta att den itne är tillgänglig längre.
				if (oscar.backpack.itemSlotFull == true)
				{
					std::cerr << "You are already holding a weapon. Drop it and try again! \n";
				}
				else if (roomContent.items[loop].itemAvailability == true && oscar.weapon.weaponSlotFull == false)
				{
					oscar.weapon.weaponSlotFull = true;							//ryggsäck nu full
					oscar.weapon.weaponName = roomContent.items[0].itemName;	//den innehåller en item som heter 
					roomContent.items[loop].itemAvailability = false;			//itemet finns nu inte tillgängligt i rummet

					std::cout << "Your hand now contains" << oscar.weapon.weaponName << '\n';
				}


			}

			if (currentCommand == wholeCommand && roomContent.items[loop].itemClass == "potion")
			{																	//System för att kolla vilka items som är tillgängliga samt system för att plock upp skiten och sätta att den itne är tillgänglig längre.
				if (oscar.potion.potionSlotFull == true)
				{
					std::cerr << "Your back pack is full. Empty the backpack and then try again! \n";
				}
				else if (roomContent.items[loop].itemAvailability == true && oscar.potion.potionSlotFull == false)
				{
					oscar.potion.potionSlotFull = true;							//ryggsäck nu full
					oscar.potion.potionName = roomContent.items[0].itemName;	//den innehåller en item som heter 
					roomContent.items[loop].itemAvailability = false;			//itemet finns nu inte tillgängligt i rummet

					std::cout << "Your xxx olympics backpack now contains" << oscar.potion.potionName << '\n';
				}


			}
		} // gör ett system så att om inget kommando passar skicka fel
	}

	if (currentCommand == "empty backpack")
	{
		if (oscar.backpack.itemSlotFull == true)
		{
			oscar.backpack.itemSlotFull = false;
			oscar.backpack.itemName = "";
			oscar.backpack.itemAbility = "";
		}
		else
		{
			std::cout << "Your backpack is already empty! \n";
		}
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
			oscar.firstTimeInCloset = false;

			//Closet start item
			closetContent.items[0].itemName = "boxers";
			closetContent.items[0].itemClass = "backpack";
			closetContent.items[1].itemName = "butterKnife";

			std::cout << "You lie knocked out on the floor in a confined space under a pile of clothes" << '\n'
			<< "You see a pair of bamboo boxershorts that your dads cousin manufactures write pickup boxers to pick up the bamboo boxershorts that is lying besides you." << '\n'
			<< "This item is of type " << closetContent.items[0].itemClass << '\n';
			std::cout << "You only have one itemslot in your xxx olypics backpack if you wish to pick up another item write empty backpack and then pick up..." << '\n'
			<< "Now try pick up and drop the boxers\n" << '\n';



			while (oscar.backpack.itemSlotFull != true)
			{
				command(closetContent);
			}
			
			std::cout << "Good you picked up the boxers, now try to drop them again \n";

			while (oscar.backpack.itemSlotFull != false)
			{
				command(closetContent);

			}

			std::cout << "Good you dropped the underware. You don't want to walk around with those all the time.";

	}

}



void purge()
{
	std::cin.clear();
	std::cin.ignore(1000);
}
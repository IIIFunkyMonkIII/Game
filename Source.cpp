#include <iostream>
#include <string>
#include <limits>
#include <Windows.h>
#include <chrono>
#include <thread>


//Globals
int X{ 1 };
int Y{ 2 };
int Z{ 2 };
									//the room we are in
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

	bool svanteAlive{ true };

	bool firstTimeInCloset{ true };
	bool firstTimeInRoom{ true };
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
void svante();
void oscarsRoom();
void compactArray(Room roomContent, int removedItem, int contentArraySize);
int lastItemInContentArray(Room roomContent, int contentArraySize);
void next();


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

		if (temp == "START" || temp == "start" || temp == "Start")
			{
			std::cout << "Welcome to Oscars Life!";
			go = true;
			sleep_for(3s);
			system("CLS");
		}
		else
		{
			purge();
			std::cerr << "Erronious input! Read the instructions again. \n";
		}

	} while (go != true);



	roomList();
	return;
}

void command(Room roomContent) // måste göra en bättre lösning på Room och roomContent så att command blir en kravlös funktion
{
	std::string currentCommand{};
	getline(std::cin, currentCommand);
	std::string wholeCommand{};
	int contentArraySize{ 5 };//gör till dynamisk array eller vector.
	bool commandFound{false};

	// gör en if för om början på commando == pick up
	if (currentCommand.substr(0, 7) == "pick up")								// pick up command
	{
		for (int loop{ 0 }; loop < contentArraySize; loop++)					//Loop för att jämföra items
		{
			wholeCommand = ("pick up " + roomContent.items[loop].itemName);

			if (currentCommand == wholeCommand && roomContent.items[loop].itemClass == "backpack")
			{																	//System för att kolla vilka items som är tillgängliga samt system för att plock upp skiten och sätta att den itne är tillgänglig längre.
				if (oscar.backpack.itemSlotFull == true)
				{
					std::cerr << "Your backpack already contains one item. Empty the backpack and then try again! \n";
				}
				else if (roomContent.items[loop].itemAvailability == true && oscar.backpack.itemSlotFull == false)
				{				
					oscar.backpack.itemSlotFull = true;							//ryggsäck nu full
					oscar.backpack.itemName = roomContent.items[loop].itemName;	//den innehåller en item som heter 
					roomContent.items[loop].itemAvailability = false;				//itemet finns nu inte tillgängligt i rummet

					std::cout << "Your xxx olympics backpack now contains " << oscar.backpack.itemName << '\n';
				}
				
				commandFound = true;
			}	

			if (currentCommand == wholeCommand && roomContent.items[loop].itemClass == "weapon")
			{																	//System för att kolla vilka items som är tillgängliga samt system för att plock upp skiten och sätta att den itne är tillgänglig längre.
				if (oscar.weapon.weaponSlotFull == true)
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

				commandFound = true;
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
				commandFound = true;
			}
			
			if (commandFound == true && roomContent.items[loop].itemAvailability == false)
			{
				compactArray(roomContent, loop, contentArraySize);
			}		
		}

		if (commandFound == false)
		{
			std::cout << "That item doesn't exist! \n \n";
		}
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

	return;
}

void roomList() // rumLista för att navigera genom alla rum.
{
	if(Z == 2 && Y == 2 && X == 1)
	{
		closet();
	}
	if (Z == 2 && Y == 2 && X == 2)
	{
		oscarsRoom();
	}


	return;
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
			closetContent.items[1].itemClass = "weapon";

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

			std::cout << "Good you dropped the underware. You don't want to walk around with those all the time. \n";

			// stand up command

			std::cout << "You take one step east and get out of the closet. \n"; 

			X++;
			next();
	}

	return;
}

void oscarsRoom()
{
	if (oscar.firstTimeInRoom == true)
	{
		std::cout << "You see your chonker of a gaming computer that is missing a leg. You have balanced it up with your latest mac computer.\n" <<
			"The computer is connected to three monitors and dolby surround. Besides the desk you see the gaming chair you won in a poll last year. \n" <<
			"In the chair lies a hairy beast called Svante and with a swift motion he lunges at you for an attack! \n \n";

		std::cout << "What path do you choose: attack or cuddles?: ";

		svante(); //Fortsätt Svante funktionen.

	}
}

void svante()
{
	std::string path{};
	
	while (path != "cuddles" || path != "attack")
	{
		std::cin >> path;

		if (path == "cuddles")
		{
			std::cout << "You chose to embrace the terrible beast and he now follows you because he want's food down in the kitchen \n" <<
				"Find kibble for Svante within 10 commands or he will eat you!\n" << "The kitchen is down stairs, walk out of the room and you should find them.";
			
			for (int loop{0}; X != 6 && Y != 2 && Z != 1 && loop <= 10; loop++)
			{
				command();
			}

		}
		else if (path == "attack")
		{
			std::cout << "You chose to confront the beast and much like in Harry Potter the chambre of secrets you win the fight with the power of love. \n" 
				<< "Svante gets smited in to oblivion and you win the fight but you loose he power of love ability. \n"
				<< "It's soon time for school and you better get ready by walking there.":

		}
		else
		{
			std::cout << "You have to pick a path! \n \n";
			purge();
		}
	}
}

void compactArray(Room roomContent, int loop, int contentArraySize)
{
	int lastItemInList{ lastItemInContentArray(roomContent, contentArraySize) };

	//kopierar över item information till hålet som skapats
	roomContent.items[loop].itemAvailability = roomContent.items[lastItemInList].itemAvailability;
	roomContent.items[loop].itemClass = roomContent.items[lastItemInList].itemClass;
	roomContent.items[loop].itemName = roomContent.items[lastItemInList].itemName;
	//Sätter sista i listan till tom
	roomContent.items[lastItemInList].itemAvailability = false;
	roomContent.items[lastItemInList].itemClass = "";
	roomContent.items[lastItemInList].itemName = "";
}

int lastItemInContentArray(Room roomContent, int contentArraySize)
{
	int lastItemInList{-1};  // -1 enkel fix för off by one error

	for (int l{ 0 }; l < contentArraySize; l++)
	{
		if (roomContent.items[l].itemName != "")
		{
			lastItemInList++;
		}
	}

	return lastItemInList;
}

void next()
{
	char next{};
	while (next != 'n')
	{
		std::cout << "Press n to continue: ";
		std::cin >> next;
	}
	system("CLS");
}

void purge()
{
	std::cin.clear();
	std::cin.ignore(1000,'\n');
	
	return;
}
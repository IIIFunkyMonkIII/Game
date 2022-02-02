#include <iostream>
#include <string>
#include <limits>
#include <Windows.h>
#include <chrono>
#include <thread>


//Globals
int X{ 1 };
int Y{ 2 };
int Z{ 2 };							//Array for the contents of the rooms
int currentRoom{0};					//the room we are in
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
	
	bool alive{true};

	bool svanteAlive{ true };

	bool questInProgress{ true };
	bool firstTimeInCloset{ true };
	bool firstTimeInRoom{ true };
	std::string path{""};
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
Room roomContent[7]{};


//Forward Declarations
void roomList();
void command();
void purge();
void closet();
void start();
void svante();
void oscarsRoom();
void compactArray(int removedItem, int contentArraySize);
int lastItemInContentArray(int contentArraySize);
void next();
void dead();
void hallway();
void stairs();
void vestibule();

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
		purge();

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

void command() 
{
	std::cout << "write a command: ";

	std::string currentCommand{};
	getline(std::cin, currentCommand);
	std::string wholeCommand{};
	int size{ 5 };																//gör om ork finns till dynamisk array eller vector.
	bool commandFound{false};


	
	if (currentCommand.substr(0, 7) == "pick up")								// pick up command
	{
		for (int loop{ 0 }; loop < size; loop++)								//Loop för att jämföra items
		{
			wholeCommand = ("pick up " + roomContent[currentRoom].items[loop].itemName);		// sätter ihop en sök mening med pick up och det loopade itemet

			if (currentCommand == wholeCommand && roomContent[currentRoom].items[loop].itemClass == "backpack")
			{																	//System för att kolla vilka items som är tillgängliga samt system för att plock upp skiten och sätta att den itne är tillgänglig längre.
				if (oscar.backpack.itemSlotFull == true)
				{
					std::cerr << "Your backpack already contains one item. Empty the backpack and then try again! \n";
				}
				else if (roomContent[currentRoom].items[loop].itemAvailability == true && oscar.backpack.itemSlotFull == false)
				{				
					oscar.backpack.itemSlotFull = true;							//ryggsäck nu full
					oscar.backpack.itemName = roomContent[currentRoom].items[loop].itemName;	//den innehåller en item som heter 
					roomContent[currentRoom].items[loop].itemAvailability = false;				//itemet finns nu inte tillgängligt i rummet

					std::cout << "Your xxx olympics backpack now contains " << oscar.backpack.itemName << '\n';
				}
				
				commandFound = true;
			}	

			if (currentCommand == wholeCommand && roomContent[currentRoom].items[loop].itemClass == "weapon")
			{																	//System för att kolla vilka items som är tillgängliga samt system för att plock upp skiten och sätta att den itne är tillgänglig längre.
				if (oscar.weapon.weaponSlotFull == true)
				{
					std::cerr << "You are already holding a weapon. Drop it and try again! \n";
				}
				else if (roomContent[currentRoom].items[loop].itemAvailability == true && oscar.weapon.weaponSlotFull == false)
				{
					oscar.weapon.weaponSlotFull = true;							//ryggsäck nu full
					oscar.weapon.weaponName = roomContent[currentRoom].items[0].itemName;	//den innehåller en item som heter 
					roomContent[currentRoom].items[loop].itemAvailability = false;			//itemet finns nu inte tillgängligt i rummet

					std::cout << "Your hand now contains" << oscar.weapon.weaponName << '\n';
				}

				commandFound = true;
			}

			if (currentCommand == wholeCommand && roomContent[currentRoom].items[loop].itemClass == "potion")
			{																	//System för att kolla vilka items som är tillgängliga samt system för att plock upp skiten och sätta att den itne är tillgänglig längre.
				if (oscar.potion.potionSlotFull == true)
				{
					std::cerr << "Your back pack is full. Empty the backpack and then try again! \n";
				}
				else if (roomContent[currentRoom].items[loop].itemAvailability == true && oscar.potion.potionSlotFull == false)
				{
					oscar.potion.potionSlotFull = true;							//ryggsäck nu full
					oscar.potion.potionName = roomContent[currentRoom].items[0].itemName;	//den innehåller en item som heter 
					roomContent[currentRoom].items[loop].itemAvailability = false;			//itemet finns nu inte tillgängligt i rummet

					std::cout << "Your xxx olympics backpack now contains" << oscar.potion.potionName << '\n';
				}
				commandFound = true;
			}
			
			if (commandFound == true && roomContent[currentRoom].items[loop].itemAvailability == false)
			{
				compactArray(loop, size);
			}		
		}

		if (commandFound == false)
		{
			std::cout << "That item doesn't exist! \n \n";
		}
	}

	if (currentCommand == "empty backpack")
	{
		int lastElement{ lastItemInContentArray(size) + 1 }; // +1 för att få sista lediga

		if (oscar.backpack.itemSlotFull == true && lastElement <= 5)
		{
			roomContent[currentRoom].items[lastElement].itemName = oscar.backpack.itemName;
			roomContent[currentRoom].items[lastElement].itemClass = "backpack";
				roomContent[currentRoom].items[lastElement].itemAvailability = true;

			oscar.backpack.itemSlotFull = false;
			oscar.backpack.itemName = "";
			oscar.backpack.itemAbility = "";		
		}
		else if (lastElement > 5)
		{
			std::cout << "This room is too cluttered! Clean up or leave it some where else. \n";
		}
		else
		{
			std::cout << "Your backpack is already empty! \n";
		}
	}
	
	//kommandon för rörelse i rum
	if (currentCommand == "north") 
	{
		Y++;
		roomList();
	}

	if (currentCommand == "south") 
	{
		Y--;
		roomList();
	}

	if (currentCommand == "east")
	{
		X++;
		roomList();
	}

	if (currentCommand == "west")
	{
		X--;
		roomList();
	}

	if (currentCommand == "down")
	{
		if (X == 3 && Y == 3 && Z == 2)
		{
			Z--;
			roomList();
		}
		else
		{
			std::cout << "Do you want to sink through the floor?\n";
		}
	}

	if (currentCommand == "up")
	{
		if (X == 3 && Y == 3 && Z == 1)
		{
			Z++;
			roomList();
		}
		else
		{
			std::cout << "Didn't know you could fly through cielings\n";
		}

	}
	//Lista över kommandon
	if (currentCommand == "command list")
	{
		std::cout << "The possible commands are: \n" << "pick up...\n" << "empty backpack\n" << "north\n" << "south\n" << "east\n" << "west\n" << "kys \n";
	}

	if (currentCommand == "kys")
	{
		oscar.alive = false;
		dead();
	}

	return;
}

void roomList() // rumLista för att navigera genom alla rum.
{


	if (Z == 2 && Y == 2 && X == 1 && Z == 2)						// koordinater som är okej
	{
		closet();
		currentRoom = 0;
	}
	else if (X == 2 && Y == 2 && Z == 2) // koordinater som är okej
	{
		oscarsRoom();
		currentRoom = 1;
	}
	else if (X == 3 && Y == 2 && Z == 2)
	{
		hallway();
	}
	else if (X == 3 && Y == 3 && Z == 2)
	{
		if (oscar.svanteAlive == true)
		{
			std::cout << "Svante gets impatient and decides to push you down the stairs\n";
			sleep_for(3s);
			dead();
		}
		else
		{
			stairs();
		}

	}
	else if(X == 2 && Y == 3 && Z == 1)
	{
		vestibule();
	}
	else
	{
		std::cout << "You can't walk that way!\n";
	}


	return;
}

void closet()
{

	if (oscar.firstTimeInCloset == true)
	{
			oscar.firstTimeInCloset = false;

			//Closet start item
			roomContent[currentRoom].items[0].itemName = "boxers";
			roomContent[currentRoom].items[0].itemClass = "backpack";
			roomContent[currentRoom].items[1].itemName = "butterKnife";
			roomContent[currentRoom].items[1].itemClass = "weapon";

			std::cout << "You lie knocked out on the floor in a confined space under a pile of clothes" << '\n'
			<< "You see a pair of bamboo boxershorts that your dads cousin manufactures write pickup boxers to pick up the bamboo boxershorts that is lying besides you." << '\n'
			<< "This item is of type " << roomContent[currentRoom].items[0].itemClass << '\n';
			std::cout << "You only have one itemslot in your xxx olypics backpack if you wish to pick up another item write empty backpack and then pick up..." << '\n'
			<< "Now try pick up and drop the boxers\n" << '\n';



			while (oscar.backpack.itemSlotFull != true)
			{
				if (oscar.alive == false)
				{
					break;
				}
				command();
			}
			
			if (oscar.alive == true)
			{
				std::cout << "Good you picked up the boxers, now try to drop them again \n";
			}
		

			while (oscar.backpack.itemSlotFull != false)
			{
				if (oscar.alive == false)
				{
					continue;
				}
				command();

			}

			if (oscar.alive == true)
			{
				std::cout << "Good you dropped the underware. You don't want to walk around with those all the time. \n";
				std::cout << "You take one step east and get out of the closet. \n";

				X++;
				next();
				roomList();
			}

	}
	else
	{
		std::cout << "You have entered the closet\n";
	}
}

void oscarsRoom()
{

	if (oscar.firstTimeInRoom == true)
	{
		std::cout << "You see your chonker of a gaming computer that is missing a leg. You have balanced it up with your latest mac computer.\n" <<
			"The computer is connected to three monitors and dolby surround. Besides the desk you see the gaming chair you won in a poll last year. \n" <<
			"In the chair lies a hairy beast called Svante and with a swift motion he lunges at you for an attack! \n \n";

		svante(); //Fortsätt Svante funktionen.

	}
	else
	{
		std::cout << "You have entered your bedroom\n";
	}
	
}

void hallway()
{
	std::cout << "You have entered the hallway \n" << "To the north there is a staircase that leads to the first floor\n";
}

void svante()
{

	while (oscar.path != "cuddles" && oscar.path != "attack")
	{
		std::cout << "What path do you choose: attack or cuddles?: ";
		getline(std::cin, oscar.path);

		if (oscar.path == "cuddles" || oscar.path == "attack")
		{
			system("CLS");
			oscar.firstTimeInRoom = false;
		}
		else
		{
			std::cout << "\n Read the instruction again \n";
		}
	}
	

	if (oscar.path == "cuddles")
	{
		std::cout << "You chose to embrace the terrible beast and he now follows you because he want's food down in the kitchen \n" <<
		"Find kibble for Svante within 10 commands or he will eat you!\n" << "The kitchen is down stairs, walk out of the room and you should find them.\n\n";

		int countDown{};

		for (int loop{ 10 }; loop > 0; loop--)
		{
			if (oscar.alive == false)
			{
				break;
			}
			std::cout << "Turns left: " << loop << '\n';
			countDown = loop;
			command();
		}

		if (countDown == 1)
		{
			std::cout << "Svande decides to chomp you in the heel. \n" << "The last thing you see before you close your eyes is a little evil smile on his furry face whilst he feasts on your blood.\n";
			sleep_for(10s);
			dead();
		}



	}
	else if (oscar.path == "attack")
	{
		std::cout << "You chose to confront the beast and much like in Harry Potter the chambre of secrets you win the fight with the power of love. \n"
			<< "Svante gets smited in to oblivion and you win the fight but you loose he power of love ability. \n"
			<< "It's soon time for school and you better get ready by walking there.\n\n";

		oscar.weapon = { false, "", 0 };
		svante.alive = false;

		while (X != 1 && Y != 1 && Z != 3)
		{
			if (oscar.alive == false)
			{
				continue;
			}
			command();
		}
	}

	return;
}

void stairs()
{
	std::cout << "You are now down stairs \n";

}

void vestibule()
{
	std::cout << "You are now standing in the vestibule \n";
}

void compactArray(int loop, int contentArraySize)
{
	int lastItemInList{ lastItemInContentArray( contentArraySize) };

	//kopierar över item information till hålet som skapats
	roomContent[currentRoom].items[loop].itemAvailability = roomContent[currentRoom].items[lastItemInList].itemAvailability;
	roomContent[currentRoom].items[loop].itemClass = roomContent[currentRoom].items[lastItemInList].itemClass;
	roomContent[currentRoom].items[loop].itemName = roomContent[currentRoom].items[lastItemInList].itemName;
	//Sätter sista i listan till tom
	roomContent[currentRoom].items[lastItemInList].itemAvailability = false;
	roomContent[currentRoom].items[lastItemInList].itemClass = "";
	roomContent[currentRoom].items[lastItemInList].itemName = "";

	return;
}

int lastItemInContentArray( int contentArraySize)
{
	int lastItemInList{-1};  // -1 enkel fix för off by one error

	for (int l{ 0 }; l < contentArraySize; l++)
	{
		if (roomContent[currentRoom].items[l].itemName != "")
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
		purge();
	}
	system("CLS");

	return;
}

void purge()
{
	std::cin.clear();
	std::cin.ignore(1000,'\n');
	
	return;
}

void dead()
{
	system("CLS");
	std::cout << "You dead\n\n";
	sleep_for(5s);
	
	oscar.alive = false;
	
	return;
}
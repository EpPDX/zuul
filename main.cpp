/*
  Zuul by Caley Epstein
  A text adventure where the player travels and picks up items
  12/2/19
  Help with vectors room and item creation from Stefan Ene
 */

#include <iostream>
#include <cstring>
#include <vector>
#include <iomanip>
#include <map>
#include <algorithm>

#include "room.h"
#include "item.h"


using namespace std;

void initializeRooms(vector<Room*>* rooms);
void initializeItems(vector<Item*>* items);

//functions
void printRoom(vector<Room*>* rooms, vector<Item*>* items, int currentRoom);
void printInventory(vector<Item*>* items, vector<int> invtry);
void getItem(vector<Room*>* rooms, vector<Item*>* items,vector<int>* invtry, int currentRoom, char name[]);
void dropItem(vector<Room*>* rooms, vector<Item*>* items, vector<int>* invtry, int currentRoom, char name[]);
int move(vector<Room*>* rooms, int currentRoom, char direction[]);


//main
int main() 
{
  //variables set up
  bool run = true;
  vector<Room*> roomList;
  vector<Item*> itemList;
  vector<int> inventory;
  
  int currentRoom = 1;
  initializeRooms(&roomList);
  initializeItems(&itemList);
  
  char input[30];
  
  //text for user
  cout << "You are tapped inside a spooky scary maze. You wake up and don't remember a thing! Then you notice a note in your hand. It reads: Mwahahaha I have trapped you in the super secret basement below sunset. To excape you must collect all three pieces of the IB cirriculum. That is the only way you will get a 100 on your C++ practical test! -Mr. Galbraith" << endl;
  cout << "commands: help, quit, go, get, inventory, and drop" << endl; 
  
  
  //main running until quit makes false
  while (run) 
  {
    cout << endl << "You currently are ";
    printRoom(&roomList, &itemList, currentRoom);
    cin >> input;
    cin.clear();
    cin.ignore(10000, '\n');
    
    if (strcmp(input, "quit") == 0) 
    {
      run = false;
    }
    
    //sees direction player wants to move
    else if (strcmp(input, "go") == 0) 
    {
      cout << "north, south, east, or west?" << endl;
      cin >> input;
      cin.clear();
      cin.ignore(10000, '\n');
      
      if (move(&roomList, currentRoom, input) == 0) 
      {
	cout << endl << "nothing in that direction" << endl;
      }
      
      else 
      {
	currentRoom = move(&roomList, currentRoom, input);
      }
    }
    
    
    else if (strcmp(input, "get") == 0) 
    {
      
      cout << "What item?" << endl;
      cin >> input;
      cin.clear();
      cin.ignore(10000, '\n');
      getItem(&roomList, &itemList, &inventory, currentRoom, input);
    }
    
    
    else if (strcmp(input, "inventory") == 0) 
    {
      if (inventory.size() != 0) 
      {
	cout << endl << "You have: ";
	printInventory(&itemList, inventory);
      } 
      else 
      {
	cout << endl << "you have nothing yet" << endl;
      }
    }
    
    
    
    else if (strcmp(input, "drop") == 0) 
    {
      cout << "What item?" << endl;
      cin >> input;
      cin.clear();
      cin.ignore(10000, '\n');
      dropItem(&roomList, &itemList, &inventory, currentRoom, input);
    }
    
    
    else if (strcmp(input, "help") == 0) 
    {
      cout << "Commands: help, quit, go, get, inventory, and drop. Remember, you need all three pieces of the IB cirriculum" << endl;
      
    }
    else 
    {
      cout << endl <<"I don't know what you mean." << endl;
    }





    //to win
    for (int a = 0; a < inventory.size(); a++) 
    {
      for (int b = 0; b < inventory.size(); b++) 
      {
	for (int c = 0; c < inventory.size(); c++) 
	{
	  if (currentRoom == 1 && inventory[a] == 1 && inventory[b] == 2 && inventory[c] == 3) {
	    cout << endl << "You escaped! Galbraith gave you a 100!" << endl << endl;
	    return 0;
	  }
	}
      }
    }
  }
  
  return 0;
}




int move(vector<Room*>* rooms, int currentRoom, char direction[]) 
{
  vector<Room*>::iterator i;
  for(i = rooms->begin(); i != rooms->end(); i++) 
  {
    if (currentRoom == (*i)->getId()) 
    {
      map<int, char*> exits;
      exits = *(*i) -> getExits();
      map<int, char*>::const_iterator m;
      for (m = exits.begin(); m != exits.end(); ++m) 
      {
	if (strcmp(m -> second, direction) == 0) 
	{
	  //next room player moves to
	  return m -> first;
	}
      }
    }
  }
  return 0;
}

//make items
void initializeItems(vector<Item*>* items) 
{
  Item* remote = new Item();
  remote -> setName((char*)("cal's soul"));
  remote -> setId(4);
  items -> push_back(remote);
  Item* tbrush = new Item();
  tbrush -> setName((char*)("the 1-20 bathroom pass"));
  tbrush -> setId(5);
  items -> push_back(tbrush);
  Item* laptop = new Item();
  laptop -> setName((char*)("IB triforce of stuying"));
  laptop -> setId(1);
  items -> push_back(laptop);
  Item* bcase = new Item();
  bcase -> setName((char*)("IB triforce of having no social life"));
  bcase -> setId(2);
  items -> push_back(bcase);
  Item* ck = new Item();
  ck -> setName((char*)("IB triforce of a ton of tests"));
  ck -> setId(3);
  items -> push_back(ck);
}

void initializeRooms(vector<Room*>* rooms) 
{
  //choose direction
  char* north = (char*)("north");
  char* south = (char*)("south");
  char* east = (char*)("east");
  char* west = (char*)("west");
  
  
  map<int, char*> temp;
  
  
  //make rooms:
  Room* hall  = new Room();
  hall -> setDescription((char*)("you're in creepy room"));
  hall -> setId(1);
  temp.insert(pair<int, char*> (2, east));
  temp.insert(pair<int, char*> (3, north));
  hall -> setExits(temp);
  hall -> setItem(0);
  rooms -> push_back(hall);
  temp.clear();
  

  Room* dinner = new Room();
  dinner -> setDescription((char*)("you're in 1-20"));
  dinner -> setId(3);
  temp.insert(pair<int, char*> (1, south));
  temp.insert(pair<int, char*> (13, north));
  dinner -> setExits(temp);
  dinner -> setItem(0);
  rooms -> push_back(dinner);
  temp.clear();
  
  Room* garage = new Room();
  garage -> setDescription((char*)("you're in galbraiths office."));
  garage -> setId(13);
  temp.insert(pair<int, char*> (3, south));
  garage -> setExits(temp);
  garage -> setItem(3/*keys*/);
  rooms -> push_back(garage);
  temp.clear();
  
  Room* living = new Room();
  living -> setDescription((char*)("you're in the hub"));
  living -> setId(2);
  temp.insert(pair<int, char*> (1, west));
  temp.insert(pair<int, char*> (5, north));
  temp.insert(pair<int, char*> (8, south));
  temp.insert(pair<int, char*> (6, east));
  living -> setExits(temp);
  living -> setItem(4/*remote*/);
  rooms -> push_back(living);
  temp.clear();
  
  Room* bath = new Room();
  bath -> setDescription((char*)("you're in a very very very boring room"));
  bath -> setId(5);
  temp.insert(pair<int, char*> (2, south));
  bath -> setExits(temp);
  bath -> setItem(5/*toothbrush*/);
  rooms -> push_back(bath);
  temp.clear();
  
  Room* guest = new Room();
  guest -> setDescription((char*)("you're in the janitor's undergroud lair"));
  guest -> setId(6);
  temp.insert(pair<int, char*> (2, west));
  temp.insert(pair<int, char*> (7, north));
  guest -> setExits(temp);
  guest -> setItem(0);
  rooms -> push_back(guest);
  temp.clear();
  
  Room* closet = new Room();
  closet -> setDescription((char*)("you're in the mop bucket, you must be a contortionist"));
  closet -> setId(7);
  temp.insert(pair<int, char*> (6, south));
  closet -> setExits(temp);
  closet -> setItem(0);
  rooms -> push_back(closet);
  temp.clear();
  
  Room* inhall = new Room();
  inhall -> setDescription((char*)("you're in the sewers, gross"));
  inhall -> setId(8);
  temp.insert(pair<int, char*> (2, north));
  temp.insert(pair<int, char*> (9, west));
  temp.insert(pair<int, char*> (10, east));
  temp.insert(pair<int, char*> (11, south));
  inhall -> setExits(temp);
  rooms -> push_back(inhall);
  temp.clear();
  
  Room* office = new Room();
  office -> setDescription((char*)("you're under the bathroom, even grosser"));
  office -> setId(9);
  temp.insert(pair<int, char*> (8, east));
  office -> setExits(temp);
  office -> setItem(0);
  rooms -> push_back(office);
  temp.clear();
  
  Room* master = new Room();
  master -> setDescription((char*)("you're at the sewer offshoot"));
  master -> setId(10);
  temp.insert(pair<int, char*> (8, west));
  temp.insert(pair<int, char*> (14, north));
  temp.insert(pair<int, char*> (12, east));
  master -> setExits(temp);
  master -> setItem(2/*briefcase*/);
  rooms -> push_back(master);
  temp.clear();
  
  Room* secret = new Room();
  secret -> setDescription((char*)("you're in the pond of sewage, GROSS"));
  secret -> setId(14);
  temp.insert(pair<int, char*> (10, south));
  secret -> setExits(temp);
  secret -> setItem(0);
  rooms -> push_back(secret);
  temp.clear();
  
  Room* balcony = new Room();
  balcony -> setDescription((char*)("you're under the sewage drain"));
  balcony -> setId(12);
  temp.insert(pair<int, char*> (10, west));
  temp.insert(pair<int, char*> (4, east));
  balcony -> setExits(temp);
  balcony -> setItem(0);
  rooms -> push_back(balcony);
  temp.clear();
  
  Room* outside = new Room();
  outside -> setDescription((char*)("you're in the rifle range, sunset used to have one lol"));
  outside -> setId(11);
  temp.insert(pair<int, char*> (8, north));
  temp.insert(pair<int, char*> (15, east));
  outside -> setExits(temp);
  outside -> setItem(0);
  rooms -> push_back(outside);
  temp.clear();
  
  Room* coat = new Room();
  outside -> setDescription((char*)("you've escaped the drain! now you're just on thr ground"));
  outside -> setId(11);
  temp.insert(pair<int, char*> (8, north));
  temp.insert(pair<int, char*> (15, east));
  outside -> setExits(temp);
  outside -> setItem(1);
  rooms -> push_back(coat);
  temp.clear();
  
  Room* shed = new Room();
  shed -> setDescription((char*)("you're in the costume storage room for the drama department."));
  shed -> setId(15);
  temp.insert(pair<int, char*> (11, west));
  shed -> setExits(temp);
  shed -> setItem(0);
  rooms -> push_back(shed);
  temp.clear();
}







//message desplayed in rooms
void printRoom(vector<Room*>* rooms, vector<Item*>* items, int currentRoom) 
{
  vector<Room*>::iterator r;
  vector<Item*>::iterator i;
  for (r = rooms->begin(); r != rooms->end(); r++) 
  {
    if (currentRoom == (*r)->getId()) 
    {
      cout << (*r)->getDescription() << endl;
      cout << "exits: ";
      for (map<int, char*>::const_iterator it = (*r) -> getExits() -> begin(); it != (*r) -> getExits() -> end(); it++) 
      {
	cout << it -> second << " ";
      }
      
      cout << endl;
      cout << "items in the room: ";
      int itemCount = 0;
      
      for (i = items->begin(); i != items->end(); i++) 
      {
          //gets item name
	if ((*r)->getItem() == (*i)->getId()) 
	{
	  cout << (*i)->getName();
	  itemCount++;
	}
      }
      
      //if no item is returned then...
      if (itemCount == 0) 
      {
	cout << "no items in here." << endl;
      } 
      else 
      {
      cout << endl;
      }
    }
  }
}



void printInventory(vector<Item*>* items, vector<int> invtry) 
{
  vector<Item*>::iterator i;
  for (i = items->begin(); i != items->end(); i++) 
  {
    for (int a = 0; a < invtry.size(); a++) 
    {
      if (invtry[a] == (*i) -> getId()) 
      {
	cout << (*i) -> getName() << " ";
      }
    }
  }
  cout << endl;
}


//gets item and adds to inv while deleting from room
void getItem(vector<Room*>* rooms, vector<Item*>* items,vector<int>* invtry, int currentRoom, char name[]) 
{
  vector<Room*>::iterator r;
  vector<Item*>::iterator i;
  for (r = rooms->begin(); r != rooms->end(); r++) 
  {
    if (currentRoom == (*r) -> getId()) {
      for (i = items->begin(); i != items->end(); i++) 
      {
	if (((*r) -> getItem() == (*i) -> getId()) && (strcmp((*i) -> getName(), name) == 0)) 
	{

	  invtry -> push_back((*i) -> getId());

	  (*r) -> setItem(0);
	  cout << endl << "got " << (*i) -> getName() << "." << endl;
	  return;
	}
      }
    } 
  }
  cout << "that item is not in the room" << endl;
}


//gets item from inventory and puts it in room
void dropItem(vector<Room*>* rooms, vector<Item*>* items, vector<int>* invtry, int currentRoom, char name[]) 
{
  int counter;
  vector<Room*>::iterator r;
  vector<Item*>::iterator i;
  vector<int>::iterator iv;
  for(r = rooms->begin(); r != rooms->end(); r++) 
  {
    if(currentRoom == (*r) -> getId()) 
    {
      \
      if ((*r) -> getItem() == 0) 
      {
	for (i = items->begin(); i != items->end(); i++) 
	{
	   
	  if (strcmp((*i) -> getName(), name) == 0) 
	  { 
	    for (iv = invtry -> begin(); iv != invtry -> end(); iv++) 
	    {
	      
	      if ((*iv) == (*i) -> getId()) 
	      {
		cout << endl << "dropped " << (*i) -> getName() << "." << endl;
		
		(*r) -> setItem((*i) -> getId());
		
		iv = invtry -> erase(iv);
		return;
	      }
	    }
	  }
	  else if (counter == items -> size() - 1) 
	  {
	    cout << endl << "you don't have that item" << endl;
	  }
	  counter++;
	}
      }
      else 
      {
	cout << endl << "that item is already in the room" << endl;
      }
    }
  }
}
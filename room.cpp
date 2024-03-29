//file for getting and setting room info

#include <iostream>
#include <cstring>
#include <map>
#include "room.h"

using namespace std;



Room::Room() 
{
}



char* Room::getDescription()
{
  return description;
}

map<int, char*>* Room::getExits() 
{
  return &exits;
}

int Room::getId()
{
  return id;
}

int Room::getItem()
{
  return item;
}



void Room::setDescription(char* newDescription)
{
  description = newDescription;
}

void Room::setExits(map<int, char*> newExits) 
{
  exits = newExits;
}

void Room::setId(int newId)
{
  id = newId;
}

void Room::setItem(int newItem) 
{
  item = newItem;
}
//this keeps track of the items with getters and setters

#include <iostream>
#include <cstring>
#include "item.h"

using namespace std;

Item::Item() 
{

}

char* Item::getName()
{
  return name;
}

int Item::getId()
{
  return id;
}

void Item::setName(char* newName)
{
  name = newName;
}

void Item::setId(int newId)
{
  id = newId;
}
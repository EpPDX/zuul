//.h file for room data

#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <cstring>
#include <map>

using namespace std;



class Room 
{
 public:
  Room();
  char* getDescription();
  int getId();
  int getItem();
  map<int, char*>* getExits();
  void setDescription(char*);
  void setExits(map<int, char*>);
  void setId(int);
  void setItem(int);
 private:
  char* description;
  map<int, char*> exits;
  int id;
  int item;
};


#endif
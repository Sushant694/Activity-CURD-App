#pragma once 
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
using namespace std;

const int MAX_ACTIVITIES = 30;
const int MAX_STR = 51;

enum Type {
    Athletic = 0,
    Food = 1,
    Arts = 2,
    Games = 3,
    Others = 4
};

struct Activity {
    char name[MAX_STR];
    char location[MAX_STR];
    char level[MAX_STR];
    int Rating;
    Type types;
};

// Function prototypes
void loadActivities(Activity activities[], int &size);
void saveActivities(const Activity activities[], int size);
void insertActivitySorted(Activity activities[], int &size, const Activity &newAct);
void List_By_Name(Activity activities[], int &size);
void List_By_Location(const Activity activities[], int size, const char location[]);
void listByType(const Activity activities[], int size, Type types);
int findByName(const Activity activities[], int size, const char name[]);
void removeByIndex(Activity activities[], int &size, int index);
const char* typeToString(Type types);
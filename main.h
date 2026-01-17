#pragma once
#include "activity.h"

void printMenu();
char getMenuChoice();
void readCString(char dest[], int maxLen);
void addActivity(Activity activities[], int &size);

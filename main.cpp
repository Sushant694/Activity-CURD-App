#include <iostream>
#include <limits>
#include <cstring>
#include <fstream>
#include <cctype>
#include "activity.h"
#include "main.h"
using namespace std;

// ALL function implementations go here
void printMenu() {
    cout << "\nPick an option from below:\n\n"
         << "(a)Add a new activity\n"
         << "(b)List activities by name\n"
         << "(c)List activities by location\n"
         << "(d)List activities by Type\n"
         << "(e)Remove an activity\n"
         << "(f)Search by activity name\n"
         << "(q)Quit\n\n";
}

char getMenuChoice() {
    char choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return tolower(choice);
}

void readCString(char dest[], int maxLen) {
    cin.getline(dest, maxLen);
    while (strlen(dest) == 0) {
        cin.getline(dest, maxLen);
    }
}

void addActivity(Activity activities[], int &size) {
    if (size >= MAX_ACTIVITIES) {
        cout << "List is full.\n";
        return;
    }

    Activity a;
    cout << "Enter the activity name (50 characters or less): ";
    readCString(a.name, MAX_STR);
    cout << "Enter the activity location (50 characters or less): ";
    readCString(a.location, MAX_STR);
    cout << "Enter the activity level: ";
    readCString(a.level, MAX_STR);

    bool valid = false;
    while (!valid) {
        cout << "Enter the activity rating: ";
        if (!(cin >> a.Rating)) {
            cout << "Invalid rating! Please enter a valid rating!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else if (a.Rating < 1 || a.Rating > 10) {
            cout << "Rating must be between 1 and 10.\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            valid = true;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    int typeNum;
    valid = false;
    while (!valid) {
        cout << "Enter Type number(0-Athletics, 1-Food, 2-Arts, 3-Games, 4-Others): ";
        if (!(cin >> typeNum)) {
            cout << "Invalid Type! Please enter 0-4.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else if (typeNum < 0 || typeNum > 4) {
            cout << "Invalid Type! Please enter 0-4.\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            valid = true;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    a.types = static_cast<Type>(typeNum);

    insertActivitySorted(activities, size, a); 
    cout << "\nActivity added!\n";
    List_By_Name(activities, size);
}

// NEW FUNCTIONS - declared in main.h
void removeActivity(Activity activities[], int &size) {
    // Show current list first
    List_By_Name(activities, size);  // This needs fixing - see note below
    cout << "\nPick the index to remove: ";
    
    int index;
    if (cin >> index) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (index >= 1 && index <= size) {
            removeByIndex(activities, size, index - 1);
            cout << "\nActivity removed!\n";
        } else {
            cout << "Invalid index!\n";
        }
    } else {
        cout << "Invalid index!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    List_By_Name(activities, size);

}

void searchActivity(Activity activities[], int size) {
    char name[MAX_STR];
    cout << "Enter the activity name: ";
    readCString(name, MAX_STR);
    
    int idx = findByName(activities, size, name);
    if (idx == -1) {
        cout << "Activity not found!!\n";
    } else {
        cout << "\nActivity found!\n";
        cout << (idx + 1) << ". "
             << activities[idx].name << ';'
             << activities[idx].location << ';'
             << activities[idx].level << ';'
             << activities[idx].Rating << ';'
             << typeToString(activities[idx].types) << '\n';
    }
}

void listActivitiesByLocation(Activity activities[], int size) {
    char location[MAX_STR];
    cout << "Enter location name: ";
    readCString(location, MAX_STR);
    List_By_Location(activities, size, location);
}

void listActivitiesByType(Activity activities[], int size) {
    int typeNum;
    cout << "Enter Type number(0-Athletics, 1-Food, 2-Arts, 3-Games, 4-Others): ";
    if (cin >> typeNum) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (typeNum >= 0 && typeNum <= 4) {
            listByType(activities, size, static_cast<Type>(typeNum));
        } else {
            cout << "Invalid Type!\n";
        }
    } else {
        cout << "Invalid Type!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int main() {
    Activity activities[MAX_ACTIVITIES];
    int size = 0;

    cout << "Welcome!\nThis program will help you manage your activities.\n\n";
    loadActivities(activities, size);

    char choice = 'x';
    while (choice != 'q') {
        printMenu();
        choice = getMenuChoice();

        if (choice == 'a') {
            addActivity(activities, size);
        } 
        else if (choice == 'b') {
            List_By_Name(activities, size);
        }
        else if (choice == 'c') {
            listActivitiesByLocation(activities, size);
        }
        else if (choice == 'd') {
            listActivitiesByType(activities, size);
        }
        else if (choice == 'e') {
            removeActivity(activities, size);

        }
        else if (choice == 'f') {
            searchActivity(activities, size);
        }
        else if (choice != 'q') {
            cout << "Invalid option!! Please try again!\n";
        }
    }

    saveActivities(activities, size);
    cout << "\nActivities written to file! Thank you for using my program!!\n";
    return 0;
}

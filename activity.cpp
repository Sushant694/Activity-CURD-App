#include "activity.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
using namespace std;

void loadActivities(Activity activities[], int &size) {
    size = 0;
    ifstream inFile("activity.txt");
    if (!inFile.is_open()) return;
    
    string line;
    while (getline(inFile, line) && size < MAX_ACTIVITIES) {
        if (line.empty()) continue;
        
        // 1. NAME (before first ;)
        size_t location = line.find(";");
        if (location == string::npos) continue;
        string nameStr = line.substr(0, location);
        strncpy(activities[size].name, nameStr.c_str(), MAX_STR - 1);
        activities[size].name[MAX_STR-1] = '\0';
        
        // 2. LOCATION (between 1st and 2nd ;)
        string rest1 = line.substr(location + 1);
        location = rest1.find(";");
        if (location == string::npos) continue;
        string locStr = rest1.substr(0, location);
        strncpy(activities[size].location, locStr.c_str(), MAX_STR - 1);
        activities[size].location[MAX_STR-1] = '\0';
        
        // 3. LEVEL (between 2nd and 3rd ;)
        string rest2 = rest1.substr(location + 1);
        location = rest2.find(";");
        if (location == string::npos) continue;
        string levelStr = rest2.substr(0, location);
        strncpy(activities[size].level, levelStr.c_str(), MAX_STR - 1);
        activities[size].level[MAX_STR-1] = '\0';
        
        // 4. RATING (between 3rd and 4th ;)
        string rest3 = rest2.substr(location + 1);
        location = rest3.find(";");
        if (location == string::npos) continue;
        string ratingStr = rest3.substr(0, location);
        activities[size].Rating = stoi(ratingStr);
        
        // 5. TYPE (after 4th ;)
        string typeStr = rest3.substr(location + 1);
        int typeNum = stoi(typeStr);
        if (typeNum < 0 || typeNum > 4) typeNum = 4;
        activities[size].types = static_cast<Type>(typeNum);
        
        size++;
    }
    
    inFile.close();

    // Bubble Sort by activity name (alphabetical)
    for(int i = 0; i < size - 1; i++) {
        for(int j = 0; j < size - i - 1; j++) {  // FIXED: j starts at 0
            if(strcmp(activities[j].name, activities[j+1].name) > 0) {
                // Swap activities[j] and activities[j+1]
                Activity temp = activities[j];
                activities[j] = activities[j+1];
                activities[j+1] = temp;
            }
        }
    }

    cout << "Loaded and sorted" << size << " activities\n.";
}


void saveActivities(const Activity activities[], int size) {
    ofstream outFile("activity.txt");
    for (int i = 0; i < size; i++) {
        outFile << activities[i].name << ";"
                << activities[i].location << ";"
                << activities[i].level << ";"
                << activities[i].Rating << ";"
                << static_cast<int>(activities[i].types) << "\n";
    }
    outFile.close();
}

void insertActivitySorted(Activity activities[], int &size, const Activity &newAct) {
    if (size >= MAX_ACTIVITIES) {
        cout << "List is full. Cannot add more activities.\n";
        return;
    }
    
    int pos = 0;
    while (pos < size && strcmp(activities[pos].name, newAct.name) < 0) {
        pos++;
    }
    
    for (int i = size; i > pos; i--) {
        activities[i] = activities[i-1];
    }
    activities[pos] = newAct;
    size++;
}

const char* typeToString(Type types) {
    switch (types) {
        case Athletic: return "Athletics";
        case Food: return "Food";
        case Arts: return "Arts";
        case Games: return "Games";
        default: return "Others";
    }
}

void List_By_Name(Activity activities[], int &size) {
    // YOUR WORKING VERSION - keep it exactly as you have it

    for (int i = 0; i < size; i++) {
        cout << (i + 1) << ". "
             << activities[i].name << ';'
             << activities[i].location << ';'
             << activities[i].level << ';'
             << activities[i].Rating << ';'
             << typeToString(activities[i].types) << '\n';
    }
}

void List_By_Location(const Activity activities[], int size, const char location[]) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (strstr(activities[i].location, location)) {
            count++;
            cout << count << ". "
                 << activities[i].name << ';'
                 << activities[i].location << ';'
                 << activities[i].level << ';'
                 << activities[i].Rating << ';'
                 << typeToString(activities[i].types) << '\n';
        }
    }
    if (count == 0) {
        cout << "No activities found at that location.\n";
    }
}

void listByType(const Activity activities[], int size, Type types) {
    bool found = false;
    for (int i = 0; i < size; i++) {
        if (activities[i].types == types) {
            cout << activities[i].name << ';'
                 << activities[i].location << ';'
                 << activities[i].level << ';'
                 << activities[i].Rating << ';'
                 << typeToString(activities[i].types) << '\n';
            found = true;
        }
    }
    if (!found) {
        cout << "No activities found for that type.\n";
    }
}

int findByName(const Activity activities[], int size, const char name[]) {
    for (int i = 0; i < size; i++) {
        if (strcmp(activities[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

void removeByIndex(Activity activities[], int &size, int index) {
    if (index < 0 || index >= size) {
        cout << "Invalid index.\n";
        return;
    }
    for (int i = index; i < size - 1; i++) {
        activities[i] = activities[i + 1];
    }
    size--;
}

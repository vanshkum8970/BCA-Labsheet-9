#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Structure to store Item details
struct Item {
    int itemId;
    char studentName[30];
    char itemName[30];
    char status[10]; // "Lost" or "Found"
    char location[30];
};

// Global variables for student login credentials
string regStudentId = "", regPassword = "";

// Module 1: Student Login System
void studentLogin() {
    cout << "\n--- STUDENT REGISTRATION & LOGIN ---\n";
    cout << "Register your Student ID: ";
    cin >> regStudentId;
    cout << "Register your Password: ";
    cin >> regPassword;
    
    string loginId, loginPass;
    cout << "\n--- LOGIN NOW ---\n";
    cout << "Enter Student ID: ";
    cin >> loginId;
    cout << "Enter Password: ";
    cin >> loginPass;

    if (loginId == regStudentId && loginPass == regPassword) {
        cout << "Login Successful!\n";
    } else {
        cout << "Invalid Credentials! Access Denied.\n";
    }
}

// Module 2 & 3: Report Lost or Found Item
void reportItem(int id, const char itemStatus[]) {
    Item itm;
    itm.itemId = id;
    strcpy_s(itm.status, itemStatus);

    cout << "\n--- REPORT " << itm.status << " ITEM ---\n";
    cout << "Enter Student Name: ";
    cin >> itm.studentName;
    cout << "Enter Item Name (e.g., Wallet, ID_Card, Laptop): ";
    cin >> itm.itemName;
    cout << "Enter Location (Lost/Found at): ";
    cin >> itm.location;

    // File Handling: Saving record to text file
    ofstream outFile("lost_found_records.txt", ios::app);
    outFile << itm.itemId << " " << itm.studentName << " " << itm.itemName << " " << itm.status << " " << itm.location << endl;
    outFile.close();

    cout << "Item reported and saved successfully! Record ID: " << itm.itemId << "\n";
}

// Module 4: Search Item by Name
void searchItem() {
    char searchKey[30];
    cout << "\n--- SEARCH ITEM ---\n";
    cout << "Enter Item Name to search: ";
    cin >> searchKey;

    ifstream inFile("lost_found_records.txt");
    if (!inFile) {
        cout << "No records found!\n";
        return;
    }

    int id;
    char name[30], item[30], stat[10], loc[30];
    bool found = false;

    cout << "\nID\tStudent\t\tItem\t\tStatus\t\tLocation\n";
    cout << "-------------------------------------------------------------\n";
    while (inFile >> id >> name >> item >> stat >> loc) {
        string s1(item), s2(searchKey);
        if (s1 == s2) {
            cout << id << "\t" << name << "\t\t" << item << "\t\t" << stat << "\t\t" << loc << endl;
            found = true;
        }
    }
    inFile.close();

    if (!found) {
        cout << "No matching item found in records.\n";
    }
}

// Module 5: Auto Match Lost & Found Items
void autoMatchItems() {
    cout << "\n--- AUTO MATCH LOST & FOUND RECORDS ---\n";
    ifstream inFile("lost_found_records.txt");
    if (!inFile) {
        cout << "No records available for matching!\n";
        return;
    }

    // Temporary arrays to store records in memory
    const int MAX = 100;
    int ids[MAX];
    string names[MAX], items[MAX], statuses[MAX], locations[MAX];
    int count = 0;

    while (inFile >> ids[count] >> names[count] >> items[count] >> statuses[count] >> locations[count]) {
        count++;
    }
    inFile.close();

    bool matchFound = false;
    // Comparing Lost and Found items with the same item name
    for (int i = 0; i < count; i++) {
        for (int j = i + 1; j < count; j++) {
            if (items[i] == items[j] && statuses[i] != statuses[j]) {
                cout << "[MATCH FOUND!] Item '" << items[i] << "' reported as " << statuses[i] 
                     << " by " << names[i] << " and reported as " << statuses[j] 
                     << " by " << names[j] << "!\n";
                matchFound = true;
            }
        }
    }

    if (!matchFound) {
        cout << "No auto-matches found at this moment.\n";
    }
}

// Module 6: View All Records
void viewAllRecords() {
    cout << "\n--- ALL LOST & FOUND RECORDS ---\n";
    ifstream inFile("lost_found_records.txt");
    if (!inFile) {
        cout << "No records found!\n";
        return;
    }

    int id;
    char name[30], item[30], stat[10], loc[30];

    cout << "ID\tStudent\t\tItem\t\tStatus\t\tLocation\n";
    cout << "-------------------------------------------------------------\n";
    while (inFile >> id >> name >> item >> stat >> loc) {
        cout << id << "\t" << name << "\t\t" << item << "\t\t" << stat << "\t\t" << loc << endl;
    }
    inFile.close();
}

// Main Menu-Driven Program
int main() {
    int choice;
    int idCounter = 1;

    do {
        cout << "\n=========================================\n";
        cout << "   SMART CAMPUS LOST & FOUND SYSTEM\n";
        cout << "=========================================\n";
        cout << "1. Student Login\n";
        cout << "2. Report Lost Item\n";
        cout << "3. Report Found Item\n";
        cout << "4. Search Item\n";
        cout << "5. Auto Match Lost & Found\n";
        cout << "6. View All Records\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                studentLogin();
                break;
            case 2:
                reportItem(idCounter, "Lost");
                idCounter++;
                break;
            case 3:
                reportItem(idCounter, "Found");
                idCounter++;
                break;
            case 4:
                searchItem();
                break;
            case 5:
                autoMatchItems();
                break;
            case 6:
                viewAllRecords();
                break;
            case 7:
                cout << "Exiting system. Thank you!\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 7);

    return 0;
}

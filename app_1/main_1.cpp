#include <iostream>
#include "../code_1/miniGit.hpp"
#include <filesystem>
using namespace std;

// temporary comment, remove befor turning in
// use this command to run the code
// g++ --std=c++17 main_1.cpp ../code_1/miniGit.cpp -o a.out

/*
 * Purpose; displays a menu with options
 */
void displayMenu()
{
    cout << "Select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. init " << endl;
    cout << " 2. add " << endl;
    cout << " 3. rm " << endl;
    cout << " 4. commit " << endl;
    cout << " 5. checkout" << endl;
    cout << " 6. search" << endl;
    cout << " 7. quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}
int main(int argc, char* argv[]) 
{
    bool menuOn = true;
    int menuChoice = 0;
    
    MiniGit myGit;
    string fileName = "";
    
    while(menuOn)
    {
        displayMenu();
        
        cin >> menuChoice;
        while(menuChoice <= 0 || menuChoice > 3)
        {
            cout << "Enter a valid optiond: ";
            cin >> menuChoice;
        }
        
        switch(menuChoice)
        {
            // initialise a new repository
            case 1:
                myGit.init(5);
            break;
                
            // add files to current commit
            case 2:
                fileName = "";
                cout << "Enter a file name: ";
                cin >> fileName;
                
                myGit.add(fileName);
            break;
                /*
            // remove files from current commit
            case 3:
            break;
                
            // Commit Changes
            case 4:
            break;
                
            // Search commits based on key word
            case 5:
            break;
                
            // check out specific version based on a unique commit option
            case 6:
            break;
                */
            // quit
            case 3:
                menuOn = false;
            break;
        }
    }
   
    return 0;
}
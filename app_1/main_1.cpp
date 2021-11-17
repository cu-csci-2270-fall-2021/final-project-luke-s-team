#include <iostream>
#include "../code_1/miniGit.hpp"
#include <filesystem>
#include <string>
using namespace std;
// temporary comment, remove befor turning in
// use this command to run the code
// g++ --std=c++17 main_1.cpp ../code_1/miniGit.cpp ../code_1/hash.cpp -o a.out

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

// check to make sure the commit message is a valid length of three words
bool checkCommitMessage(string message)
{
    int words = 0;
    for(int length = 0; message.size() > length; length++)
        if(message[length] == ' ')
            words++;
    if(words > 2)
        return false;
    return true;
}

int main(int argc, char* argv[]) 
{
    bool menuOn = true;
    int menuChoice = 0;
    string m_input;
    
    MiniGit myGit;
    string fileName = "";
    string message = "";
    
    while(menuOn)
    {
        displayMenu();
        
        // used from provided code in assignment 4
        getline(cin,m_input);
        try
        {
             menuChoice = stoi(m_input);
        }
        catch (exception& e)
        {
            menuChoice = 10;
        }
        
        
        switch(menuChoice)
        {
            // initialise a new repository
            case 1:
                myGit.init(5);
                myGit.printSearchTable();
            break;
                
            // add files to current commit
            case 2:
                fileName = "";
                cout << "Enter a file name: ";
                getline(cin,fileName);
                
                myGit.add(fileName);
            break;
        
            // remove files from current commit
            case 3:
                fileName = "";
                cout << "Enter a file name: ";
                getline(cin,fileName);
                
                myGit.rm(fileName);
            break;
                
            // Commit Changes
            case 4:
                cout << "Enter a commit message: ";
                getline(cin, message);
                cout << message << endl;
                /*
                while(!checkCommitMessage(message))
                {
                    cout << "Enter a valid commit message: ";
                    getline(cin, message);
                    cout << message << endl;
                }
                */
                //myGit.commit(message);
            break;
                
            // Search commits based on key word
            case 5:
                cout << "not coded yet" << endl;
            break;
                
            // check out specific version based on a unique commit option
            case 6:
                cout << "not coded yet" << endl;
            break;
                
            // quit
            case 7:
                menuOn = false;
            break;
            default:
                cout << "Invalid input" << endl;
            break;
        }
    }
   
    return 0;
}


#include <iostream>
#include "../code_1/miniGit.hpp"
#include <filesystem>
#include <string>
using namespace std;
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
// make sure the user enters a valid word to to search for
bool checkSearchKey(string key)
{
    for(int i = 0; i < key.size(); i+=1)
        if(key[i] == ' ')
            return false;
    return true;
}
// make sure the user enters a valid search key
bool checkCommitNum(string commitNum)
{
    // check to make sure string is a number
    for(int i = 0; i < commitNum.size(); i+=1)
        if(!isdigit(commitNum[i]))
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
    string searchKey = "";
    string commitNum = "";
    
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
                
                while(!checkCommitMessage(message) || myGit.node(message))
                {
                    cout << "Enter a valid commit message: ";
                    getline(cin, message);
                }
                
                myGit.commit(message);
                myGit.printSearchTable();
            break;
                
            // check out specific version based on a unique commit option
            case 5:
                cout << "Enter a commit number to return to: ";
                getline(cin,commitNum);
                while(!checkCommitNum(commitNum)||stoi(commitNum)>myGit.getCommits() || stoi(commitNum) < 0)
                {
                    cout << "Enter a valid commit number: ";
                    getline(cin,commitNum);
                }
                myGit.checkout(commitNum);
            break;
                
            // Search commits based on key word
            case 6:
                cout << "Enter a key word to search for: ";
                getline(cin,searchKey);
                while(!checkSearchKey(searchKey))
                {
                    cout << "Enter a single word: ";
                    getline(cin,searchKey);
                }
                myGit.search(searchKey);
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

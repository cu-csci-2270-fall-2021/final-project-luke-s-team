#include <iostream>
#include "../code_1/miniGit.hpp"
#include <filesystem>
<<<<<<< HEAD
namespace fs = std::filesystem;

#include "miniGit.hpp"
#include <vector>

bool node(string message){
    BranchNode *branchNode = commitHead;
    if(message == branchNode->commitMessage) return true;
    for(int node = 0; commits > node; node++) {
        branchNode = branchNode->next;
        if(message == branchNode->commitMessage) return true;
    }
    return false;
}

<<<<<<< HEAD
// check to make sure the commit message is a valid length of three words
bool checkCommitMessage(string message)
{
    int words = 0;
    for(int length = 0; message.size() > length; length++)
        if(message[length] == ' ')
            words++;
    if(words > 2 || node)
        return false;
    return true;
=======
MiniGit::MiniGit() {
    fs::remove_all(".minigit");
    fs::create_directory(".minigit");
>>>>>>> 3b172db1aeac25fd6ddc57ea4bc56bc1ff28f144
}

MiniGit::~MiniGit() {   
    // Any postprocessing that may be required
    
    // delete the singly linked list
    FileNode * crawler = commitHead->fileHead;
    while(commitHead->fileHead != NULL)
    {
        crawler = commitHead->fileHead -> next;
        delete commitHead->fileHead;
        commitHead->fileHead = crawler;
    }
    commitHead->fileHead = NULL;
    
    // delete the doubly linked list
    BranchNode * crawler2 = commitHead;
    while(commitHead != NULL)
    {
        crawler2 = commitHead -> next;
        delete commitHead;
        commitHead = crawler2;
    }
    commitHead = NULL;
    
    //fs::remove_all(".minigit");
    //fs::remove_all(".new");
}

void MiniGit::init(int hashtablesize) 
=======
#include <string>
using namespace std;
// temporary comment, remove befor turning in
// use this command to run the code
// g++ --std=c++17 main_1.cpp ../code_1/miniGit.cpp ../code_1/hash.cpp -o a.out

/*
 * Purpose; displays a menu with options
 */
void displayMenu()
>>>>>>> 7388eafd58848916203494503f779e7318ccd197
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
                
                while(!checkCommitMessage(message))// || myGit.node(message))
                {
                    cout << "Enter a valid commit message: ";
                    getline(cin, message);
                }
                
                myGit.commit(message);
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


#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#include <filesystem>
namespace fs = std::filesystem;

#include "miniGit.hpp"
#include <vector>

MiniGit::MiniGit() {
    fs::remove_all(".minigit");
    fs::create_directory(".minigit");
}

MiniGit::~MiniGit() {   
    // Any postprocessing that may be required
    fs::remove_all(".minigit");
     if(commitHead->fileHead != NULL)
        cout << "checking" << endl;
}

void MiniGit::init(int hashtablesize) 
{
    fs::remove_all(".minigit");
    fs::create_directory(".minigit");
    
}

void MiniGit::add(string fileName) 
{
    // add new node
    FileNode * newFile = new FileNode;
    newFile -> name = fileName;
    newFile -> next = commitHead->fileHead;

    // check to make sure it does not already exist
    /*
    FileNode * curr = commitHead->fileHead;
    
    // if list is null add to start
    if(curr == NULL)
    {
        fileName += "00";
        FileNode * newFile = new FileNode;
        newFile -> name = fileName;
        newFile -> next = commitHead->fileHead;
    }
    else
    {
        bool check = false;
        while(curr != NULL)
        {
            if(fileName == curr->name)
            {
                check = true;
                break;
            }
            curr = curr->next;
        }
        /*
        while(check)
        {
            cout << "Enter a file name: ";
            cin >> fileName;
            check = false;
            curr = commitHead->fileHead;
            while(curr != NULL)
            {
                if(fileName == curr->name)
                {
                    check = true;
                    break;
                }
                curr = curr->next;
            }
        }
        */
    //}*/
}

void MiniGit::rm(string fileName) {
    
}



void MiniGit::printSearchTable()
{
     //ht->printTable();
}


void MiniGit::search(string key)
{
}



string MiniGit::commit(string msg) {
    return " "; //should return the commitID of the commited DLL node
}

void MiniGit::checkout(string commitID) {
   

}

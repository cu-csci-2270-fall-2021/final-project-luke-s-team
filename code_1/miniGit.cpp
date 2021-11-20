#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#include <filesystem>
namespace fs = std::filesystem;

#include "miniGit.hpp"
#include <vector>


MiniGit::MiniGit() {
    //fs::remove_all(".minigit");
    //fs::create_directory(".minigit");
}

bool MiniGit::node(string message){
    BranchNode *branchNode = commitHead;
    if(message == branchNode->commitMessage) return true;
    while(branchNode != NULL){
        if(message == branchNode->commitMessage) return true;
        branchNode = branchNode->next;
    }
    return false;
}

int MiniGit::getCommits()
{
    return commits;
}

MiniGit::~MiniGit() {   
    // Any postprocessing that may be required
    
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
    
    fs::remove_all(".minigit");
}

void MiniGit::init(int hashtablesize) 
{ 
    
    // initialize new repository
    fs::remove_all(".minigit");
    fs::create_directory(".minigit");
    
    // create new hash table
    ht = new HashTable(hashtablesize);

    
    commits = 0;

    // create new commit head to use
    commitHead = new BranchNode;
    commitHead->commitID = 0;
    commitHead->commitMessage = "";
    commitHead->fileHead = NULL;
    commitHead->next = NULL;
    commitHead->previous = NULL;
}

void MiniGit::add(string fileName) 
{
    // create new node
    FileNode * newFile = new FileNode;
    newFile -> name = fileName;
    newFile -> version = 0;
    newFile -> next = NULL;
    
    // add node to head if head is null
    if(commitHead->fileHead == NULL)
    {
        commitHead -> fileHead = newFile;
    }
    // add node to end of list
    else
    {
        bool check = false;
        // check that the file does not already exist
        FileNode * crawler = commitHead->fileHead;
        while(crawler != NULL)
        {
            if(crawler->name == fileName)
                check = true;
            crawler = crawler->next;
        }
        // check that the file exist in the directory
        if(!fs::exists(fileName))
            check = true;
        
        // if file was already in list prompt the user to try again
        if(check)
        {
            cout << "Must enter valid file name" << endl;
        }
        // add the new file to the end of the list
        else
        {
            crawler = commitHead->fileHead;
            while(crawler->next!=NULL)
                crawler = crawler->next;
            crawler->next = newFile;
        }
    }
}

void MiniGit::rm(string fileName) 
{
    // check list is not empty
    if(commitHead->fileHead == NULL)
    {
        cout << "There are no files to delete." << endl;
    }
    // files exist
    else
    {
        // check that the file is in the list
        FileNode * crawler = commitHead->fileHead;
        bool check = false;
        while(crawler != NULL)
        {
            if(crawler->name == fileName)
                check = true;
            crawler = crawler->next;
        }
        
        //  file not in list
        if(!check)
            cout << "File is not in the list" << endl;
        // file in list
        // only head node
        else if(commitHead->fileHead->next == NULL)
        {
            delete commitHead->fileHead;
            commitHead->fileHead = commitHead->fileHead->next;
        }
        // delete file from list
        else
        {
            FileNode * pres = commitHead->fileHead;
            FileNode * prev = NULL;
            
            while(pres != NULL)
            {
                if(pres->name == fileName)
                    break;
                prev = pres;
                pres = pres->next;
            }
            // check to make sure prev is not null
            if(prev != NULL) 
                prev->next = pres->next;
            delete pres;
        }
    }
}



void MiniGit::printSearchTable()
{
     ht->printTable();
}


void MiniGit::search(string key)
{
    // check if the key exists in the hash
    if(ht->searchItem(key) != NULL)
    {
        HashNode * hn = ht->searchItem(key);
        cout << hn->key << "(";
        for(int j = 0; j < hn->commitNums.size(); j+=1)
            cout << hn->commitNums[j] << ",";
        cout << ")" << endl;
    }
    else
        cout << "Key cannot be found." << endl;
}



string MiniGit::commit(string msg) 
{
    // create new node
    BranchNode * newNode = new BranchNode;
    newNode->commitMessage = msg;
    newNode->commitID = commits;
    newNode -> next = NULL;
    
    
    
    newNode->fileHead = commitHead->fileHead;
    
    // empty starting repository add everything from the SLL
    if(commits == 0)
    {
        // starting with no prev null
        newNode->previous = NULL;
        
        // add files to minigit
        FileNode * curr = commitHead->fileHead;
        while(curr != NULL)
        {
            fs::copy_file(curr->name,".minigit/"+curr->name+to_string(curr->version));
            curr = curr->next;
        }
    }
    // will be copying/adding files
    else
    {
        // has a prev node, set here
        newNode->previous = commitHead;
        
        // check if changes
        // if no changes do not commit
        bool check = false;
        
        // check for any new files and changes in files
        // do not commit if neither is found
        // this loop also updates the directory with the new file if it was changed
        // also checks if the file of a different name is not in the directory and adds it
        FileNode * curr = commitHead->fileHead;
        while(curr != NULL)
        {
            if(fs::exists(".minigit/"+curr->name+to_string(curr->version)))
            {
                fstream t1(curr->name);
                ostringstream s1;
                s1<< t1.rdbuf();
                
                fstream t2(".minigit/"+curr->name+to_string(curr->version));
                ostringstream s2;
                s2<< t2.rdbuf();
                
                if(s1.str() != s2.str())
                {
                    curr->version+=1;
                    fs::copy_file(curr->name,".minigit/"+curr->name+to_string(curr->version));
                    check = true;
                }
            }
            else
            {
                fs::copy_file(curr->name,".minigit/"+curr->name+to_string(curr->version));
                check = true;
            }
            curr = curr->next;
        }
        
        if(!check)
        {
            cout << "No changes made. Reverting to previous commit" << endl;
            delete newNode;
            return to_string(commits);
        }
    }
        
    
    // Do the final update
    newNode->previous = commitHead;
    
    commits += 1;
    commitHead = newNode;
    
    // update commits in hash table
    string currS = "";
    for(int i = 0; i < msg.size(); i+=1)
    {
        if(msg[i] == ' ')
        {
            ht->insertItem(currS, commits-1);
            currS = "";
        }
        else if(i == msg.size()-1)
        {
            currS += msg[i];
            ht->insertItem(currS, commits-1);
        }
        else
            currS += msg[i];
    }
    
    
    //should return the commitID of the commited DLL node
    return to_string(commits-1);
    
}

void MiniGit::checkout(string commitID) {
   

}



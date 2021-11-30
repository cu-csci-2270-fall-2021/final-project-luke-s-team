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
    
    if(!fs::exists(".minigit"))
        return;
    
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

// check file and update version if already in the minigit
/*
for(int i = 0; i < commits; i+=1)
    if(fs::exists(".minigit/"+fileName+to_string(i)))
        newFile -> version += 1;
*/

void MiniGit::add(string fileName) 
{
    // check minigit exists
    if(!fs::exists(".minigit"))
    {
        cout << "Must intialize" << endl;
        return;
    }
    // check on right commit
    if(commitHead->commitID != commits)
    {
        cout << "Not on most current commit. Cannot Add, remove, or commit." << endl;
        return;
    }
    // create new node
    FileNode * newFile = new FileNode;
    newFile -> name = fileName;
    newFile -> version = 0;
    newFile -> next = NULL;
    newFile->repository = fileName + "0";
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
    // check minigit exists
    if(!fs::exists(".minigit"))
    {
        cout << "Must intialize" << endl;
        return;
    }
    // check on right commit
    if(commitHead->commitID != commits)
    {
        cout << "Not on most current commit. Cannot Add, remove, or commit." << endl;
        return;
    }
    
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
    // check minigit exists
    if(!fs::exists(".minigit"))
    {
        cout << "Must intialize" << endl;
        return;
    }
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
    // check minigit exists
    if(!fs::exists(".minigit"))
    {
        cout << "Must intialize" << endl;
        return "";
    }
    
    // check on right commit
    if(commitHead->commitID != commits)
    {
        cout << "Not on most current commit. Cannot Add, remove, or commit." << endl;
        return "";
    }
    
    // create new node
    BranchNode * newNode = new BranchNode;
    newNode->commitMessage = msg;
    newNode->commitID = commits+1;
    newNode -> next = NULL;
    newNode -> fileHead = NULL;
    //newNode->fileHead = commitHead->fileHead;
    
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
                // get strings of each file
                fstream t1(curr->name);
                ostringstream s1;
                s1<< t1.rdbuf();
                
                fstream t2(".minigit/"+curr->name+to_string(curr->version));
                ostringstream s2;
                s2<< t2.rdbuf();
                
                // compare to check changes
                if(s1.str() != s2.str())
                {
                    curr->version+=1;
                    
                    // create new file in minigit
                    fstream myFileF;
                    myFileF.open(curr->name);
                    ostringstream myFileO;
                    myFileO<< myFileF.rdbuf();
        
                    
                    ofstream newFile(".minigit/"+curr->name+to_string(curr->version));
                    newFile << myFileO.str();
                    newFile.close();
                    myFileF.close();
                }
                else
                    check = true;
            }
            else
            {
                // create new file in minigit
                fstream myFileF;
                myFileF.open(curr->name);
                ostringstream myFileO;
                myFileO<< myFileF.rdbuf();


                ofstream newFile(".minigit/"+curr->name+to_string(curr->version));
                newFile << myFileO.str();
                newFile.close();
                myFileF.close();
                
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
    newNode->fileHead = commitHead->fileHead;
    
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

void MiniGit::checkout(string commitID) 
{
    // check minigit exists
    if(!fs::exists(".minigit"))
    {
        cout << "Must intialize" << endl;
        return;
    }
    int commitNum = stoi(commitID);
    if(commitNum == commitHead->commitID)
    {
        cout << "Currently on commit " << commitID << endl;
        return;
    }
    
    // double check with user 
    bool check = false; 
    string c;
    cout << "You may lose all current local changes." << endl;
    cout << "Do you want to continue? YES (y) NO (n): " << endl;
    getline(cin, c);
    
    if(c == "y" || c == "Y")
        check = true;
    if(!check)
    {
        cout << "No changes will be made." << endl;
        return;
    }
    
    // get the node with the right commit   
    BranchNode * commitNode = commitHead;
    while(commitNode != NULL)
    {
        if(commitNode->commitID == commitNum)
            break;
        commitNode = commitNode->previous;
    }
    
    // update the directory
    cout << commitNode->commitID << endl;
    FileNode * currFile = commitNode -> fileHead;
    
    while(currFile != NULL)
    {   
        if(fs::exists(currFile->name) && fs::exists(".minigit/"+currFile->name+to_string(currFile->version)))
        {
            // get string of file in the curr directory
            fstream myFileF;
            myFileF.open(currFile->name);
            ostringstream myFileS;
            myFileS<< myFileF.rdbuf();
   
            // get string of the file in the minigit
            fstream gitFileF;
            gitFileF.open(".minigit/"+currFile->name+to_string(currFile->version));
            ostringstream gitFileS;
            gitFileS<< gitFileF.rdbuf();
            
            cout << "Copying: " << gitFileS.str() << " to: " << myFileS.str() << endl;
           
            // replace string in directory with string from minigit 
            ofstream myFileO;
            myFileO.open(currFile->name);
            myFileO << gitFileS.str();
            myFileO.close();
            
            myFileF.close();
            gitFileF.close(); 
        }
        else
            cout << "file DNE" << endl;
            
        currFile = currFile -> next;
    }
    
    commitHead = commitNode;
}


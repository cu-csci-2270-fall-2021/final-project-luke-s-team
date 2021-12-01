#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#include <filesystem>
namespace fs = std::filesystem;

#include "miniGit.hpp"
#include <vector>


MiniGit::MiniGit() {
}

// this function checks if the commit message has already been used
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
    
    // if not initialized, then nothing to delete
    if(!fs::exists(".minigit"))
        return;
    
    // get the most recent commit 
    BranchNode * crawler = commitHead;
    while(crawler != NULL)
    {
        if(crawler->commitID == commits)
            break;
        if(commits < crawler->commitID)
            crawler = crawler->previous;
        else if(commits > crawler->commitID)
            crawler = crawler->next;
    }
    
    // go through each DLL and delete it
    // first delete each SLL associated with the DLL
    while(crawler != NULL)
    {
        FileNode * crawler2 = commitHead->fileHead;
        while(crawler2 != NULL)
        {
            crawler2 = commitHead->fileHead->next;
            delete commitHead->fileHead;
            commitHead->fileHead = crawler2;
        }
        crawler = commitHead->previous;
        delete commitHead;
        commitHead = crawler;
    }
    
    // remove all files from the minigit
    fs::remove_all(".minigit");
}

void MiniGit::init(int hashtablesize) 
{ 
    // do not want to initialize a minigit multiple times
    if(fs::exists(".minigit"))
    {
        cout << "Already initialized" << endl;
        return;
    }
    
    // initialize new repository
    fs::remove_all(".minigit");
    fs::create_directory(".minigit");
    
    // create new hash table
    ht = new HashTable(hashtablesize);

    // set commits to 0
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
    // check if minigit exists
    if(!fs::exists(".minigit"))
    {
        cout << "Must intialize" << endl;
        return;
    }
    // check if file exists
    if(!fs::exists(fileName))
    {
        cout << "Enter a valid file name" << endl;
        return;
    }
    // check if on most recent commit
    if(commitHead->commitID != commits)
    {
        cout << "Not on most current commit. Cannot Add, remove, or commit." << endl;
        return;
    }
    
    // create new node/ file to add to the SLL
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
    // else add node to end of list
    else
    {
        bool check = false;
        // check that the file does not already exist in the SLL
        FileNode * crawler = commitHead->fileHead;
        while(crawler != NULL)
        {
            if(crawler->name == fileName)
                check = true;
            crawler = crawler->next;
        }
        // check that the file does not already exist in the directory
        if(!fs::exists(fileName))
            check = true;
        
        // if file was already exists prompt the user to try again
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
    // check if minigit exists
    if(!fs::exists(".minigit"))
    {
        cout << "Must intialize" << endl;
        return;
    }
    // check if on most recent commit
    if(commitHead->commitID != commits)
    {
        cout << "Not on most current commit. Cannot Add, remove, or commit." << endl;
        return;
    }
    
    // check to make sure the SLL is not empty
    if(commitHead->fileHead == NULL)
    {
        cout << "There are no files to delete." << endl;
    }
    // the SLL is not empty, so can traverse to delete a file
    else
    {
        // check that the file exists in the SLL
        FileNode * crawler = commitHead->fileHead;
        bool check = false;
        while(crawler != NULL)
        {
            if(crawler->name == fileName)
                check = true;
            crawler = crawler->next;
        }
        
        //  file not in the SLL
        if(!check)
            cout << "File is not in the list" << endl;
        // file is in SLL so will remove it from the SLL
        // if the SLL only had a head node delete the head node
        else if(commitHead->fileHead->next == NULL)
        {
            delete commitHead->fileHead;
            commitHead->fileHead = commitHead->fileHead->next;
        }
        // else delete file from the SLL
        else
        {
            FileNode * pres = commitHead->fileHead;
            FileNode * prev = NULL;
            
            // find the file to remove
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
    // print the hash table
    ht->printTable();
}


void MiniGit::search(string key)
{
    // check if minigit exists
    if(!fs::exists(".minigit"))
    {
        cout << "Must intialize" << endl;
        return;
    }
    
    // check if the key exists in the hash
    // if it exist search for the key and print its commit numbers
    if(ht->searchItem(key) != NULL)
    {
        HashNode * hn = ht->searchItem(key);
        cout << hn->key << "(";
        for(int j = 0; j < hn->commitNums.size(); j+=1)
            cout << hn->commitNums[j] << ",";
        cout << ")" << endl;
    }
    // key did not exist
    else
        cout << "Key cannot be found." << endl;
}



string MiniGit::commit(string msg) 
{
    // check if minigit exists
    if(!fs::exists(".minigit"))
    {
        cout << "Must intialize" << endl;
        return "";
    }
    // check if on right commit
    if(commitHead->commitID != commits)
    {
        cout << "Not on most current commit. Cannot Add, remove, or commit." << endl;
        return "";
    }
    
    // create new node
    BranchNode * newNode = new BranchNode;
    newNode->commitMessage = "";
    newNode->commitID = commits+1;
    newNode -> next = NULL;    
    newNode -> fileHead = NULL;
    
    // create a deep copy of the previous SLL for newNode
    FileNode * newLL = new FileNode;
    newNode -> fileHead = newLL;
    FileNode * crawlLL = commitHead->fileHead;
    while(crawlLL != NULL)
    {
        newLL -> name = crawlLL -> name;
        newLL -> version = crawlLL -> version;
        newLL -> repository = crawlLL -> repository;
        if(crawlLL->next == NULL)
            newLL -> next = NULL;
        else
            newLL -> next = new FileNode;
        
       newLL = newLL -> next;
       crawlLL = crawlLL->next;
    }
    
    // empty starting repository add everything from the SLL to minigit
    if(commits == 0)
    {
        // starting with no prev null
        newNode->previous = NULL;
        
        // add files to minigit
        FileNode * curr = newNode->fileHead;
        while(curr != NULL)
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
            
            curr = curr->next;
        }
    }
    // will be copying/adding files
    else
    {        
        // check if changes made
        // if no changes do not commit
        bool check = false;
        
        // check for any new files and changes in files
        // do not commit if neither is found
        // this loop also updates the directory with the new file if it was changed
        // also checks if the file of a different name is not in the directory and adds it
        
        FileNode * curr = newNode->fileHead;
        FileNode * commitCurr = commitHead -> fileHead;
        // crawl through the SLL
        while(curr != NULL)
        {
            // check if file already exists in the minigit
            // if already in minigit check for any changes
            // if changes update the version of the fil in the SLL and add that version with the new data to the minigit
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
                    // update file in the SLL
                    commitCurr->version+=1;
                    commitCurr->repository= commitCurr->name + to_string(commitCurr->version);
                    curr->version+=1;
                    curr->repository = curr->name + to_string(curr->version);
                    
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
            }
            // file was not in the minigit so add it to the minigit
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
            commitCurr = commitCurr->next;
        }
        
        // no changes found in the SLL so do not commit
        if(!check)
        {
            cout << "No changes made. Reverting to previous commit" << endl;
            delete newNode;
            return to_string(commits);
        }
    }
        
    
    // Do the final update
    newNode->previous = commitHead;
    commitHead->next = newNode;
    
    FileNode * ccl = newNode -> fileHead;
    int ii = 0;
    while(ccl != NULL)
    {
        cout << ii << ": " << ccl->name << ccl->version<< endl;
        ccl = ccl->next;
        ii+=1;
    }
    
    commits += 1;
    commitHead -> commitMessage = msg;
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
        if(commitNum < commitNode->commitID)
            commitNode = commitNode->previous;
        else if(commitNum > commitNode->commitID)
            commitNode = commitNode->next;
    }
    
    // update the directory
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
            
            
            if(myFileS.str() != gitFileS.str())
            {
                cout << "Copying: " << gitFileS.str() << " to: " << myFileS.str() << endl;

                // replace string in directory with string from minigit 
                ofstream myFileO;
                myFileO.open(currFile->name);
                myFileO << gitFileS.str();
                myFileO.close();
            }
            
            myFileF.close();
            gitFileF.close(); 
            
        }
        else
            cout << "file DNE" << endl;
            
        currFile = currFile -> next;
    }
    
    commitHead = commitNode;
    
}


// CPP program to implement hashing with chaining
#include<iostream>
#include "hash.hpp"


using namespace std;

HashNode* HashTable::createNode(string key, HashNode* next)
{
    HashNode* nw = new HashNode;
    nw->key = key;
    nw->next = next;
    return nw;
}

HashTable::HashTable(int bsize)
{
    tableSize= bsize;
    table = new HashNode*[tableSize];
    for(int i=0;i<bsize;i++)
        table[i] = nullptr;
}

//function to calculate hash function
unsigned int HashTable::hashFunction(string s)
{
    // use division method to create a hash
    int sum = 0;
    for(int i = 0; i < s.size(); i+=1)
        sum += s[i];
    sum %= tableSize;
    return sum;
}

// TODO Complete this function
//function to search
HashNode* HashTable::searchItem(string key)
{
    int i = hashFunction(key);
    HashNode * curr = table[i];
    while(curr != NULL)
    {
        if(curr->key == key)
            return curr;
        curr = curr->next;
    }
    return NULL; 
}

//TODO Complete this function
//function to insert
bool HashTable::insertItem(string key, int cNum)
{
    // word is not in hash, update with new word
    if(!searchItem(key))
    {
        int i = hashFunction(key);
        // create new hash
        HashNode * newHash = createNode(key,table[i]);
        newHash -> commitNums.push_back(cNum);
        table[i] = newHash;
        
        return true;
    }
    // word is already in hash, add cNum to its commmitNums
    else
    {
        HashNode * hn = searchItem(key);
        hn->commitNums.push_back(cNum);
        
    }
    return false;
}


// function to display hash table //
/* assume the table size is 5. For each bucket it will show the 
** the string key and the commit number (separated by comma) within parenthesis
** e.g. the key is science and commit numbers are 1 and 4. The key science
** is hashed to position 0. So the print format will be-

0|| science(1,4,)
1|| 
2|| 
3|| 
4|| difficult(3,)-->fun(2,)-->computer(0,)

*/
void HashTable::printTable()
{
    for(int i = 0; i < tableSize; i+=1)
    {
        cout << i << "// ";
        HashNode * curr = table[i];
        while(curr != NULL)
        {
            cout << curr->key << "(";
            for(int j = 0; j < curr->commitNums.size(); j+=1)
                cout << curr->commitNums[j] << ",";
            if(curr->next == NULL)
                cout << ")";
            else
                cout << ")-->";
            curr = curr->next;
        }
        cout << endl;
    }
}



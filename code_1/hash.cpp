// CPP program to implement hashing with chaining
#include<iostream>
#include "hash.hpp"


using namespace std;

HashNode* HashTable::createNode(string key, HashNode* next)
{
    HashNode* nw = NULL;
    return nw;
}

HashTable::HashTable(int bsize)
{
    tableSize = bsize;
    table[tableSize];
    for(int i = 0; i < tableSize; i+=1)
        table[i] = NULL;
}

//function to calculate hash function
unsigned int HashTable::hashFunction(string s)
{
    // use division method to create a hash
    int sum = 0;
    for(int i = 0; i < s.size(); i+=1)
        sum += s[i];
    sum %= tableSize;
    
    // use linear probing to fix collisions
    while(table[sum] != NULL)
    {
        sum += 1;
        if(sum < tableSize)
            sum = 0;
    }
    
    return sum;
}

// TODO Complete this function
//function to search
HashNode* HashTable::searchItem(string key)
{
    for(int i = 0; i < tableSize; i+=1)
        if(table[i]->key == key)
            return table[i];
    return NULL; 
}

//TODO Complete this function
//function to insert
bool HashTable::insertItem(string key, int cNum)
{
    HashNode * newNode = new HashNode;
    newNode -> key = key;
    newNode -> commitNums.push_back(cNum);
    
    int hash = hashFunction(key);
    table[hash] = newNode;
    
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
        cout << table[i]->key << "(";
        for(int j = 0; j < table[i]->commitNums.size();j+=1)
            cout << table[i]->commitNums[j] << ", ";
        cout << endl;
    }
}

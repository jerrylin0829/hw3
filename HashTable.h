#include <bits/stdc++.h>

using namespace std;

class HashTable
{
    public:
        int arr_size;

        int *randomNum; 

        list<int> *arr;

        HashTable(int);

        void insertItem(int, int);

        bool searchItem(int, int);

        int hashFunction(int, int);

        bool isPrime(int);

        int nextPrime(int);


};

HashTable::HashTable(int size)
{
    arr_size = nextPrime(size);
    arr = new list<int>[arr_size];
    randomNum = new int[4];
    randomNum[0] = rand()%arr_size;
    randomNum[1] = rand()%arr_size;
    randomNum[2] = rand()%arr_size;
    randomNum[3] = rand()%arr_size; 
}

void HashTable::insertItem(int key, int prime)
{
    int i = hashFunction(key, prime);
    arr[i].push_back(key);
}

bool HashTable::searchItem(int key, int prime)
{
    int i = hashFunction(key, prime);
    for(list<int>:: iterator it = arr[i].begin (); it != arr[i].end ();  ++it){
        if(*it == key)
            return true;
    }
    return false;
}

int HashTable::hashFunction(int key, int prime)
{
    unsigned int bytes[4];
    unsigned long n = key;

    bytes[0] = (n >> 24) & 0xFF;
    bytes[1] = (n >> 16) & 0xFF;
    bytes[2] = (n >> 8) & 0xFF;
    bytes[3] = (n >> 0) & 0xFF;

    int x1 = bytes[0];
    int x2 = bytes[1];
    int x3 = bytes[2];
    int x4 = bytes[3];  

    return (x1*randomNum[0] + x2*randomNum[1] + x3*randomNum[2] + x4*randomNum[3]) % prime;    
}

bool HashTable::isPrime(int n)
{
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;

    if (n % 2 == 0 || n % 3 == 0)
        return false;

    for (int i = 5; i * i <= n; i = i + 6){
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

int HashTable::nextPrime(int N)
{
    int p = N;
    bool found = false;

    while(!found){
        p++;

        if(isPrime(p))
            found = true;
    }

    return p;    
}

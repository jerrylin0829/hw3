#include <bits/stdc++.h>
#include <fstream>
#include "HashTable.h"

using namespace std;

int main()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<unsigned long long> dis(1, pow(2, 30));

   

    int number;
    double ans1;
    double ans2;

    for (int pow = 10; pow <= 30; ++pow)
    { 
        
        fstream input_file;
        fstream output_file;
        
        int num = 1 << pow;
        HashTable hash(num);
        int prime = hash.nextPrime(num);

        clock_t start, end;

        input_file.open("input/" + to_string(pow) + ".txt");

        if (input_file.is_open())
        {

            start = clock();

            for (int i = 0; i < num; ++i)
            {
                input_file >> number;
                hash.insertItem(number, prime);
            }

            end = clock();

            ans1 = ((double)(end - start)) / CLOCKS_PER_SEC;

            start = clock();

            for (int i = 0; i < 100000; ++i)
            {
                hash.searchItem(rand(), prime);
            }

            end = clock();

            ans2 = ((double)(end - start)) / CLOCKS_PER_SEC;

            output_file.open("result/result_5.dat", ios::app);
            if (output_file.is_open())
            {
                output_file << "2^" << pow << ", " << ans1 << ", " << ans2 << endl;
            }
        }
        input_file.close();
    }

    return 0;
}

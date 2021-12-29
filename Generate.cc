#include <bits/stdc++.h>
#include <unistd.h>
#include <time.h>
#include <fstream>
#include <string>
#include <random>
using namespace std;

int main(){

    for(int i = 10; i <= 30; ++i){
        
        sleep(1);
        ofstream myfile;
        myfile.open("input/" + to_string(i) + ".txt");
        unsigned int seed = time(NULL);
        mt19937 gen(seed);
        uniform_int_distribution<> distr(1,pow(2,30));

        for(int j = 0; j < pow(2, i); ++j){
            myfile << distr(gen) << " ";
        }
    }
}

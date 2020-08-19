// Lawrence Chan
// COMP15 Hash Example
// 3/30/2019 
// Edits: 3/31/2019
// example of hashing function to generate hashes; insertion
// compile: clang++ -std=c++11 -o hashEx hashExample.cpp
// run    : ./hashEx

#include <iostream>
#include <string>
#include <functional>

using namespace std;

const int RAYSIZE = 7;

int main(){
        //setup
        string inputRay[RAYSIZE] = {"penguins", 
                                    "harpseals", 
                                    "polarbears", 
                                    "seagulls", 
                                    "walruses",
                                    "articfoxes",
                                    "narwhals"};

        string animalRay[RAYSIZE]; // initalized to all "-1"
        for (int i = 0; i < RAYSIZE; i++){
            animalRay[i] = "-1";
        }

        //showing hash and compressed
        cout << "string_tohash\thash\t\t\tcompressed" << endl;
        for (int i = 0; i < RAYSIZE; i++)
            cout << inputRay[i] << "\t" //input
                 << hash<string>{}(inputRay[i]) << "\t" //hashing
                 << hash<string>{}(inputRay[i]) % RAYSIZE //compression
                 << endl;

        cout << endl;

        //inserting if and only if no collision
        for (int i = 0; i < RAYSIZE; i++){
            int index = hash<string>{}(inputRay[i]) % RAYSIZE;
            if (animalRay[index] == "-1"){
                cout << "inserting " << inputRay[i] 
                     << "\t at " << index << endl;
                animalRay[index] = inputRay[i];
            }
            else
                cout << "unable to insert " << inputRay[i] << " at " << index 
                     << " -- collision with " << animalRay[index] << endl;
        }

        cout << endl;

        //final array print
        cout << "Final array: ";
        for (int i = 0; i < RAYSIZE; ++i){
            cout << animalRay[i];
            if (i < RAYSIZE -1)
                cout << " | ";
            else
                cout << endl;
        }
        return 0;
}

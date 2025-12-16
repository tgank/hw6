#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        //w array stores BASE-36 vals for 6-group chars
        unsigned long long w[5] = {0, 0, 0, 0, 0}; 

        int stringLength = k.length();

        //w array filled right -> left
        int wordIndx = 4;

        //process str in groups of 6 end -> front
        for(int i = stringLength - 1; i >= 0 && wordIndx >= 0; i -=6){
            //calc starting pos of group
            int group_s;
            if( i - 5 >= 0) 
            //group of 6
              group_s = i - 5;
            else 
            //partial group @ string's start
              group_s = 0;
            

            unsigned long long group_val = 0;
            unsigned long long base_36 = 1; //36 to the power of 0

            //base-36 -> dec
            //right -> left 
            for(int j = i; j >= group_s; j--){
                unsigned long long digit_val = letterDigitToNumber(k[j]);
                group_val += digit_val * base_36;
                base_36 *= 36; //next digit
            }

            w[wordIndx] = group_val;

            //next index in w
            wordIndx --;
        }

        //hash formula
        unsigned long long hash_val = 0;
        for(int i = 0; i < 5; i++){
            hash_val += rValues[i] * w[i];
        }

        return hash_val;
        

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if(letter >= 'A' && letter <= 'Z'){
        //ASCII for conversion
            letter = letter - 'A' + 'a'; 
        }

        if(letter >= 'a' && letter <= 'z'){
        //map lowercase
            return letter - 'a';
        }
        else if(letter >= '0' && letter <= '9'){
        //map digits
            return (letter - '0') + 26;
        }

        return 0;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif

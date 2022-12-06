// Names: Nadia Sousa, Yashaswini Mandalam, C. Wyatt Polasek, Sean Phelan
// Term Project: StringSearch1 - stringSearch.cpp
// File to run our string search algorithm

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<iomanip>

//This program uses the Rabin Karp or Boyer Moore algorithm to find a certain pattern in a text
// Compile instructions:
// For Rabin Karp ->  ./stringSearch filename pattern rb 
// For Boyer Moore -> ./stringSearch filename pattern bm

// tasks - rk function
//parameters is large string and small string
//necessary numbers:
//length of big string
//length of pattern
//hash value of text, hash value of pattern
//a prime number to mod
//a d value to multiply

// Rabin Karp Function
int rabinKarp(std::string pattern, std::string* bigStr){
    //Declaration of variables to be used
        //Pattern Length
    int patLen = pattern.size();
        //Text Length
    int textLen = bigStr->size();
        //Pattern Hash
    int patHash = 0;
        //Text Hash
    int textHash = 0;
        //Found Count
    int found = 0;
        //Incremental and hold variables
    int mod = 2147483647;
    int d = 256;
    int h = 1;
    int i, j;

//Calculates the power of h used to determine hash
    for(i = 0; i < patLen - 1; i++){
        h = (h * d) % mod;
    }

//Calculate hash of pattern and first window of text
    for(i = 0; i < patLen; i++){
        patHash = (d * patHash + pattern[i]) % mod;
        textHash = (d * textHash + (*bigStr)[i]) % mod; 
    }


    for(i = 0; i <= (textLen - patLen); i++){

            //Checks hash values are equal, then compare the characters
        if(patHash == textHash){
            for(j = 0; j < patLen; j++){
                if((*bigStr)[i + j] != pattern[j]){
                    break;
                }
            }

            //Increment found if all characters match
        if(j == patLen){
            found++;
        }
    }

        if(i < textLen - patLen){

                //Calculates hash for next window of characters
            textHash = (d * (textHash - (*bigStr)[i] * h) + (*bigStr)[i + patLen]) % mod;

            if(textHash < 0){
                textHash = textHash + mod;
            }
        }
    }

    return found;
}

// Badchar Shift Function
    //Preprocessing for shift table used in the Boyer Moore function
void badcharShift(std::string pattern, std::vector<int>* shifts){

        //Default store a shift = pattern length
    for(int i = 0; i < 256; i++){
        shifts->push_back(-1);
    }

        //Calculates and inserts shifts for letters that are present in the pattern
    for(int i = 0; i < pattern.size(); i++){
        (*shifts)[(int) pattern[i]] = i;
    }
}

// Boyer Moore Function
int boyerMoore(std::string pattern, std::string *bigStr, std::vector<int>* shifts){
    //Declaration of variables to be used
        //Pattern Length
    int patLen = pattern.size();
        //Text Length
    int textLen = bigStr->size();
        //Incremental and hold variables
    int idx = 0;
    int found = 0;
    int j;


    //While loop to conitinue until the end of the text
    while(idx <= textLen - patLen){

        j = patLen - 1;
            //loop to check if the characters match
        while(j >= 0 && pattern[j] == (*bigStr)[idx + j]){
            j--;
        }

            //Increments found if all characters match
        if(j < 0){
            found++;
            if(idx + patLen < textLen){
                idx = idx + patLen - (*shifts)[(*bigStr)[idx + patLen]];
            }
        }

            //If there is a mismatch, gets the shift from shift vector
        if(j >= 0){
            idx = idx + std::max(1, j - (*shifts)[(*bigStr)[idx + j]]);
        }
    }

    return found;
}

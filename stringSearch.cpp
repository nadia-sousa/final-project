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

// Readfile Function
    //Reads all characters from the file into a variable called bigStr
void readFile(std::string filename, std::string* bigStr){
        //Opens file with the name 'filename'
    std::ifstream file(filename);
        //Reads the string in the first line to a pointer of the string variable 'bigStr'
    std::string temp;
    while(std::getline(file, temp)){
        (*bigStr) += temp;
    }
}


// tasks - main
//get input string, file name and type of algorithm
//read the file and store characters into a string
//rb for rabin karp, bm for boyer moore
//pass the input string and big string into the RK or BM function

// Main Function
int main(int argc, char* argv[]){

//Reading input from command line arguments
        //Filename
    std::string filename = argv[1];
        //String to search for
    std::string inStr = argv[2];
        //Choice for either the Rabin Karp or Boyer Moore algorithm
    std::string algorithm = argv[3];
        //Variable to hold the string to be searched through
    std::string bigStr;
        //Vector to hold shifts
    std::vector<int> shifts;
        //Number of instances where the input string was found
    int found;

//Declares time function to track overall runtime
    clock_t start, end;

    //Takes time value at start of function
    start = clock();

//Calls the readfile function to read bigStr from filename
    readFile(filename, &bigStr);
//Determines which algorithm should be used based on user input
        //Rabin Karp algorithm
    if(algorithm == "rb"){

            //Calls algorithm and reads the retern value into the found variable
        found = rabinKarp(inStr, &bigStr);

            //Takes time value at the end of the Rabin Karp algorithm
        end = clock();

            //Output for algorithm used
        std::cout << "\nUsing the Rabin Karp Algorithm:\n";
    }
        //Boyer Moore algorithm
    else{

            //This function stores shifts into the shifts vector
        badcharShift(inStr, &shifts);
            //Calls algorithm and reads the retern value into the found variable
        found = boyerMoore(inStr, &bigStr, &shifts);

            //Takes time value at the end of the Boyer Moore algorithm
        end = clock();

            //Output for algorithm used
        std::cout << "\nUsing the Boyer Moore Algorithm:\n";
    }

//Calculate and display time
    double timeElapsed = ( double(end - start) / double(CLOCKS_PER_SEC) );
    // std::cout << "Time Elapsed: " << std::fixed << timeElapsed << std::setprecision(5) << "sec(s)\n\n";

//Final output
        //Number of instances found and time elapsed
    std::cout << "(" << found << ") instances of '" << inStr << "' found in " << std::fixed << timeElapsed << std::setprecision(5) << "sec(s)\n\n";    
}

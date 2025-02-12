#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>

// using namespace std;

/**
 * Are you a good square calculator ?
 **/

int sq(int N){
    return N*N;
}

std::string threelsGood(int N){
    if(N%3 == 0) return "threelsGood";
    else return std::to_string(N);
}

int main(int argc, char *argv[])
{
    int n; // The number of integers to be squared
    std::cin >> n; std::cin.ignore();
    std::string stream;
    for (int i = 0; i < n; i++) {
        int s; // An integer to be squared
	std::cin >> s; std::cin.ignore();
	stream += threelsGood(sq(s)) + " ";        
    }



    // Write an answer using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    std::cout << stream << std::endl; // answer: A list of elements joined by spaces
    return 0;
}

// g++ -std=c++17 codeClash_threalsGood.cpp -o ccThrealsGood

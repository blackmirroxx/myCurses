#include <iostream>
#include <vector>
#include <cstdint>
#include <fstream>
#include <list>
#include <algorithm> // find_if() ... 

// prototype 
int leastPrimeGreaterThan(int);

// using namespace std;

int main(void){
  auto test = 1.0/4.0; // int or float ? 
  int p = 0;
  std::cout << test << std::endl;
  std::cout << "least prime greater than: " << std::endl;
  std::cin >> p;
  std::cout << "is " << leastPrimeGreaterThan(p) << std::endl; 
  return 0;
}

// lambda prime
int leastPrimeGreaterThan(int b){
   std::vector <int> primes {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
   
   return *std::find_if(primes.begin(), primes.end(), [b] (int v) {return v > b; }); 
}

// compile it with g++ -std=c++17

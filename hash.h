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
        if(false == debug){   generateRValues(); }}
    HASH_INDEX_T operator()(const std::string& k) const
    {
        std::vector<unsigned long long> convertedValues(5, 0);  
        std::string cleanedStr;
        
        for (char ch : k) {
            if (std::isalnum(ch)) { cleanedStr += std::tolower(ch); }
        } int strLen = cleanedStr.length();
        int numGroups = (strLen + 5) / 6;  

 // Process each 6-character group starting from the end
        for (int i = 0; i < numGroups; i++) {
            int startPos = std::max(0, strLen - 6 * (i + 1));
  int endPos = strLen - 6 * i;
       std::string group = cleanedStr.substr(startPos, endPos - startPos);

   unsigned long long val = 0;
    unsigned long long power = 1;
            for (int j = group.size() - 1; j >= 0; --j) {
   val += letterDigitToNumber(group[j]) * power;
    power *= 36;
            }

            convertedValues[4 - i] = val;  
 }

        // compute final hash value using the r-values
        HASH_INDEX_T resultHash = 0;
        for (int i = 0; i < 5; ++i) {
            resultHash += convertedValues[i] * rValues[i];
        }

        return resultHash;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if (std::isdigit(letter)) {
            return static_cast<HASH_INDEX_T>(letter - '0' + 26);
        }
        return static_cast<HASH_INDEX_T>(letter - 'a');
    }

    void generateRValues()
    {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator(); }  }
};

#endif
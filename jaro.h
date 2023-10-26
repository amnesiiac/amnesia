#ifndef JAROWINKLER_H_
#define JAROWINKLER_H_

// ref: https://github.com/TriviaMarketing/Jaro-Winkler/tree/master

#include <string>
#include <algorithm>

const double JARO_WEIGHT_STRING_A(1.0/3.0);
const double JARO_WEIGHT_STRING_B(1.0/3.0);
const double JARO_WEIGHT_TRANSPOSITIONS(1.0/3.0);

const unsigned long int JARO_WINKLER_PREFIX_SIZE(4);
const double JARO_WINKLER_SCALING_FACTOR(0.1);
const double JARO_WINKLER_BOOST_THRESHOLD(0.7);

// declaration
double jaroDistance(const std::string& a, const std::string& b);
double jaroWinklerDistance(const std::string&a, const std::string& b);

// definition
double jaroDistance(const std::string& a, const std::string& b){
    // register strings length
    int aLength(a.size());
    int bLength(b.size());
    
    // if one string has null length, we return 0.
    if(aLength == 0 || bLength == 0){
        return 0.0;
    }
    
    // calculate max length range
    int maxRange(std::max(0, std::max(aLength, bLength)/2-1));
    
    // creates 2 vectors of integers
    std::vector<bool> aMatch(aLength, false);
    std::vector<bool> bMatch(bLength, false);
    
    // calculate matching characters
    int matchingCharacters(0);
    for(int aIndex(0); aIndex<aLength; ++aIndex){
        // calculate window test limits (limit inferior to 0 and superior to bLength)
        int minIndex(std::max(aIndex-maxRange, 0));
        int maxIndex(std::min(aIndex+maxRange+1, bLength));
        
        if(minIndex >= maxIndex){
            // no more common character because we don't have characters in b to test with characters in a
            break;
        }
        
        for(int bIndex(minIndex); bIndex<maxIndex; ++bIndex){
            if (!bMatch.at(bIndex) && a.at(aIndex) == b.at(bIndex)){
                // found some new match
                aMatch[aIndex] = true;
                bMatch[bIndex] = true;
                ++matchingCharacters;
                break;
            }
        }
    }
    
    // if no matching characters, we return 0
    if(matchingCharacters == 0){
        return 0.0;
    }
    
    // calculate character transpositions
    std::vector<int> aPosition(matchingCharacters, 0);
    std::vector<int> bPosition(matchingCharacters, 0);
    
    for(int aIndex(0), positionIndex(0); aIndex<aLength; ++aIndex){
        if(aMatch.at(aIndex)){
            aPosition[positionIndex] = aIndex;
            ++positionIndex;
        }
    }
    
    for(int bIndex(0), positionIndex(0); bIndex<bLength; ++bIndex){
        if(bMatch.at(bIndex)){
            bPosition[positionIndex] = bIndex;
            ++positionIndex;
        }
    }
    
    // counting half-transpositions
    int transpositions(0);
    for(int index(0); index<matchingCharacters; ++index){
        if(a.at(aPosition.at(index)) != b.at(bPosition.at(index))){
            ++transpositions;
        }
    }
    
    // calculate Jaro distance
    return (
        JARO_WEIGHT_STRING_A * matchingCharacters / aLength +
        JARO_WEIGHT_STRING_B * matchingCharacters / bLength +
        JARO_WEIGHT_TRANSPOSITIONS * (matchingCharacters-transpositions/2) / matchingCharacters
    );
}

double jaroWinklerDistance(const std::string&a, const std::string& b){
    // calculate Jaro distance
    double distance(jaroDistance(a, b));
    
    if (distance > JARO_WINKLER_BOOST_THRESHOLD){
        // calculate common string prefix
        int commonPrefix(0);
        for(int index(0), indexEnd(std::min(std::min(a.size(), b.size()), JARO_WINKLER_PREFIX_SIZE)); index<indexEnd; ++index){
            if(a.at(index) == b.at(index)){
                ++commonPrefix;
            }
            else{
                break;
            }
        }
        // calculate Jaro-Winkler distance
        distance += JARO_WINKLER_SCALING_FACTOR * commonPrefix * (1.0-distance);
    }
    return distance;
}

#endif // JAROWINKLER_HPP


#ifndef LEVEN_H_
#define LEVEN_H_

// ref: https://github.com/guilhermeagostinelli/levenshtein

#include <iostream>
#include <string.h>
#include <math.h>
#include <algorithm>

// declaration
int levenshteinDist(string word1, string word2);

// definition
int levenshteinDist(string word1, string word2){
    int size1 = word1.size();
    int size2 = word2.size();
    int verif[size1+1][size2+1]; // verification matrix: 2d arr to store the calculated distance

    // if one of the words has zero length, the distance is equal to the size of the other word.
    if(size1 == 0){
        return size2;
    }
    if(size2 == 0){
        return size1;
    }

    // sets the first row and the first column of the verification matrix with the numerical order from 0 to the length of each word.
    for(int i=0; i<=size1; i++){
        verif[i][0] = i;
    }
    for(int j=0; j<=size2; j++){
        verif[0][j] = j;
    }

    // verification step / matrix filling.
    for(int i=1; i<=size1; i++){
        for(int j=1; j<=size2; j++){
            // sets modification cost.
            // 0 means no modification (i.e. equal letters) and 1 means that a modification is needed (i.e. unequal letters).
            int cost = (word2[j-1] == word1[i-1]) ? 0 : 1;

            // sets the current position of the matrix as the minimum value between a (deletion), b (insertion) and c (substitution).
            // a = the upper adjacent value plus 1: verif[i-1][j] + 1
            // b = the left adjacent value plus 1: verif[i][j-1] + 1
            // c = the upper left adjacent value plus the modification cost: verif[i-1][j-1] + cost
            verif[i][j] = std::min(
                std::min(verif[i-1][j] + 1, verif[i][j-1] + 1),
                verif[i-1][j-1] + cost
            );
        }
    }

    // the last position of the matrix will contain the Levenshtein distance.
    return verif[size1][size2];
}

#endif


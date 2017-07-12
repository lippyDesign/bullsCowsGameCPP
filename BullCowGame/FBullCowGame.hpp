//
//  FBullCowGame.hpp
//  BullCowGame
//
//  Created by Volodymyr Lipunov on 7/11/17.
//  Copyright © 2017 Volodymyr Lipunov. All rights reserved.
//

#ifndef FBullCowGame_hpp
#define FBullCowGame_hpp

#include <stdio.h>

#include <string>

#endif /* FBullCowGame_hpp */

using FString = std::string;
using int32 = int;

// all values initialized to 0
struct FBullCowCount {
    int32 Bulls = 0;
    int32 Cows = 0;
};

enum class EGuessStatus {
    OK,
    Not_Isogramm,
    Wrong_Length,
    Not_Lowercase
};

enum class EResetStatus {
    OK,
    Not_Hidden_Word
};

class FBullCowGame {
public:
    FBullCowGame(); // constructor
    int32 GetMaxTries() const;
    int32 GetCurrentTry() const;
    int32 GetHiddenWordLength() const;
    bool IsGameWon() const;
    EGuessStatus CheckGuessValidity(FString) const; // TODO make a richer return value
    void Reset(); // TODO make a richer return value
    FBullCowCount SubmitGuess(FString); // counts bulls and cows and increases try # assuming valid guess
    
private:
    // see constructor for initialization
    int32 MyCurrentTry;
    int32 MyMaxTries;
    FString MyHiddenWord;
};

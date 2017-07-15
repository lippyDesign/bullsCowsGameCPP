//
//  FBullCowGame.hpp
//  BullCowGame
//
//  Created by Volodymyr Lipunov on 7/11/17.
//  Copyright © 2017 Volodymyr Lipunov. All rights reserved.
//
#pragma once
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
    Invalid_Status,
    OK,
    Not_Isogram,
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
    bool IsHiddenWordSelected() const;
    bool CheckLengthValidity(FString) const;
    bool IsGameWon() const;
    EGuessStatus CheckGuessValidity(FString) const;
    void Reset();
    void SetHiddenWord(int32);
    FBullCowCount SubmitValidGuess(FString); // counts bulls and cows and increases try # assuming valid guess input
    
private:
    // see constructor for initialization
    int32 MyCurrentTry;
    FString MyHiddenWord;
    bool HiddenWordSelected;
    bool bGameIsWon;
    bool IsIsogram(FString) const;
    bool IsLowercase(FString) const;
};

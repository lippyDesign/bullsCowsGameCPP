//
//  FBullCowGame.cpp
//  BullCowGame
//
//  Created by Volodymyr Lipunov on 7/11/17.
//  Copyright © 2017 Volodymyr Lipunov. All rights reserved.
//

#include "FBullCowGame.hpp"
#include <map>
#define TMap std::map;

FBullCowGame::FBullCowGame() {
    Reset();
}

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

void FBullCowGame::Reset() {
    constexpr int32 MAX_TRIES = 8;
    MyMaxTries = MAX_TRIES;
    
    const FString HIDDEN_WORD = "planet";
    MyHiddenWord = HIDDEN_WORD;
    
    MyCurrentTry = 1;
    
    bGameIsWon = false;
    
    return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const {
    // if the guess isn't an isogram
    if(!bIsIsogram(Guess)) {
        return EGuessStatus::Not_Isogramm;
    } else if (false) { // if the guess isn't all lower case
        return EGuessStatus::Not_Lowercase;
    } else if (Guess.length() != GetHiddenWordLength()) { // if the guess length is wrong
        return EGuessStatus::Wrong_Length;
    } else { //otherwise
        return EGuessStatus::OK;
    }
}

// recieves a valid guess, increments turn and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) {
    //increment the turn
    MyCurrentTry ++;
    
    // setup a return variable
    FBullCowCount BullCowCount;
    
    int32 HiddenWordLength = GetHiddenWordLength();
    //loop through all letters in the hidden word
    for (int32 MHWChar= 0; MHWChar < HiddenWordLength; MHWChar++) {
        // compare letters against the guess
        for (int32 GChar = 0; GChar < HiddenWordLength; GChar++) {
            // if they match
            if (Guess[GChar] == MyHiddenWord[MHWChar]) {
                //if they are in the same place
                if (MHWChar == GChar) {
                    // increment bulls
                    BullCowCount.Bulls++;
                // else
                } else {
                    //implement cows
                    BullCowCount.Cows++;
                }
            }
        }
    }
    
    if (BullCowCount.Bulls == HiddenWordLength) {
        bGameIsWon = true;
    } else {
        bGameIsWon = false;
    }
    
    return BullCowCount;
}

bool FBullCowGame::bIsIsogram(FString Word) const {
    // treat 0 and 1 letter words as isograms
    
    // loop through all the letters of the word
        // if the letter is in the map
            // we do not have an isogram
    
        // otherwise
            // add the letter to the map
    return true;
}


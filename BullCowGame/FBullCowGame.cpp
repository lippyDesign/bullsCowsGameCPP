//
//  FBullCowGame.cpp
//  BullCowGame
//
//  Created by Volodymyr Lipunov on 7/11/17.
//  Copyright © 2017 Volodymyr Lipunov. All rights reserved.
//

#include "FBullCowGame.hpp"
#include <map>
#define TMap std::map

FBullCowGame::FBullCowGame() { // default constructor
    Reset();
}

int32 FBullCowGame::GetMaxTries() const {
    TMap<int32, int32> WordLengthToMaxTries { {3,4}, {4,7}, {5,10}, {6,16}, {7,20} };
    return WordLengthToMaxTries[MyHiddenWord.length()];
}

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

void FBullCowGame::Reset() {
    
    const FString HIDDEN_WORD = "pla";
    MyHiddenWord = HIDDEN_WORD;
    
    MyCurrentTry = 1;
    
    bGameIsWon = false;
    
    return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const {
    // if the guess isn't an isogram
    if(!IsIsogram(Guess)) {
        return EGuessStatus::Not_Isogram;
    } else if (!IsLowercase(Guess)) { // if the guess isn't all lower case
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

bool FBullCowGame::IsIsogram(FString Word) const {
    // treat 0 and 1 letter words as isograms
    if (Word.length() <= 1) { return true; }
    // set up our map
    TMap <char, bool> LetterSeen;
    // loop through all the letters of the word
    for (auto Letter : Word) { // auto means we don't care about the type of Letter
        Letter = tolower(Letter);
        // if the letter is in the map
        if (LetterSeen[Letter] == true) {
            // we do not have an isogram
            return false;
        } else {
            // add the letter to the map
            LetterSeen[Letter] = true;
        }
    }
    return true;
}

bool FBullCowGame::IsLowercase(FString Word) const {
    // treat 0 and 1 letter words as passing so we could catch them in another method
    if (Word.length() <= 1) {return true; }
    // loop over every letter in the word
    for (auto Letter : Word) {
        // if letter is not lowercase, return early (false)
        if (!islower(Letter)) { return false; }
    }
    // if we did not have an early return, than all letters must be lower case
    return true;
}


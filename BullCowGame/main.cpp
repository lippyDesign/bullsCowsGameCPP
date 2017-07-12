//
//  main.cpp
//  BullCowGame
//
//  Created by Volodymyr Lipunov on 7/10/17.
//  Copyright © 2017 Volodymyr Lipunov. All rights reserved.
//

/*
 This is the console executable that makes use of the BullCowClass.
 This acts as the view in MVC patern and is responsible for all user interaction.
 For game logic see the FBullCowGame Class
*/

#include <iostream>
#include <string>
#include "FBullCowGame.hpp"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetGuess();
bool AskToPlayAgain();

FBullCowGame BCGame; // instantiate a new game

// entry point for application
int main() {
    bool bPlayAgain = false;
    do {
        PrintIntro();
        PlayGame();
        bPlayAgain = AskToPlayAgain();
    } while (bPlayAgain);
    
    return 0;
}

// introduce the game
void PrintIntro() {
    const int32 WORD_LENGTH = BCGame.GetHiddenWordLength();
    std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
    std::cout << "Can you guess the " << WORD_LENGTH;
    std::cout << " letter isogram I'm thinking off?\n";
    std::cout << std::endl;
    return;
}

void PlayGame() {
    
    BCGame.Reset();
    
    int32 MaxTries = BCGame.GetMaxTries();
    std::cout << MaxTries << std::endl;
    
    //loop for the number of turns asking for guesses
    for(int32 count = 1; count <= MaxTries; count++) {
        // checking if guess is valid
        FText Guess = GetGuess();
        
        EGuessStatus Status = BCGame.CheckGuessValidity(Guess);
        switch (Status) {
            case EGuessStatus::Wrong_Length:
                std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word \n";
                break;
                
            
            default:
                break;
        }
        
        // submit valid guess to the game, and receieve counts
        FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);
        // print number of bulls and cows
        std::cout << "Bulls = " << BullCowCount.Bulls;
        std::cout << ". Cows = " << BullCowCount.Cows << std::endl;
    }
    
    // TODO sammarise game here
}

// get a guess from a user
FText GetGuess() {
    int32 CurrentTry = BCGame.GetCurrentTry();
    std::cout << "Try " << CurrentTry << " enter your guess: ";
    
    FText Guess = "";
    getline(std::cin, Guess);
    return Guess;
}

bool AskToPlayAgain() {
    std::cout << "Do you want to play again? ";
    FText Response = "";
    getline(std::cin, Response);
    return (Response[0] == 'y') || (Response[0] == 'Y');
}

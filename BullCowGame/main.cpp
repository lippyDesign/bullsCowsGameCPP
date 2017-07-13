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
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

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
    std::cout << "\n\nWelcome to Bulls and Cows, a fun word game.\n";
    std::cout << "Can you guess the " << WORD_LENGTH;
    std::cout << " letter isogram I'm thinking off?\n\n";
    return;
}

void PlayGame() {
    
    BCGame.Reset();
    
    int32 MaxTries = BCGame.GetMaxTries();
    //std::cout << MaxTries << std::endl;
    
    //loop asking for guesses while the game is not won
    // and there are still tries remaining
    while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
        // checking if guess is valid
        FText Guess = GetValidGuess();
        
        // submit valid guess to the game, and receieve counts
        FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
        // print number of bulls and cows
        std::cout << "Bulls = " << BullCowCount.Bulls;
        std::cout << ". Cows = " << BullCowCount.Cows << std::endl;
    }
    
    PrintGameSummary();
    return;
}

// loop continually until user gives a valid guess
FText GetValidGuess() {
    EGuessStatus Status = EGuessStatus::Invalid_Status;
    
    FText Guess = "";

    do {
        int32 CurrentTry = BCGame.GetCurrentTry();
        std::cout << "Try " << CurrentTry << " enter your guess: ";
        
        // get a guess from a user
        getline(std::cin, Guess);
        
        // Get the status of the guess
        Status = BCGame.CheckGuessValidity(Guess);
        
        // check the status for errors
        switch (Status) {
            case EGuessStatus::Wrong_Length:
                std::cout << "Please enter only a " << BCGame.GetHiddenWordLength() << " letter word \n";
                break;
                //case:
            case EGuessStatus::Not_Lowercase:
                std::cout << "Please enter a only lower case letters \n";
                break;
            case EGuessStatus::Not_Isogramm:
                std::cout << "The word you enter must be an isogram \n";
                break;
            default:
                break;
        }
        
        std::cout << std::endl;
        
    } while(Status != EGuessStatus::OK); // keep looping until no errors in input
    
    return Guess;
}

bool AskToPlayAgain() {
    std::cout << "Do you want to play again with the same hidden word? ";
    FText Response = "";
    getline(std::cin, Response);
    return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary() {
    if (BCGame.IsGameWon()) {
        std::cout << "You won!!!!\n";
    } else {
        std::cout << "You lost, better luck next time\n";
    }
    
    return;
}

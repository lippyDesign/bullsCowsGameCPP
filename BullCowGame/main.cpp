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
int32 GetHiddenWordLength();
void PlayGame(int32);
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // instantiate a new game

// entry point for application
int main() {
    bool bPlayAgain = false;
    do {
        PrintIntro();
        int32 Length = GetHiddenWordLength();
        PlayGame(Length);
        bPlayAgain = AskToPlayAgain();
    } while (bPlayAgain);
    
    return 0;
}

// introduce the game
void PrintIntro() {
    std::cout<<"#############################################################"<<std::endl;
    std::cout<<"#                  _  _                                     #"<<std::endl;
    std::cout<<"#                 ( `   )_                                  #"<<std::endl;
    std::cout<<"#                (    )    `)                               #"<<std::endl;
    std::cout<<"#              (_   (_ .  _) _)                             #"<<std::endl;
    std::cout<<"#                                             _             #"<<std::endl;
    std::cout<<"#                                            (  )           #"<<std::endl;
    std::cout<<"#             _ .                         ( `  ) . )        #"<<std::endl;
    std::cout<<"#           (  _ )_                      (_, _(  ,_)_)      #"<<std::endl;
    std::cout<<"#         (_  _(_ ,)                                        #"<<std::endl;
    std::cout<<"#############################################################"<<std::endl;
    std::cout << "\n\nWelcome to Bulls and Cows, a fun word game.\n";
    std::cout << "Please enter the size of the hidden word you would like to play with (between 3 and 7): ";
    return;
}

int32 GetHiddenWordLength() {
    int32 wordLength = 0;
    FText Length = "";
    
    do {
        // get input from user
        getline(std::cin, Length);
        // check input validity
        bool isValidLength = BCGame.CheckLengthValidity(Length);
        if (isValidLength) {
            // convert into int and assign to word length
            wordLength = std::stoi(Length);
            break;
        }
    
    } while (!BCGame.IsHiddenWordSelected());
    
    return wordLength;
}

void PlayGame(int32 Length) {
    
    BCGame.Reset();
    
    BCGame.SetHiddenWord(Length);
    
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
        std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << " enter your guess: ";
        
        // get a guess from a user
        getline(std::cin, Guess);
        
        // Get the status of the guess
        Status = BCGame.CheckGuessValidity(Guess);
        
        // check the status for errors
        switch (Status) {
            case EGuessStatus::Wrong_Length:
                std::cout << "\nPlease enter only a " << BCGame.GetHiddenWordLength() << " letter word \n";
                break;
                //case:
            case EGuessStatus::Not_Lowercase:
                std::cout << "\nPlease enter only lower case letters \n";
                break;
            case EGuessStatus::Not_Isogram:
                std::cout << "\nThe word you enter must be an isogram \n";
                break;
            default:
                break;
        }
        
        std::cout << std::endl;
        
    } while(Status != EGuessStatus::OK); // keep looping until no errors in input
    
    return Guess;
}

bool AskToPlayAgain() {
    std::cout << "Do you want to play again? ";
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

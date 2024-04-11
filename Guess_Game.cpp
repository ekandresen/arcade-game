#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

bool playGame(int guesses) {
    int correct;
    srand(time(NULL)); // Seed the random number from system time

    if (guesses == 1) {
        correct = rand() % 200;
    }
    else {
        correct = rand() % 20;
    }

    int guessCount = 0;
    cout << "You get " << guesses << " guesses" << endl;

    while (guessCount < guesses) {
        cout << "Guess a number: " << endl;
        int guess;
        cin >> guess;

        if (guess == correct) {
            return true;
        }
        else if (guess < correct) {
            cout << "Too low" << endl;
        }
        else {
            cout << "Too high" << endl;
        }

        guessCount++;
        cout << "You have guessed " << guessCount << " times\n";
    }

    return false;
}

int main() {
    cout << "Hello, Welcome to the guess game. I hope you enjoy it." << endl;
    cout << "Do you want to play? (y/n)" << endl;

    string response;
    cin >> response;

    if (tolower(response[0]) == 'y') {
        cout << "Let's play a Game" << endl;
        cout << "Have you beaten the game before? (0: No / 1: Yes)" << endl;

        bool won;
        bool beatGame;
        cin >> beatGame;

        if (beatGame) {
            cout << "Are you ready for the impossible mode" << endl;
            won = playGame(1);
        }
        else {
            cout << "\nWhat difficulty do you want to play? Please choose the number \n0: Easy\n1: Medium\n2: Hard." << endl;

            int difficulty;
            cin >> difficulty;
            cout << "You chose " << difficulty << endl;

            switch (difficulty) {
            case 0:
                won = playGame(10);
                break;
            case 1:
                won = playGame(5);
                break;
            case 2:
                won = playGame(3);
                break;
            }
        }

        if (won) {
            cout << "Congrats, You won" << endl;
        }
        else {
            cout << "You lost, Better Luck next time" << endl;
        }
    }
    else if (tolower(response[0]) == 'n') {
        cout << "Okay, see you next time" << endl;
    }
    else {
        cout << "Invalid input. Exiting game." << endl;
    }

    return 0;
}

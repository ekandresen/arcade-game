/*****************************************************************/
/* NAME: Amanda Robbins */
/* ORGN: UAA */
/* FILE: ticTacToe.cpp */
/* DATE: Apr 10 2024 */
/*****************************************************************/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;


const char PLAYER_MARK = 'X';
const char COMPUTER_MARK = 'O';
const char EMPTY_MARK = ' ';
const int BOARD_SIZE = 3;


void displayBoard(const vector<vector<char>>& board);
bool isBoardFull(const vector<vector<char>>& board);
bool checkWinner(const vector<vector<char>>& board, char mark);
bool isMoveValid(const vector<vector<char>>& board, int row, int col);
void playerMove(vector<vector<char>>& board);
void computerMove(vector<vector<char>>& board);
void resetBoard(vector<vector<char>>& board);

int main() {
    // Initialize the board
    vector<vector<char>> board(BOARD_SIZE, vector<char>(BOARD_SIZE, EMPTY_MARK));

    int playerScore = 0;
    int computerScore = 0;
    char playAgain = 'y';

    // Main game loop
    while (playAgain == 'y' || playAgain == 'Y') {
        // Display the board and scores
        cout << "\nTic Tac Toe" << endl;
        cout << "Player Score: " << playerScore << " | Computer Score: " << computerScore << endl;
        displayBoard(board);

        // Play the game
        while (!isBoardFull(board)) {
            // Player's move
            playerMove(board);
            displayBoard(board);
            if (checkWinner(board, PLAYER_MARK)) {
                cout << "Player wins!" << endl;
                playerScore++;
                break;
            }

            // Check if the board is full after the player's move
            if (isBoardFull(board)) {
                break;
            }

            // Computer's move
            computerMove(board);
            displayBoard(board);
            if (checkWinner(board, COMPUTER_MARK)) {
                cout << "Computer wins!" << endl;
                computerScore++;
                break;
            }
        }

        // Check for a draw
        if (!checkWinner(board, PLAYER_MARK) && !checkWinner(board, COMPUTER_MARK)) {
            cout << "It's a draw!" << endl;
        }

        // Ask the user if they want to play again
        cout << "\nPlay again? (y/n): ";
        cin >> playAgain;

        // Reset the board for the next game
        resetBoard(board);
    }

    cout << "Player Score: " << playerScore << " | Computer Score: " << computerScore << endl;
    return 0;
}

// Function to display the board
void displayBoard(const vector<vector<char>>& board) {
    cout << endl;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            cout << board[i][j];
            if (j < BOARD_SIZE - 1) {
                cout << " | ";
            }
        }
        cout << endl;
        if (i < BOARD_SIZE - 1) {
            cout << "---------" << endl;
        }
    }
    cout << endl;
}

// Function to check if the board is full
bool isBoardFull(const vector<vector<char>>& board) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == EMPTY_MARK) {
                return false;
            }
        }
    }
    return true;
}

// Function to check if there is a winner
bool checkWinner(const vector<vector<char>>& board, char mark) {
    // Check rows
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i][0] == mark && board[i][1] == mark && board[i][2] == mark) {
            return true;
        }
    }

    // Check columns
    for (int j = 0; j < BOARD_SIZE; j++) {
        if (board[0][j] == mark && board[1][j] == mark && board[2][j] == mark) {
            return true;
        }
    }

    // Check diagonals
    if (board[0][0] == mark && board[1][1] == mark && board[2][2] == mark) {
        return true;
    }

    if (board[0][2] == mark && board[1][1] == mark && board[2][0] == mark) {
        return true;
    }

    return false;
}

// Function to check if a move is valid
bool isMoveValid(const vector<vector<char>>& board, int row, int col) {
    return (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE && board[row][col] == EMPTY_MARK);
}

// Function for the player's move
void playerMove(vector<vector<char>>& board) {
    int row, col;
    while (true) {
        cout << "\nEnter your move (row and column, 1-3): ";
        cin >> row >> col;

        // Convert 1-based input to 0-based
        row--;
        col--;

        if (isMoveValid(board, row, col)) {
            board[row][col] = PLAYER_MARK;
            break;
        }
        else {
            cout << "Invalid move. Try again." << endl;
        }
    }
}

// Function for the computer's move
void computerMove(vector<vector<char>>& board) {
    // Basic AI strategy: find an empty spot and place a mark
    srand(time(0)); // Initialize random seed
    int row, col;
    while (true) {
        row = rand() % BOARD_SIZE;
        col = rand() % BOARD_SIZE;
        if (isMoveValid(board, row, col)) {
            board[row][col] = COMPUTER_MARK;
            break;
        }
    }
}

// Function to reset the board
void resetBoard(vector<vector<char>>& board) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = EMPTY_MARK;
        }
    }
}

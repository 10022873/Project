#include <iostream>
#include <fstream>
using namespace std;

// Global constants
const char X = 'X';
const char O = 'O';
const int BOARD_SIZE = 3;
const char EMPTY = '_';
const string SAVE_FILE = "proj1_data.txt";

// Function prototypes
void mainMenu(int& totalGames, int& draws, int& xWins, int& oWins);
void saveGame(char board[BOARD_SIZE][BOARD_SIZE]);
void displayBoard(char board[BOARD_SIZE][BOARD_SIZE]);
void clearBoard(char board[BOARD_SIZE][BOARD_SIZE]);
char chooseSymbol();
void playGame(int& totalGames, int& draws, int& xWins, int& oWins);
bool makeMove(char board[BOARD_SIZE][BOARD_SIZE], char player, int row, int col);
bool checkWin(char board[BOARD_SIZE][BOARD_SIZE], char player);
bool checkDraw(char board[BOARD_SIZE][BOARD_SIZE]);
void calcStats(int& totalGames, int& draws, int& xWins, int& oWins, char outcome);
void displayStats(int totalGames, int draws, int xWins, int oWins);

int main() {
    int totalGames = 0, draws = 0, xWins = 0, oWins = 0;
    mainMenu(totalGames, draws, xWins, oWins);
    return 0;
}

// Main menu with stats tracking
void mainMenu(int& totalGames, int& draws, int& xWins, int& oWins) {
    int choice;
    do {
        cout << "Welcome to Tic-Tac-Toe\n";
        cout << "What would you like to do?\n";
        cout << "1. Play New Game\n";
        cout << "2. Display Stats\n";
        cout << "3. Quit\n";
        cin >> choice;

        switch (choice) {
            case 1:
                playGame(totalGames, draws, xWins, oWins);
                break;
            case 2:
                displayStats(totalGames, draws, xWins, oWins);
                break;
            case 3:
                cout << "Thank you for playing Tic-Tac-Toe\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 3);
}

// Save the current game state to a file
void saveGame(char board[BOARD_SIZE][BOARD_SIZE]) {
    ofstream outFile(SAVE_FILE);
    if (outFile.is_open()) {
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                outFile << board[i][j] << " ";
            }
            outFile << endl;
        }
        outFile.close();
    } else {
        cout << "Error saving game state to file.\n";
    }
}

// Display the current state of the board
void displayBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
    cout << "Current board:\n";
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

// Clear the board for a new game
void clearBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = EMPTY;
        }
    }
}

// Allow players to choose their symbols
char chooseSymbol() {
    char symbol;
    do {
        cout << "What symbol would you like to be? (X or O): ";
        cin >> symbol;
        symbol = toupper(symbol); // Ensure uppercase
        if (symbol != X && symbol != O) {
            cout << "Invalid symbol. Please choose X or O.\n";
        }
    } while (symbol != X && symbol != O);
    return symbol;
}

// Updated playGame to track stats
void playGame(int& totalGames, int& draws, int& xWins, int& oWins) {
    char board[BOARD_SIZE][BOARD_SIZE];
    clearBoard(board);
    char currentPlayer = chooseSymbol();
    bool gameOver = false;
    char outcome = ' '; // 'X', 'O', or 'D' for draw

    while (!gameOver) {
        displayBoard(board);
        int row, col;
        cout << "Player " << currentPlayer << ", enter row and column (0-2): ";
        cin >> row >> col;

        if (makeMove(board, currentPlayer, row, col)) {
            if (checkWin(board, currentPlayer)) {
                displayBoard(board);
                cout << "Player " << currentPlayer << " wins!\n";
                outcome = currentPlayer;
                gameOver = true;
            } else if (checkDraw(board)) {
                displayBoard(board);
                cout << "It's a draw!\n";
                outcome = 'D';
                gameOver = true;
            } else {
                currentPlayer = (currentPlayer == X) ? O : X;
            }
            saveGame(board);
        } else {
            cout << "Invalid move. Try again.\n";
        }
    }

    // Update stats after the game
    if (outcome != ' ') {
        calcStats(totalGames, draws, xWins, oWins, outcome);
    }
}

// Validate moves (unchanged from base code)
bool makeMove(char board[BOARD_SIZE][BOARD_SIZE], char player, int row, int col) { /* ... */ }

// Check for win (unchanged from base code)
bool checkWin(char board[BOARD_SIZE][BOARD_SIZE], char player) { /* ... */ }

// Check for draw (unchanged from base code)
bool checkDraw(char board[BOARD_SIZE][BOARD_SIZE]) { /* ... */ }

// Calculate stats
void calcStats(int& totalGames, int& draws, int& xWins, int& oWins, char outcome) {
    totalGames++;
    if (outcome == X) {
        xWins++;
    } else if (outcome == O) {
        oWins++;
    } else {
        draws++;
    }
}

// Display stats
void displayStats(int totalGames, int draws, int xWins, int oWins) {
    cout << "********************\n";
    cout << "Total games: " << totalGames << "\n";
    cout << "Draws: " << draws << "\n";
    cout << "X wins: " << xWins << "\n";
    cout << "O wins: " << oWins << "\n";
    cout << "********************\n";
}

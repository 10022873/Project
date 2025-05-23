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
void mainMenu();
void saveGame(char board[BOARD_SIZE][BOARD_SIZE]);
void playGame();
void displayBoard(char board[BOARD_SIZE][BOARD_SIZE]);
void clearBoard(char board[BOARD_SIZE][BOARD_SIZE]);
char chooseSymbol();
bool makeMove(char board[BOARD_SIZE][BOARD_SIZE], int row, int col, char symbol);
char checkWin(char board[BOARD_SIZE][BOARD_SIZE]);

int main() {
    mainMenu();
    return 0;
}

// Main menu function
void mainMenu() {
    int choice;
    do {
        cout << "Welcome to Tic-Tac-Toe\n";
        cout << "What would you like to do?\n";
        cout << "1. Play New Game\n";
        cout << "2. Quit\n";
        cin >> choice;

        switch (choice) {
            case 1:
                playGame();
                break;
            case 2:
                cout << "Thank you for playing Tic-Tac-Toe\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 2);
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

// Display the board
void displayBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
    cout << "Current board:\n";
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

// Clear the board
void clearBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = EMPTY;
        }
    }
}

// Player chooses symbol
char chooseSymbol() {
    char XorO;
    do {
        cout << "What do you want as your symbol? (options are X or O): ";
        cin >> XorO;
        if (XorO != 'O' && XorO != 'X')
            cout << "Invalid symbol. Try again." << endl;
    } while (XorO != 'O' && XorO != 'X');
    return XorO;
}

// Play game function
void playGame() {
    char board[BOARD_SIZE][BOARD_SIZE];
    clearBoard(board);
    char symbol = chooseSymbol();

    do {
        displayBoard(board);
        int row, col;
        cout << "Player " << symbol << ", enter row and col (0-2): ";
        cin >> row >> col;

        if (makeMove(board, row, col, symbol)) {
            if (checkWin(board) == 'X') {
                displayBoard(board);
                cout << "Player X wins\n";
                cout << "Thanks for playing\n";
                return;
            } else if (checkWin(board) == 'O') {
                displayBoard(board);
                cout << "Player O wins\n";
                cout << "Thanks for playing\n";
                return;
            } else if (checkWin(board) == 'T') {
                displayBoard(board);
                cout << "It's a tie\n";
                cout << "Thanks for playing\n";
                return;
            }
        } else {
            cout << "Invalid move. Try again.\n";
        }
    } while (checkWin(board) == 'G');
}

// Make a move
bool makeMove(char board[BOARD_SIZE][BOARD_SIZE], int row, int col, char symbol) {
    if (row >= BOARD_SIZE || col >= BOARD_SIZE || row < 0 || col < 0)
        return false;
    if (board[row][col] != EMPTY)
        return false;
    board[row][col] = symbol;
    return true;
}

// Check for a winner
char checkWin(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != EMPTY)
            return board[i][0];
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != EMPTY)
            return board[0][i];
    }

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != EMPTY)
        return board[0][0];
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != EMPTY)
        return board[0][2];

    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            if (board[i][j] == EMPTY)
                return 'G';

    return 'T';
}

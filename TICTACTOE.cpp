
#include <iostream>
using namespace std;

enum Player { NONE = '*', PLAYER_X = 'X', PLAYER_O = 'O' };
void printBoard(const Player board[][3]);
bool placeMark(Player board[][3], Player player);
bool checkWinner(const Player board[][3], Player player);
bool isBoardFull(const Player board[][3]);
void playTicTacToe();

int main() {
    playTicTacToe();
    return 0;
}

void playTicTacToe() {
    Player board[3][3] = {{NONE, NONE, NONE}, {NONE, NONE, NONE}, {NONE, NONE, NONE}};
    bool gameRunning = true;
    Player currentPlayer = PLAYER_X;

    while (gameRunning) {
        printBoard(board);
        if (placeMark(board, currentPlayer)) {
            if (checkWinner(board, currentPlayer)) {
                printBoard(board);
                cout << "Player " << static_cast<char>(currentPlayer) << " wins!" << endl;
                gameRunning = false;
            } else if (isBoardFull(board)) {
                printBoard(board);
                cout << "It's a draw!" << endl;
                gameRunning = false;
            }
            currentPlayer = (currentPlayer == PLAYER_X) ? PLAYER_O : PLAYER_X;
        } else {
            cout << "Invalid move, try again." << endl;
        }
    }
}

void printBoard(const Player board[][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << static_cast<char>(board[i][j]) << "\t";
        }
        cout << endl;
    }
}

bool placeMark(Player board[][3], Player player) {
    int row, col;
    cout << "Player " << static_cast<char>(player) << ", enter row and column (1-3) to place your mark: ";
    cin >> row >> col;

    if (cin.fail() || row < 1 || row > 3 || col < 1 || col > 3 || board[row - 1][col - 1] != NONE) {
        cin.clear(); // Clear error flags
        cin.ignore(10000, '\n'); // Discard bad input
        return false;
    }

    board[row - 1][col - 1] = player;
    return true;
}

bool checkWinner(const Player board[][3], Player player) {
    // Check rows, columns, and diagonals
    for (int i = 0; i < 3; ++i) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return true;
        }
    }
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return true;
    }
    return false;
}

bool isBoardFull(const Player board[][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == NONE) {
                return false;
            }
        }
    }
    return true;
}

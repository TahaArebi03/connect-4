#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

class State {
public:
    char current_player;
};

class Connect_4 {
public:
    Connect_4() {}
    void startGame(vector<vector<char>> board, State &state);
};

void printBoard(vector<vector<char>> board) {
    cout << "   0    1    2    3    4    5    6" << endl;

    for(int i = 0; i < 6; i++) {
        cout << "+----+----+----+----+----+----+----+" << endl;

        for(int j = 0; j < 7; j++) {
            cout << "| " << board[i][j] << "  ";
        }
        cout << "|" << endl;
    }
    cout << "+----+----+----+----+----+----+----+" << endl;
}
int GetDropRow(vector<vector<char>> board, int col) {
    for(int row = 5; row >= 0; row--) {
        if(board[row][col] == ' ') {
            return row;
        }
    }
    return -1; // Column is full
}
int countHorizontal(vector<vector<char>> board, int row, int col, char player) {
    int count = 0;
    // Check to the left
    for(int c = col; c >= 0; c--) {
        if(board[row][c] == player) {
            count++;
        } else {
            break;
        }
    }
    // Check to the right
    for(int c = col + 1; c < 7; c++) {
        if(board[row][c] == player) {
            count++;
        } else {
            break;
        }
    }
    return count;
}
int countVertical(vector<vector<char>> board, int row, int col, char player) {
    int count = 0;
    // Check downwards
    for(int r = row; r < 6; r++) {
        if(board[r][col] == player) {
            count++;
        } else {
            break;
        }
    }
    return count;
}
int countDiagonalLToR(vector<vector<char>> board, int row, int col, char player) {
    int count = 0;
    // Check top-left to bottom-right
    for(int r = row, c = col; r >= 0 && c >= 0; r--, c--) {
        if(board[r][c] == player) {
            count++;
        } else {
            break;
        }
    }
    for(int r = row + 1, c = col + 1; r < 6 && c < 7; r++, c++) {
        if(board[r][c] == player) {
            count++;
        } else {
            break;
        }
    }
    return count;
}
int countDiagonalRToL(vector<vector<char>> board, int row, int col, char player) {
    int count = 0;
    // Check top-right to bottom-left
    for(int r = row, c = col; r >= 0 && c < 7; r--, c++) {
        if(board[r][c] == player) {
            count++;
        } else {
            break;
        }
    }
    for(int r = row + 1, c = col - 1; r < 6 && c >= 0; r++, c--) {
        if(board[r][c] == player) {
            count++;
        } else {
            break;
        }
    }
    return count;
}

int countDiagonal(vector<vector<char>> board, int row, int col, char player) {
    int count = 0;
    // Check top-left to bottom-right
    count += countDiagonalLToR(board, row, col, player);
    // Check top-right to bottom-left
    count += countDiagonalRToL(board, row, col, player);
    return count;
}

int evaluateBoard(vector<vector<char>> board,int row,int col, char player) {
    // Simple evaluation function: count number of 2, 3 in a row for the player
    int score = 0;
    
    // Check horizontal
    score+=countHorizontal(board, row,col ,player);
    // vertical 
    score+=countVertical(board, row,col ,player);
    // diagonal
    score+=countDiagonal(board, row,col ,player);   
    
    return score;
}
int minimaxPlay(vector<vector<char>> board, State &state) {
    int column_chosen;
    vector<int> valid_columns;
    int max=-1;
    vector<vector<char>> temp_board=board;
    // for(int row=5;row<=0;row--){
        for(int col=0;col<7;col++){
            if(board[0][col]==' '){
                valid_columns.push_back(col);
            }
        }
        for(int col:valid_columns){
            
            int score=0;
            int row=GetDropRow(temp_board,col);
            if(row!=-1){
                temp_board[row][col]=state.current_player;
            }
            else{
                // العمود ممتلئ، تخطي هذه الحركة
                continue;
            }
            // حساب عدد القطع المتصلة
            score= evaluateBoard(temp_board,row,col,state.current_player);
            if(score>max){
                max=score;
                column_chosen=col;
            }
            // رجع اللوحة إلى حالتها الأصلية
            temp_board[row][col]=' ';
            
        }
    // }
    return column_chosen;
}
void applyMove(vector<vector<char>> &board, int col, char player) {
    for(int row = 5; row >= 0; row--) {
        if(board[row][col] == ' ') {
            board[row][col] = player;
            break;
        }
    }
}

void checkGameState(vector<vector<char>> board, State &state){
    if(checkWin(board, state.current_player)){
        state.is_terminal=true;
        cout << "Player " << state.current_player << " wins!" << endl;
        return;
    }
    else if(isBoardFull(board)){
        state.is_terminal=true;
        cout << "The game is a draw!" << endl;
        return;
    }
}

void Connect_4::startGame(vector<vector<char>> board, State &state) {

    cout << "Starting the Connect 4 Game..." << endl;
    cout << "Randomly selecting the first player..." << endl;

    cout << "Player 'R' uses Minimax Algorithm." << endl;
    cout << "Player 'Y' uses Expectimax Algorithm." << endl;
    int column_chosen;
    state.current_player = (rand() % 2 == 0 ? 'R' : 'Y');
    if(state.current_player == 'R') {
        cout << "Player Minimax starts first!" << endl;
    } else {
        cout << "Player Expectimax starts first!" << endl;
    }
    while (true)
    {
        if (state.current_player == 'R') {
            printBoard(board);
            column_chosen = minimaxPlay(board, state);
            cout << "Player Minimax chooses column: " << column_chosen << endl;
        

        } else {
            printBoard(board);
            column_chosen = expectimaxPlay(board, state);
        
        }
        applyMove(board, column_chosen, state.current_player);
        checkGameState(board, state);
        state.current_player = (state.current_player == 'R' ? 'Y' : 'R');
    }
    
    
}

int main() {
    Connect_4 game;
    State state;

    vector<vector<char>> board = {
        {' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' '},
        {' ',' ','Y',' ',' ',' ',' '}
    };

    cout << "Connect 4 Game Initialized!" << endl;
    printBoard(board);

    game.startGame(board, state);

    return 0;
}


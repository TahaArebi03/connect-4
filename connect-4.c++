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
    int HorizontalWins=0;
    int VerticalWins=0;
    int DiagonalLtoRWins=0;
    int DiagonalRtoLWins=0;
    Connect_4() {}
    void startGame(vector<vector<char>> board, State &state);
private:
    int minimaxPlay(vector<vector<char>> board, State &state);
    int expectimaxPlay(vector<vector<char>> board, State &state);
    
    
    int GetDropRow(vector<vector<char>> board, int col);
    void checkGameState(vector<vector<char>> board,int column_chosen, State &state);
    void applyMove(vector<vector<char>> &board, int col, char player);
    bool checkWin(vector<vector<char>> board,int col, char player);
    bool isBoardFull(vector<vector<char>> board);

    
    int evaluateBoard(vector<vector<char>> board,int row,int col, char player);
    
    int countHorizontal(vector<vector<char>> board, int row, int col, char player);
    int countVertical(vector<vector<char>> board, int row, int col, char player);
    int countDiagonal(vector<vector<char>> board, int row, int col, char player);

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
int Connect_4::GetDropRow(vector<vector<char>> board, int col) {
    for(int row = 5; row >= 0; row--) {
        if(board[row][col] == ' ') {
            return row;
        }
    }
    return -1; // Column is full
}
int Connect_4::countHorizontal(vector<vector<char>> board, int row, int col, char player) {
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
    // شرط col +1 بش مانحسب نفس العمود مرتين
    for(int c = col + 1; c < 7; c++) {
        if(board[row][c] == player) {
            count++;
        } else {
            break;
        }
    }
    if(count>=4){
        return 10000;
    }
    else{
        return count;
    }
}
int Connect_4::countVertical(vector<vector<char>> board, int row, int col, char player) {
    int count = 0;
    // Check downwards
    for(int r = row; r < 6; r++) {
        if(board[r][col] == player) {
            count++;
        } else {
            break;
        }
    }
    if(count>=4){
        return 10000;
    }
    else{
        return count;
    }   
}
int countDiagonalLToR(vector<vector<char>> board, int row, int col, char player) {
    int count = 0;
    // Check top-left to bottom-right
    
    // Check top-left
    for(int r = row, c = col; r >= 0 && c >= 0; r--, c--) {
        if(board[r][c] == player) {
            count++;
        } else {
            break;
        }
    }
    // Check bottom-right
    for(int r = row + 1, c = col + 1; r < 6 && c < 7; r++, c++) {
        if(board[r][c] == player) {
            count++;
        } else {
            break;
        }
    }
    if(count>=4){
        return 10000;
    }
    else{
        return count;
    }
}
int countDiagonalRToL(vector<vector<char>> board, int row, int col, char player) {
    int count = 0;
    // Check top-right to bottom-left

    // Check top-right
    for(int r = row, c = col; r >= 0 && c < 7; r--, c++) {
        if(board[r][c] == player) {
            count++;
        } else {
            break;
        }
    }
    // Check bottom-left
    for(int r = row + 1, c = col - 1; r < 6 && c >= 0; r++, c--) {
        if(board[r][c] == player) {
            count++;
        } else {
            break;
        }
    }
    if(count>=4){
        return 10000;
    }
    else{
        return count;
    }
}



int Connect_4::evaluateBoard(vector<vector<char>> board,int row,int col, char player) {
    int h=countHorizontal(board, row, col, player);
    int v=countVertical(board, row, col, player);
    int d1=countDiagonalLToR(board, row, col, player);
    int d2=countDiagonalRToL(board, row, col, player);
    if(h==10000){
        HorizontalWins++;
        return 10000;
    }
    else if(v==10000){
        VerticalWins++;
        return 10000;
    }
    else if(d1==10000){
        DiagonalLtoRWins++;
        return 10000;
    }
    else if(d2==10000){
        DiagonalRtoLWins++;
        return 10000;
    }
    else{
        int score=0;
        score=h+v+d1+d2;
        return score;
    }
}
int Connect_4::minimaxPlay(vector<vector<char>> board, State &state) {
    int column_chosen;
    vector<int> valid_columns;
    int max=-1;
    vector<vector<char>> temp_board=board;
    // for(int row=5;row<=0;row--){
        // الاعمدة الي ليست ممتلئة
        for(int col=0;col<7;col++){
            if(board[0][col]==' '){
                valid_columns.push_back(col);
            }
        }
        for(int col:valid_columns){
            
            int score=0;
            int row= GetDropRow(temp_board,col);
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
int Connect_4::expectimaxPlay(vector<vector<char>> board, State &state) {
    
}

void Connect_4::applyMove(vector<vector<char>> &board, int col, char player) {
    for(int row = 5; row >= 0; row--) {
        if(board[row][col] == ' ') {
            board[row][col] = player;
            break;
        }
    }
}
bool Connect_4::checkWin(vector<vector<char>> board,int column_chosen, char player) {
    
    int row = GetDropRow(board, column_chosen);
    // كان الصف يساوي سالب واحد معناها القطعة موجودة في الصف صفر والعمود ممتلئ
    if (row == -1) {
        row=0;
    }
    // لو تححصلت علي مكان فارغ معناها القطعة الي تحتها هيا الي نبيها
    else{
        row+=1;
    }
    // Check horizontal
    if (countHorizontal(board, row, column_chosen, player) >= 4) {
        return true;
    }
    // Check vertical
    if (countVertical(board, row, column_chosen, player) >= 4) {
        return true;
    }
    // Check diagonal
    if(countDiagonalLToR(board, row, column_chosen, player) >= 4) {
        return true;
    }
    if(countDiagonalRToL(board, row, column_chosen, player) >= 4) {
        return true;
    }


    return false;
}
bool Connect_4::isBoardFull(vector<vector<char>> board) {
    for(int col = 0; col < 7; col++) {
        if(board[0][col] == ' ') {
            return false; // Found an empty space in the top row
        }
    }
    return true; // No empty spaces found, board is full
}
void Connect_4::checkGameState(vector<vector<char>> board,int column_chosen, State &state){
    if(checkWin(board,column_chosen ,state.current_player)){
        // state.is_terminal=true;
        cout << "Player " << state.current_player << " wins!" << endl;
        return;
    }
    else if(isBoardFull(board)){
        // state.is_terminal=true;
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
    // Randomly select the first player
    state.current_player = (rand() % 2 == 0 ? 'R' : 'Y');
    cout << "Player '" << state.current_player << "' starts first!" << endl;
    if(state.current_player == 'R') {
        cout << "Player Minimax starts first!" << endl;
    } else {
        cout << "Player Expectimax starts first!" << endl;
    }
    while (true)
    {
        if (state.current_player == 'R') {
            printBoard(board);
            // Get the column chosen by Minimax player
            column_chosen = minimaxPlay(board, state);
            cout << "Player Minimax chooses column: " << column_chosen << endl;
        

        } else {
            printBoard(board);
            column_chosen = expectimaxPlay(board, state);
        
        }
        applyMove(board, column_chosen, state.current_player);
        checkGameState(board, column_chosen,state);
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


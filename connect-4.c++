#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

class State {
public:
    char current_player;
};

class Connect_4 {
public:
    int minHorizontalWins=0;
    int minVerticalWins=0;
    int minDiagonalLtoRWins=0;
    int minDiagonalRtoLWins=0;
    int expHorizontalWins=0;
    int expVerticalWins=0;
    int expDiagonalLtoRWins=0;
    int expDiagonalRtoLWins=0;
    int MinimaxWins=0;
    int ExpectimaxWins=0;
    Connect_4() {}
    void startGame(vector<vector<char>> board, State &state);
private:
    int minimaxPlay(vector<vector<char>> board, State &state);
    int expectimaxPlay(vector<vector<char>> board, State &state);
    
    
    int GetDropRow(vector<vector<char>> board, int col);
    bool checkGameState(vector<vector<char>> board,int lastMoveRow,int column_chosen, State &state);
    int applyMove(vector<vector<char>> &board, int col, char player);
    bool OppenentCanWin(vector<vector<char>> board, char player);
    bool checkWin(vector<vector<char>> board,int lastMoveRow,int col, char player);
    void WhoWon(vector<vector<char>> board,int lastMoveRow,int column_chosen, char player);
    void wayOfWinning(vector<vector<char>> board,int lastMoveRow,int column_chosen, char player);
    bool isBoardFull(vector<vector<char>> board);

    
    int evaluateMinimax(vector<vector<char>> board,int row,int col, char player);
    int evaluateExpectimax(vector<vector<char>> board,int row,int col, char player);
    
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
    // if(count>=4){
    //     return 10000;
    // }
    // else{
    //     return count;
    // }
    return count;
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
    // if(count>=4){
    //     return 10000;
    // }
    // else{
    //     return count;
    // }
    return count;   
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
    // if(count>=4){
    //     return 10000;
    // }
    // else{
    //     return count;
    // }
    return count;
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
    // if(count>=4){
    //     return 10000;
    // }
    // else{
    //     return count;
    // }
    return count;
}

bool Connect_4::checkWin(vector<vector<char>> board,int lastMoveRow,int column_chosen, char player) {
    
    int row=lastMoveRow;
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


int Connect_4::applyMove(vector<vector<char>> &board, int col, char player) {
    for(int row = 5; row >= 0; row--) {
        if(board[row][col] == ' ') {
            board[row][col] = player;
            return row;
        }
    }
    return -1; // Column is full
}

bool Connect_4::OppenentCanWin(vector<vector<char>> board, char player){
    char opponent = (player == 'R') ? 'Y' : 'R';
    // التحقق من كل الأعمدة إذا كان اللاعب يقدر يفوز في الحركة الجاية
    for(int col=0;col<7;col++){
        // الحصول على الصف الذي ستسقط فيه القطعة
        int row = GetDropRow(board,col);
        if(row!=-1){
            board[row][col]=opponent;
            // التحقق إذا كانت هذه الحركة تؤدي إلى الفوز
            bool win=checkWin(board,row,col,opponent);
            // رجع اللوحة إلى حالتها الأصلية
            board[row][col]=' ';
            if(win){
                return true;
            }
        }
    }
    return false;
}

int Connect_4::evaluateMinimax(vector<vector<char>> board,int row,int col, char player) {
    int h=countHorizontal(board, row, col, player);
    int v=countVertical(board, row, col, player);
    int d1=countDiagonalLToR(board, row, col, player);
    int d2=countDiagonalRToL(board, row, col, player);
    if(h==4||v==4||d1==4||d2==4){
        return 10000;
    }
    int score=0;
    score=h+v+d1+d2;
    // إذا كانت هذه الحركة تمنع الخصم من الفوز في الحركة التالية، أعطِ قيمة عالية بالإضافة إلى score
    if(OppenentCanWin(board,player)){
        return -5000 + score;
    }

    return score;
}

int Connect_4::evaluateExpectimax(vector<vector<char>> board,int row,int col, char player) {
    int h=countHorizontal(board, row, col, player);
    int v=countVertical(board, row, col, player);
    int d1=countDiagonalLToR(board, row, col, player);
    int d2=countDiagonalRToL(board, row, col, player);
    if(h>=4||v>=4||d1>=4||d2>=4){
        return 10000;
    }
    // else if(OppenentCanWin(board,player)){
    //     return -5000;
    // }
    int score=0;
    score=h+v+d1+d2;
    return score;
}

int Connect_4::minimaxPlay(vector<vector<char>> board, State &state) {
    int column_chosen;
    vector<int> valid_columns;
    int max=-1;
    vector<int> best_cols;
    vector<vector<char>> temp_board=board;
    // for(int row=5;row<=0;row--){
        // الاعمدة الي ليست ممتلئة
        for(int col=0;col<7;col++){
            if(board[0][col]==' '){
                valid_columns.push_back(col);
            }
        }
        // إذا كانت اللوحة فارغة او تحتوي على حركة واحدة، اختر عشوائي
        vector<int> random_cols;
        for(int col:valid_columns){
            // النتيجة في كل عمود بعد المحاولة
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
            score= evaluateMinimax(temp_board,row,col,state.current_player);
            cout << "Minimax evaluating col " << col << ": score = " << score << endl;
            // cout << "Minimax evaluating col " << col << ": score = " << score << endl;
            if(score==0||score==1){
                random_cols.push_back(col);
            }
            if(score > max){
                max = score;
                best_cols.clear();
                best_cols.push_back(col);
            } else if(score == max){
                best_cols.push_back(col);
            }

            // رجع اللوحة إلى حالتها الأصلية
            temp_board[row][col]=' ';
            
        }
        // اختر عشوائي من أفضل العواميد
        if(!best_cols.empty()){
            int random_index = rand() % best_cols.size();
            column_chosen = best_cols[random_index];
        }
        // cout << "Minimax chose col " << column_chosen << " with max score " << max << endl;
        if(!random_cols.empty()&&max<=1){
            int random_index=rand()%random_cols.size();
            column_chosen=random_cols[random_index];
            // cout << "Randomly chose from low scores: " << column_chosen << endl;
        }
    // }
    return column_chosen;
}
int Connect_4::expectimaxPlay(vector<vector<char>> board, State &state) {
    // cout << "Expectimax is calculating the best move..." << endl;
    int column_chosen;
    vector<int> valid_columns;
    double bestValue=-10000.0;
    vector<int> best_cols;
    // for(int row=5;row<=0;row--){
        // الاعمدة الي ليست ممتلئة
        for(int col=0;col<7;col++){
            if(board[0][col]==' '){
                valid_columns.push_back(col);
            }
        }
        // إذا كانت اللوحة فارغة او تحتوي على حركة واحدة، اختر عشوائي
        vector<int> random_cols;
        for(int col:valid_columns){
            vector<vector<char>> temp_board1=board;
            
            int ownScore=0;
            int row= GetDropRow(temp_board1,col);
            if(row!=-1){
                temp_board1[row][col]=state.current_player;
            }
            else{
                // العمود ممتلئ، تخطي هذه الحركة
                continue;
            }
            // حساب عدد القطع المتصلة
            ownScore= evaluateExpectimax(temp_board1,row,col,state.current_player);
            // حساب نقاط الخصم
            char opponent = (state.current_player == 'R') ? 'Y' : 'R';
            double sumOppScores=0;
            double opponentScore=0;
            int numOppMoves=0;
            double score=ownScore;
            for(int oppCol = 0; oppCol < 7; oppCol++){
                int oppRow = GetDropRow(temp_board1, oppCol);

                if(oppRow == -1) continue;

                temp_board1[oppRow][oppCol] = opponent;

                opponentScore = evaluateExpectimax(temp_board1, oppRow, oppCol, opponent);

                sumOppScores += opponentScore;
                numOppMoves++;
                temp_board1[oppRow][oppCol]=' ';
            }
            bool opponentCanWin = false;

            for(int oppCol = 0; oppCol < 7; oppCol++){
                int oppRow = GetDropRow(temp_board1, oppCol);
                if(oppRow == -1) continue;

                temp_board1[oppRow][oppCol] = opponent;

                if(checkWin(temp_board1, oppRow, oppCol, opponent)){
                    opponentCanWin = true;
                    temp_board1[oppRow][oppCol] = ' ';
                    break;
                }

                temp_board1[oppRow][oppCol] = ' ';
            }

            if(opponentCanWin){
                score = -5000;   // استبعاد الحركة
            }
            else{
                double avgOppScore = sumOppScores / numOppMoves;
                score = ownScore - avgOppScore;
            }
            if(score > bestValue){
                bestValue = score;
                best_cols.clear();
                best_cols.push_back(col);
            } else if(score == bestValue){
                best_cols.push_back(col);
            }
            // إذا كانت اللوحة فارغة، اختر عشوائي

            cout << "Expectimax evaluating col " << col << ": score = " << score << endl;
            if(score==0||score==1){
                random_cols.push_back(col);

            }
        }
        // اختر عشوائي من أفضل العواميد
        if(!best_cols.empty()){
            int random_index = rand() % best_cols.size();
            column_chosen = best_cols[random_index];
        }
        // cout << "Minimax chose col " << column_chosen << " with max score " << max << endl;
        if(!random_cols.empty()&&bestValue<=1){
            int random_index=rand()%random_cols.size();
            column_chosen=random_cols[random_index];
            // cout << "Randomly chose from low scores: " << column_chosen << endl;
        }

    // }
    return column_chosen;
}



void Connect_4::wayOfWinning(vector<vector<char>> board,int lastMoveRow,int column_chosen, char player){
    if(countHorizontal(board, lastMoveRow, column_chosen, player)>=4){
        if(player=='R'){
            
            minHorizontalWins++;
        }
        else{
            expHorizontalWins++;
        }
        cout << "HorizontalWins" << endl;
    }
    if(countVertical(board, lastMoveRow, column_chosen, player)>=4){
        if(player=='R'){
            minVerticalWins++;
        }
        else{
            expVerticalWins++;
        }
        cout << "VerticalWins" << endl;
    }
    if(countDiagonalLToR(board, lastMoveRow, column_chosen, player)>=4){
        if(player=='R'){
            minDiagonalLtoRWins++;
        }
        else{
            expDiagonalLtoRWins++;
        }
        cout << "DiagonalLtoRWins" << endl;
    }
    if(countDiagonalRToL(board, lastMoveRow, column_chosen, player)>=4){
        if(player=='R'){
            minDiagonalRtoLWins++;
        }
        else{
            expDiagonalRtoLWins++;
        }
        cout << "DiagonalRtoLWins" << endl;
    }

}

void Connect_4::WhoWon(vector<vector<char>> board,int lastMoveRow,int column_chosen, char player){
    if(player=='R'){
        MinimaxWins++;
        
        cout<<"Minimax Algorithm Wins!"<<endl;
    }
    else{
        ExpectimaxWins++;
        cout<<"Expectimax Algorithm Wins!"<<endl;
    }
    wayOfWinning(board,lastMoveRow,column_chosen,player);
}
bool Connect_4::isBoardFull(vector<vector<char>> board) {
    for(int col = 0; col < 7; col++) {
        if(board[0][col] == ' ') {
            return false; // Found an empty space in the top row
        }
    }
    return true; // No empty spaces found, board is full
}
bool Connect_4::checkGameState(vector<vector<char>> board,int lastMoveRow,int column_chosen, State &state){
    if(checkWin(board,lastMoveRow,column_chosen ,state.current_player)){
        WhoWon(board,lastMoveRow,column_chosen ,state.current_player);

        return true;
    }
    else if(isBoardFull(board)){
        // state.is_terminal=true;
        cout << "The game is a draw!" << endl;
        return true;
    }
    else{
        return false;
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
            // Get the column chosen by Minimax player
            column_chosen = minimaxPlay(board, state);
            cout << "Player Minimax chooses column: " << column_chosen << endl;
            // printBoard(board);
        

        } else {
            column_chosen = expectimaxPlay(board, state);
            cout << "Player Expectimax chooses column: " << column_chosen << endl;
            // printBoard(board);
        
        }
        int lastMoveRow=applyMove(board, column_chosen, state.current_player);
        printBoard(board);
        
        if(checkGameState(board,lastMoveRow ,column_chosen,state)){
            break;
        }
        state.current_player = (state.current_player == 'R' ? 'Y' : 'R');
    }
    
    
}

int main() {
    srand(time(NULL)); // Initialize random seed
    Connect_4 game;
    State state;

    vector<vector<char>> board = {
        {' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' '}
    };

    cout << "Connect 4 Game Initialized!" << endl;
    // printBoard(board);

    game.startGame(board, state);

    return 0;
}


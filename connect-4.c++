#include<iostream>
#include<vector>
using namespace std;
class Connect_4{

};
class State{
    public:
    char current_player;
    
};
void printBoard(vector<vector<char>> board){
    cout << "   0    1    2    3    4    5    6" << endl;


    for(int i=0;i<6;i++){
        cout << "+----+----+----+----+----+----+----+" << endl;
    

        for(int j=0;j<7;j++){
            
            cout << "| " << board[i][j] << "  ";
        }
        cout << "|" << endl;
    }
    cout << "+----+----+----+----+----+----+----+" << endl;
}
int main(){
    vector<vector<char>> board={
        {' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' '},
        {' ',' ','y',' ',' ',' ',' '}};
    cout << "Connect 4 Game Initialized!" << endl;
    printBoard(board);    
    
    return 0;

}

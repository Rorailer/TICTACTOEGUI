#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>

using namespace std;

const string BOARD[5][5] = {
    {" ", " | ", " ", "|", " "},
    {"--", "+", "--", "+", "--"},
    {" ", " | ", " ", " | ", " "},
    {"--", "+", "--", "+", "--"},
    {" ", " | ", " ", " | ", " "}
};


void clear_board(string board[5][5]){
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            board[i][j]=BOARD[i][j];
        }
    }
}

void save_score(int winP1,int winP2,int lossP1, int lossP2, int draws){
    ofstream file;
    file.open("score.txt");
    file << winP1 << endl;
    file << lossP1 << endl;
    file << winP2 << endl;
    file << lossP2 << endl;
    file << draws << endl;

}

void load_score(int &winP1,int &winP2,int &lossP1, int &lossP2, int &draws){
    ifstream file;
    file.open("score.txt");
    file >> winP1;
    file >> lossP1;
    file >> winP2;
    file >> lossP2;
    file >> draws;
}


pair<int, int> coord_gen(){
    srand(time(0));
    int x = rand() % 3;
    int y = rand() % 3;
    return make_pair(x, y);
}


int cls_screen() {
    #if defined(_WIN32) || defined(_WIN64)
        cout << "Running on Windows" << endl;
        system("cls");
    #elif defined(__linux__)
        cout << "Running on Linux" << endl;
        system("clear");
    #elif defined(__APPLE__) || defined(__MACH__)
        cout << "Running on macOS" << endl;
        system("clear");
    #else
        cout << "Unknown operating system" << endl;
    #endif

    return 0;
}


//^ Checking for WIN
bool winchecklogic(const string board[5][5], char symbol) {
    // Convert symbol to a string for comparison
    string symbolStr(1,symbol);

    // rows
    if((board[0][0] == symbolStr && board[0][2] == symbolStr && board[0][4] == symbolStr) ||
        (board[2][0] == symbolStr && board[2][2] == symbolStr && board[2][4] == symbolStr) ||
        (board[4][0] == symbolStr && board[4][2] == symbolStr && board[4][4] == symbolStr))
        return 1;

    // columns
    if((board[0][0] == symbolStr && board[2][0] == symbolStr && board[4][0] == symbolStr) ||
        (board[0][2] == symbolStr && board[2][2] == symbolStr && board[4][2] == symbolStr) ||
        (board[0][4] == symbolStr && board[2][4] == symbolStr && board[4][4] == symbolStr)
        )
        return 1;

    // diagonals
    if((board[0][0] == symbolStr && board[2][2] == symbolStr && board[4][4] == symbolStr) ||
        (board[0][4] == symbolStr && board[2][2] == symbolStr && board[4][0] == symbolStr))
        
        return 1;


    return 0;

}








int main(){


//User chooses to play a friend or computer.
    int user_choice;
    cout << "How do you want to play? \n1.With a Friend.\n2.With Computer.\nEnter 1 or 2: ";
    cin >> user_choice;
    
    //^ Creating board (Kind of a roundabout way.)
    string board[5][5];
    clear_board(board);
    
    
    //^ Player Vs Player

    if(user_choice==1){
        int winP1,winP2,lossP1,lossP2,draws;
        load_score(winP1,winP2,lossP1,lossP2,draws);
        string temp;
        
        cout << "Want to use previous score?";
        cin >> temp;

        if(temp[0] == 'Y' || temp[0] == 'y'){
            cout << "OK!" << endl;
        }
        else{
            winP1 = 0;
            winP2 = 0;
            lossP1 = 0;
            lossP2 = 0;
            draws = 0;
        }



        bool play = true;
        int result = 0;
        int turn = 0;
        

        while(play==true){

            cout << "Player 1: " << winP1 << " Wins, " << lossP1 << " Losses.\n";
            cout << "Player 2: " << winP2 << " Wins, " << lossP2 << " Losses.\n";
            cout << "Draws: " << draws << endl;
            
            if(turn >0){
                cout << "\nWant to play again?: Y/N ";
                cin >> temp;
                if(temp[0] =='Y' || temp[0] =='y'){
                    turn = 0;
                    result = 0;
                    clear_board(board);
                    
                }
                else{break;}
            }

        
        // Max 9 Turns, after that terminates 
            while(turn < 9 && result != 1){
                
                // Co ordintated
                int x,y;
                char symbol;
                cls_screen();
                //& Print Board;
                for(int i=0;i<=4;i++){
                    for(int j=0;j<=4;j++){
                        cout << board[i][j];
                        }
                    cout << endl;
                    }   
                if(turn>3){

                    result = winchecklogic(board,symbol);
                    if(result==1){
                        if(symbol == 'X'){
                            cout << "Player 1 Wins!!!!";
                            winP1 +=1;lossP2+=1;
                            save_score(winP1,winP2,lossP1,lossP2,draws);
                            break;
                        }
                        else{
                            cout << "Player 2 Wins!!!!";
                            winP2+=1;lossP1+=1;
                            save_score(winP1,winP2,lossP1,lossP2,draws);
                            break;
                        }
                    }
                }
                if(turn % 2 == 0){ // Player 1's Turn
                    if(turn == 0){ // Extra info for first round/turn of the game.
                        symbol = 'O';
                        cout << "Player 1's Turn\n\nEnter coordinated seperated by space: ";
                    } 
                    else{
                        symbol = 'O';
                        cout << "Player 1's Turn: ";
                    }


                }
                else{
                    symbol = 'X';
                    cout << "Player 2's Turn: ";
                }
                cin >> x >> y;
                if(x < 0 || x > 2 || y < 0 || y > 2 || board[x*2][y*2] != " ") {
                    cout << "Invalid move. Try again." << endl;
                     // Skip this iteration if the move is invalid
                }
                else{

                    // Place the symbol on the correct coordinates
                    board[x*2][y*2] = symbol;
                    turn++; 
                }

                //checking for draws, if turns exceed 8(meaning no result) make it draw.
                if(turn>8){
                    cout << "\nDraw!!!";
                    draws+=1;
                    save_score(winP1,winP2,lossP1,lossP2,draws);
                }

            }
        }

        

        }
        else if(user_choice==2){
            
            bool play = true;
            int result = 0;
            int turn = 0;
            string temp;


            while(play==true){

                if(turn >0){
                cout << "\nWant to play again?: Y/N ";
                cin >> temp;
                if(temp[0] =='Y' || temp[0] =='y'){
                    turn = 0;
                    result = 0;
                    clear_board(board);
                    
                }
                else{break;}
            }

        
        // Max 9 Turns, after that terminates 
            while(turn < 9 && result != 1){
                
                // Co ordintated
                int x,y;
                char symbol;
                cls_screen();
                //& Print Board;
                for(int i=0;i<=4;i++){
                    for(int j=0;j<=4;j++){
                        cout << board[i][j];
                        }
                    cout << endl;
                    }   
                
                if(turn % 2 == 0){ // Player's Turn
                    if(turn == 0){ // Extra info for first round/turn of the game.
                        symbol = 'O';
                        cout << "Player's Turn\n\nEnter coordinated seperated by space: ";
                    } 
                    else{
                        symbol = 'O';
                        cout << "Player's Turn: ";
                    }


                }
                else{
                    symbol = 'X';
                    cout << "Computer's Turn: ";
                }
                
                if(symbol == 'X'){
                    // will get random numbers until it chooses a valid box.
                    while(board[x*2][y*2] != " "){

                        pair<int, int> coord = coord_gen();
                        x = coord.first;
                        y = coord.second;
                    }
                }
                else{
                    cin >> x >> y;
                }


                if(x < 0 || x > 2 || y < 0 || y > 2 || board[x*2][y*2] != " ") {
                    cout << "Invalid move. Try again." << endl;
                     // Skip this iteration if the move is invalid
                }
                else{

                    // Place the symbol on the correct coordinates
                    board[x*2][y*2] = symbol;
                    turn++; 
                }

                
                if(turn>3){

                    result = winchecklogic(board,symbol);
                    if(result==1){
                        if(symbol == 'X'){
                            cout << "Computer Wins!!!!";
                            break;
                        }
                        else{
                            cout << "Player Wins!!!!";
                            break;
                        }
                    }
                }
                //checking for draws, if turns exceed 8(meaning no result) make it draw.
                if(turn>8){
                    cout << "\nDraw!!!";
                    }

            }
        }

        



        }
        else{
            cout << "Invalid Choice";
        }



    return 0;
    }

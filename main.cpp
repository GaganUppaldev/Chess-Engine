#include<iostream>
using namespace std;


class piece{
    public:
    string color;
    string symbol;
    

    //constructor
    piece(string c , string s) : color(c) , symbol(s) {};
    
    virtual bool isvalidmove(int st , int sc , int dr , int dc , piece* grid[8][8]) = 0;    

    //return color + symbol on call from function display
    string getdisplay(){
        return color + symbol; 
    }

    virtual ~piece() {}
    


};

//pawn move
class Pawn : public piece{
    public:
    //constructor 
    Pawn(string c) : piece(c,"P") {};
    bool isvalidmove(int sr , int sc , int dr ,int dc , piece* grid[8][8]) override{
       // Boundary check
        if(dr < 0 || dr > 7 || dc < 0 || dc > 7)
            return false;

        // WHITE PAWN
        if(color == "W"){

            // Move forward 1 (must be empty)
            if(dr == sr - 1 && sc == dc && grid[dr][dc] == nullptr)
                return true;

            // First move 2 steps
            if(sr == 6 && dr == sr - 2 && sc == dc &&
               grid[sr - 1][sc] == nullptr &&
               grid[dr][dc] == nullptr)
                return true;

            // Diagonal capture
            if(dr == sr - 1 && abs(dc - sc) == 1 &&
               grid[dr][dc] != nullptr &&
               grid[dr][dc]->color == "B")
                return true;
        }

        // BLACK PAWN
        if(color == "B"){

            // Move forward 1
            if(dr == sr + 1 && sc == dc && grid[dr][dc] == nullptr)
                return true;

            // First move 2 steps
            if(sr == 1 && dr == sr + 2 && sc == dc &&
               grid[sr + 1][sc] == nullptr &&
               grid[dr][dc] == nullptr)
                return true;

            // Diagonal capture
            if(dr == sr + 1 && abs(dc - sc) == 1 &&
               grid[dr][dc] != nullptr &&
               grid[dr][dc]->color == "W")
                return true;
        }

        return false;
    }
    
};
    
//Rock
class Rock : public piece{
    public:
    Rock(string c ) : piece(c,"R"){}
    //override 
    bool isvalidmove(int sr , int sc , int dr , int dc , piece* grid[8][8]) override {

       
    // boundary check
    if(dr < 0 || dr > 7 || dc < 0 || dc > 7)
        return false;

    // rook must move in straight line
    if(sr != dr && sc != dc)
        return false;

    // moving vertically down
    if(dr > sr){
        for(int i = sr + 1; i < dr; i++){
            if(grid[i][sc] != nullptr)
                return false;
        }
    }

    // moving vertically up
    if(dr < sr){
        for(int i = sr - 1; i > dr; i--){
            if(grid[i][sc] != nullptr)
                return false;
        }
    }

    // moving right
    if(dc > sc){
        for(int i = sc + 1; i < dc; i++){
            if(grid[sr][i] != nullptr)
                return false;
        }
    }

    // moving left
    if(dc < sc){
        for(int i = sc - 1; i > dc; i--){
            if(grid[sr][i] != nullptr)
                return false;
        }
    }

    // cannot capture own piece
    if(grid[dr][dc] != nullptr && grid[dr][dc]->color == color)
        return false;

    return true;
}

  
     


};

//Bishop

class Bishop : public piece {
    public:
    Bishop(string c) : piece(c , "BS"){}
    bool isvalidmove(int sr , int sc , int dr , int dc , piece* grid[8][8]) override {
        //boundry check 
        if(dr < 0 || dr > 7 || dc < 0 || dc > 7){
            return false;
        }

        //must move in daigonal 
        if(abs(dr - sr) != abs(dc - sc)){
            return false;
        }

        //direction check
         int rowStep = (dr > sr) ? 1 : -1;
         int colStep = (dc > sc) ? 1 : -1;


         int r = sr + rowStep;
         int c = sc + colStep;
        while(r != dr){
            if(grid[r][c] != nullptr)
            return false;
            r += rowStep;
            c += colStep;

            // cannot capture own piece
           if(grid[dr][dc] != nullptr && grid[dr][dc]->color == color)
           return false;
    }

    return true;
        
    }


};


//queen

class Queen : public piece{
    public:
    Queen(string c) : piece(c , "Q"){}
    bool isvalidmove(int sr , int sc , int dr , int dc , piece* grid[8][8]) override{
        //boudry check 
        if(dr < 0 || dr > 7 || dc < 0 || dc > 7){
            return false;
        }

        //check if move is valid for rook or bishop
        Rock tempR(color);//temporary object of rock and bishop to check if move is valid for either of them because queen can move like both
        Bishop tempB(color);
        if(tempR.isvalidmove(sr, sc, dr, dc, grid) || tempB.isvalidmove(sr, sc, dr, dc, grid)){
            return true;
        }
        return false;
        


    }

};

class knight : public piece{
    public:
    knight(string c) : piece(c,"K"){}
    bool isvalidmove(int sr , int sc , int dr , int dc , piece* grid[8][8]) override{

        //boundry check 
        if(dr < 0 || dr > 7 || dc < 0 || dc > 7){
            return false;
        }
        //knight L Shape move check
        int r = abs(dr - sr);
        int c = abs(dc - sc);

        
        if((r == 2 && c == 1) || (r == 1 && c == 2)){

            // cannot capture own piece
            if(grid[dr][dc] != nullptr && grid[dr][dc]->color == color)
                return false;

            return true;
        }

        return false;


    }
};
//king 

class King : public piece{
    public:
    King(string c) : piece(c , "*"){}
    bool isvalidmove(int sr , int sc , int dr , int dc , piece* grid[8][8]) override{
        //boundry check
        if(dr < 0 || dr > 7 || dc < 0 || dc > 7){
            return false;
        }

        int r = abs(dr - sr);
        int c = abs(dc - sc);

        // king can move 1 square in any direction
        if(r <= 1 && c <= 1){

            // cannot capture own piece
            if(grid[dr][dc] != nullptr && grid[dr][dc]->color == color)
                return false;

            return true;
        }
        
        return false;
    }
};





class Board{
    //grid made , every box of grid is pointer of piece means it will store object adress objects created  by constructor piece now via adress we shifts adress and make
    //moves in chess or our whole logic is moving addresses or pointers in the game 
    piece* grid[8][8]; 
    public:
    Board(){
        for(int i = 0 ; i < 8 ; i++){
            for(int j = 0; j < 8 ; j++){
                grid[i][j] = nullptr;
                
            }
        }

        setup();
    }
    
    //setup

    
    void setup(){
        //black pawns
        for(int i = 0; i < 8 ; i++){
            grid[1][i] = new Pawn("B");
        }

        //white pawns
        for(int i = 0 ; i < 8 ; i++){
            grid[6][i] = new Pawn("W");
        }

        // black rooks
        grid[0][0] = new Rock("B");
        grid[0][7] = new Rock("B");

        // white rooks
        grid[7][0] = new Rock("W");
        grid[7][7] = new Rock("W");

        //bishops 
        grid[0][2] = new Bishop("B");
        grid[0][5] = new Bishop("B");
        grid[7][2] = new Bishop("W");
        grid[7][5] = new Bishop("W");
        
        //queen
        grid[0][3] = new Queen("B");
        grid[7][3] = new Queen("W");
        
        //knight
        grid[0][1] = new knight("B");
        grid[0][6] = new knight("B");

        grid[7][1] = new knight("W");
        grid[7][6] = new knight("W");

        //king 
        grid[0][4] = new King("B");
        grid[7][4] = new King("W");
    }
    

    //display 
    void display(){
        for(int i = 0 ; i < 8 ; i++){
            for(int j = 0 ; j < 8 ; j++){
                if(grid[i][j] != nullptr){
                    cout << grid[i][j]->getdisplay() << " ";
                }else{
                    cout << "-- ";
                }
            }
            cout << endl;
        }
    }
    
    void move(int sr , int sc , int dr , int dc ){
        if(grid[sr][sc] == nullptr){
            cout << "No piece there !" << endl;
             return;
        }

        if(grid[sr][sc]->isvalidmove(sr,sc,dr,dc,grid)){
            grid[dr][dc] = grid[sr][sc];
            grid[sr][sc] = nullptr;

        }else{
            cout << "Invalid move!";
        }
    }

    ~Board(){

    for(int i = 0 ; i < 8 ; i++){
        for(int j = 0 ; j < 8 ; j++){
            delete grid[i][j];
        }

      }

    }
    
};

int main() {

cout << "Chess Engine" << endl;
Board board;
board.display();
//movments
cout << "\nMoving white pawn from (6,0) to (5,0)\n\n";

    /*
    board.move(6,0,5,0);
    
    board.display();
    cout << "Rock movement << endl" << endl;
    board.move(7,0,6,0);
    */
    board.display();
    


}


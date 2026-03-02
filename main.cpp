#include<iostream>
using namespace std;


class piece{
    public:
    string color;
    string symbol;
    

    //constructor
    piece(string c , string s) : color(c) , symbol(s) {};
    
    virtual bool isvalidmove(int st , int sc , int dr , int dc) = 0;    

    //return color + symbol on call from function display
    string getdisplay(){
        return color + symbol; 
    }
};


class Pawn : public piece{
    public:
    //constructor 
    Pawn(string c) : piece(c,"P") {};
    bool isvalidmove(int sr , int sc , int dr ,int dc) override{
       if(color == "W" && dr == sr - 1 && sc == dc) 
            return true;

        if(color == "B" && dr == sr + 1 && sc == dc)
            return true;

        return false;
    }
    
};
    

class queen: public piece{
    public:
    queen(string c ) : piece(c,"Q"){}


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
        }

        if(grid[sr][sc]->isvalidmove(sr,sc,dr,dc)){
            grid[dr][dc] = grid[sr][sc];
            grid[sr][sc] = nullptr;

        }else{
            cout << "Invalid move!";
        }
    }
    
};

int main() {

cout << "We did it mate" << endl;
Board board;
board.display();
//movments
cout << "\nMoving white pawn from (6,0) to (5,0)\n\n";
    board.move(6,0,5,0);

    board.display();



}

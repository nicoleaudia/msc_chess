#include <iostream>
#include <cstdlib> //for absolute value
#include <cassert>
#include "ChessPiece.h"
#include "ChessBoard.h" //trying this to see if i still get the error

using namespace std;

//overloads the output operator to output a string instead of an integer value for pieceColor
ostream &operator<<(ostream &out, const Color& color) {
  switch(color){
  case black:
    out << "Black"; break;
  case white:
    out << "White"; break;
  }
  return out;
}

ChessPiece::ChessPiece(Color c){
  pieceColor = c;
}

ChessPiece::~ChessPiece() {}

Color ChessPiece::getColor(){
  return pieceColor;
}

//Pawn methods -------------------------------------------------------------------------------------------------------
Pawn::Pawn(Color c) : ChessPiece(c) {}

Pawn::~Pawn() {};

bool Pawn::isFirstMove(int startingRow){
  if (this->getColor() == white && startingRow == 6){
    return true;
  }
  if (this->getColor() == black && startingRow == 1){
    return true;
  }
  else {
    return false;
  }
}

bool Pawn::isValidMove(ChessBoard &cb, int startingRow, int startingCol, int moveToRow, int moveToCol) {

  int rowMoveDirection;
  if (getColor() == white){
    rowMoveDirection = -1;
  }
  else {
    rowMoveDirection = 1;
  }

  //if straight
  if (moveToCol == startingCol){
    if (cb.getPiece(moveToRow, moveToCol) == nullptr){
      if (isFirstMove(startingRow) && (moveToRow == startingRow + (rowMoveDirection * 2)) && cb.isStraightClear(startingRow, startingCol, moveToRow, moveToCol)){
        return true;
      }
      else if (moveToRow == (startingRow + rowMoveDirection)){
        return true;
      }
      else{
        return false;
      }
    }
  }

  //if diagonal
  if (moveToRow == (startingRow + rowMoveDirection)){
    if ((moveToCol == startingCol + 1) || (moveToCol == startingCol - 1)){
      if (cb.getPiece(moveToRow, moveToCol) != nullptr){
        return true;
      }
    }
  }

  return false;
}
/*
  if (getColor() == white){
    //check condition only allowed if it's first move
    if (isFirstMove(startingRow)){
      //still need to figure out how to check what's at location...
      if((moveToRow == startingRow - 2) && (moveToCol == startingCol) && cb.isStraightClear(startingRow, startingCol, moveToRow, moveToCol) && cb.getPiece(moveToRow, moveToCol) == nullptr){
        cout << cb.getPiece(moveToRow, moveToCol);
        cout << "this is white pawn's first move, and it's moving 2 spaces forward." << endl;
        return true;
      }
    }
    //check conditions allowed for any valid move (including first)
    if (!isFirstMove(startingRow) || isFirstMove(startingRow)){
      if ((moveToRow == startingRow - 1) && (moveToCol == startingCol) && cb.isStraightClear(startingRow, startingCol, moveToRow, moveToCol) && cb.getPiece(moveToRow, moveToCol) == nullptr){
        cout << cb.getPiece(moveToRow, moveToCol);
        cout << "this is either the white pawn's first move or not, but it's moving forward 1 space." << endl;
      return true;
      }
      if (moveToRow == startingRow - 1){
        if ((moveToCol == startingCol + 1) || (moveToCol == startingCol - 1)){
          if (cb.isDiagonalClear(startingRow, startingCol, moveToRow, moveToCol)){
            cout << "this is either the white pawn's first move or not, but it's moving diagonally forward one space." << endl;
            return true;
          }
        }
      }   
    } 
  }//white brace

  if (getColor() == black){
    //check condition only allowed if it's first move
    if (isFirstMove(startingRow)){
      //still need to figure out how to check what's at location...
      if((moveToRow == startingRow + 2) && (moveToCol == startingCol) && cb.isStraightClear(startingRow, startingCol, moveToRow, moveToCol) && cb.getPiece(moveToRow, moveToCol) == nullptr){
        cout << cb.getPiece(moveToRow, moveToCol);
        cout << "this is black pawn's first move, and it's moving 2 spaces forward." << endl;
        return true;
      }
    }
    //check conditions allowed for any valid move (including first)
    if (!isFirstMove(startingRow) || isFirstMove(startingRow)){
      if ((moveToRow == startingRow + 1) && (moveToCol == startingCol) && cb.isStraightClear(startingRow, startingCol, moveToRow, moveToCol) && cb.getPiece(moveToRow, moveToCol) == nullptr){
        cout << cb.getPiece(moveToRow, moveToCol);
        cout << "this is either the black pawn's first move or not, but it's moving forward 1 space." << endl;
        return true;
      }
      if (moveToRow == startingRow + 1){
        if ((moveToCol == startingCol + 1) || (moveToCol == startingCol - 1)){
          if (cb.isDiagonalClear(startingRow, startingCol, moveToRow, moveToCol)){
            cout << "this is either the black pawn's first move or not, but it's moving diagonally forward one space." << endl;
            return true;
          }
        }
      }
    } 
  } //black brace
  
  return false; 
   //maybe need return msg? idk
} */


const char* Pawn::getName(){
  return "Pawn";
}

//Knight methods -------------------------------------------------------------------------------------------------------
Knight::Knight(Color c) : ChessPiece(c) {}

Knight::~Knight() {};

bool Knight::isValidMove(ChessBoard &cb, int startingRow, int startingCol, int moveToRow, int moveToCol) {
  //horizontal L-diagonal toward row 8, either left or right
  if (moveToRow == startingRow - 1){
    if ((moveToCol == startingCol + 2) || (moveToCol == startingCol - 2)){
      //cout << "knight moves in horizontal L toward row 8 (top of board)" << endl;
      return true;
    }
  }

  //vertical L-diagonal toward row 8, either left or right
  if (moveToRow == startingRow - 2){
    if ((moveToCol == startingCol + 1) || (moveToCol == startingCol - 1)){
      //cout << "knight moves in vertical L toward row 8 (top of board)" << endl;
      return true;
    }
  }

  //horizontal L-diagonal toward row 1, either left or right
  if (moveToRow == startingRow + 1){
    if ((moveToCol == startingCol + 2) || (moveToCol == startingCol - 2)){
      //cout << "knight moves in horizontal L toward row 1 (bottom of board)" << endl;
      return true;
    }
  }

  //vertical L-diagonal toward row 1, either left or right
  if (moveToRow == startingRow + 2){
    if ((moveToCol == startingCol + 1) || (moveToCol == startingCol - 1)){
      //cout << "knight moves in vertical L toward row 1 (bottom of board)" << endl;
      return true;
    }
  }
  return false;
}

const char* Knight::getName(){
  return "Knight";
}

//Bishop methods -------------------------------------------------------------------------------------------------------
Bishop::Bishop(Color c) : ChessPiece(c) {}

Bishop::~Bishop() {};

bool Bishop::isValidMove(ChessBoard &cb, int startingRow, int startingCol, int moveToRow, int moveToCol) {
  int n = abs(moveToRow - startingRow);
  if (n > 7){
    return false;
  }
  if (n != abs(moveToCol - startingCol)){
    return false;
  }
  if (!cb.isDiagonalClear(startingRow, startingCol, moveToRow, moveToCol)){
    return false;
  }
  return true;
}

const char* Bishop::getName(){
  return "Bishop";
}


//Rook methods -------------------------------------------------------------------------------------------------------
Rook::Rook(Color c) : ChessPiece(c) {}

Rook::~Rook() {};

bool Rook::isValidMove(ChessBoard &cb, int startingRow, int startingCol, int moveToRow, int moveToCol) {
  if ((startingRow == moveToRow) || (startingCol == moveToCol)){
    if (cb.isStraightClear(startingRow, startingCol, moveToRow, moveToCol)){
    return true;
    }
  }
  return false;
}

const char* Rook::getName(){
  return "Rook";
}

//Queen methods -------------------------------------------------------------------------------------------------------
Queen::Queen(Color c) : ChessPiece(c) {}

Queen::~Queen() {};

bool Queen::isValidMove(ChessBoard &cb, int startingRow, int startingCol, int moveToRow, int moveToCol) {
  if ((startingRow == moveToRow) || (startingCol == moveToCol)){
    if (cb.isStraightClear(startingRow, startingCol, moveToRow, moveToCol)){
    //cout << "queen will move straight." << endl;
    return true;  
    }
  }

  int n = abs(moveToRow - startingRow);

  if (n == abs(moveToCol - startingCol)){
    if (cb.isDiagonalClear(startingRow, startingCol, moveToRow, moveToCol)){
      //cout << "queen will move diagonally." << endl;
      return true;
    }
  }
  return false;
}

const char* Queen::getName(){
  return "Queen";
}

//King methods -------------------------------------------------------------------------------------------------------
King::King(Color c) : ChessPiece(c) {}

King::~King() {};

bool King::isValidMove(ChessBoard &cb, int startingRow, int startingCol, int moveToRow, int moveToCol) {
  int rowDiff = moveToRow - startingRow;
  int colDiff = moveToCol - startingCol;

  if (abs(rowDiff) == 1 && colDiff == 0){
    return true;
  }
  if (rowDiff == 0 && abs(colDiff) == 1){
    return true;
  }
  if (abs(rowDiff) ==  1 && abs(colDiff) == 1){
    return true;
  }
  return false;
}

const char* King::getName(){
  return "King";
}
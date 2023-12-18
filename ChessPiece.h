/* ChessPiece.h - header file for the class ChessPiece and its subclasses */

#ifndef CHESSPIECE_H
#define CHESSPIECE_H

//defines data type Color to fix possible values for a ChessPiece's color to black(0) or white(1)
enum Color { black, white };

#include <iostream>
#include "ChessBoard.h"

class ChessBoard;

/*********************** Class ChessPiece ***************************/



//overloads the output operator to output a string instead of an integer value for Color
std::ostream& operator << (std::ostream&, const Color& color);


class ChessPiece {
public:
  ChessPiece(Color); //constructor

  virtual ~ChessPiece();
  
  virtual bool isValidMove(ChessBoard&, int, int, int, int) = 0; //0 means this fxn does not have an implementation. so pure virtual (virtual could have default)

  Color getColor(); //not virtual bc it's not going to change for children. no need for dynamic binding

  //void setColor(char&);

  virtual const char* getName() = 0;

  // virtual bool isPathClear(ChessPiece* [8][8], int, int, int, int) = 0;

private: 
  Color pieceColor; //use getter and setter to access
};

/*********************** Child Classes ***************************/

class Pawn : public ChessPiece {
public:
  Pawn(Color);

  ~Pawn() override;
  
  bool isValidMove(ChessBoard&, int, int, int, int) override; //override asks the compiler to give us an error if they don't know what fxn to override

  const char* getName() override;

  bool isFirstMove(int);

};

class Knight : public ChessPiece {
public:
  Knight(Color);

  ~Knight() override;
  
  bool isValidMove(ChessBoard&, int, int, int, int) override; //override asks the compiler to give us an error if they don't know what fxn to override

  const char* getName() override;

};

class Bishop : public ChessPiece {
public:
  Bishop(Color);

  ~Bishop() override;
  
  bool isValidMove(ChessBoard&, int, int, int, int) override; //override asks the compiler to give us an error if they don't know what fxn to override

  const char* getName() override;

};

class Rook : public ChessPiece {
public:
  Rook(Color);

  ~Rook() override;
  
  bool isValidMove(ChessBoard&, int, int, int, int) override; //override asks the compiler to give us an error if they don't know what fxn to override

  const char* getName() override;


};

class Queen : public ChessPiece {
public:
  Queen(Color);

  ~Queen() override;
  
  bool isValidMove(ChessBoard&, int, int, int, int) override; //override asks the compiler to give us an error if they don't know what fxn to override

  const char* getName() override;

};

class King : public ChessPiece {
public:
  King(Color);

  ~King() override;
  
  bool isValidMove(ChessBoard&, int, int, int, int) override; //override asks the compiler to give us an error if they don't know what fxn to override

  const char* getName() override;

};

#endif

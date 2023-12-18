/* ChessPiece.h - header file for the class ChessPiece and its subclasses */

#ifndef CHESSPIECE_H
#define CHESSPIECE_H

/* Purpose: Defines data type Color to fix possible values for a chess piece's 
 * color to black (0) or white (1).
 */
enum Color { black, white };

#include <iostream>
#include "ChessBoard.h"

class ChessBoard;

/*********************** Class ChessPiece ***************************/

/* Purpose: Overloads the output operator to output a string instead of an 
* integer value for variables of the data type Color (Color enumeration).
 */
std::ostream& operator << (std::ostream&, const Color& color);


class ChessPiece {
public:

  /* Purpose: Constructs a ChessPiece object. 
   *
   * @param c: Takes a Color data type (Color enumeration) that represents
   * the color (white or black) of the chess piece.
   */
  ChessPiece(Color c);


  /* Purpose: Destroys a ChessPiece object */
  virtual ~ChessPiece();
  

  /* Purpose: Determines the validity of a proposed move of a particular
   * chess piece on a chess board.
   *
   * Note that implementation is defined in child classes.
   * 
   * @param cb: Takes a ChessBoard object representing the game's chess board.
   * 
   * @param startingRow: Takes an integer 0-7 representing a particular row 
   * where the chess piece is initially.
   * 
   * @param startingCol: Takes an integer 0-7 representing a particular column 
   * where the piece is initially.
   * 
   * @param moveToRow: Takes an integer 0-7 representing a particular row 
   * where the piece is proposed to move.
   * 
   * @param moveToRow: Takes an integer 0-7 representing a particular column 
   * where the piece is proposed to move.
   */
  virtual bool isValidMove(ChessBoard& cb, int startingRow, int startingCol, int moveToRow, int moveToCol) = 0; 


  /* Purpose: Gets the color of a ChessPiece object. Color values (white and
   * black) are defined in the Color enumeration.
   */
  Color getColor();

  /* Purpose: Gets the name of a ChessPiece object.
   *
   * Note that implementation is defined in child classes.
   */
  virtual const char* getName() = 0;


private: 
  Color pieceColor; //use getter and setter to access
};

/*********************** Child Classes ***************************/

class Pawn : public ChessPiece {
public:

  /* Purpose: Constructs a Pawn object, which inherits from ChessPiece.
   *
   * @param c: Takes a Color data type (Color enumeration) that represents
   * the color (white or black) of the Pawn chess piece.
   */
  Pawn(Color c);


  /* Purpose: Destroys a Pawn object. */
  ~Pawn() override;
  

  /* Purpose: Determines the validity of a proposed move of a Pawn object on 
   * a chess board. A Pawn's move is valid if it: (a) moves forward 2 squares
   * (only allowed on the first move), providing both are unoccupied; (b) 
   * moves forward 1 square if unoccupied; or (c) moves diagonally forward 1 to an 
   * occupied square, capturing the piece in that square.
   *
   * See parameter details in parent class method.
   */
  bool isValidMove(ChessBoard&, int, int, int, int) override;


  /* Purpose: Gets name "Pawn" for a Pawn object. */
  const char* getName() override;


  /* Purpose: Determines if it's a Pawn's first move.

   * Should be called to determine the validity of a proposed move,
   * as the pawn can only move forward 2 squares (unoccupied) on the
   * first move.
   * 
   * @param startingRow: Takes an integer 0-7 representing a particular row 
   * where the pawn chess piece is initially.
   */
  bool isFirstMove(int startingRow);

};


class Knight : public ChessPiece {
public:

  /* Purpose: Constructs a Knight object, which inherits from ChessPiece.
   *
   * @param c: Takes a Color data type (Color enumeration) that represents
   * the color (white or black) of the Knight chess piece.
   */
  Knight(Color c);


  /* Purpose: Destroys a Knight object. */
  ~Knight() override;
  

  /* Purpose: Determines the validity of a proposed move of a Knight object on 
   * a chess board. A Knight's move is valid if it: (a) moves 2 squares vertically
   * and 1 square horizontally; or (b) moves 1 square vertically and 2 squares
   * horizontally. A Knight can leap over other pieces in its path.
   *
   * See parameter details in parent class method.
   */
  bool isValidMove(ChessBoard&, int, int, int, int) override; 


  /* Purpose: Gets name "Knight" for a Knight object. */
  const char* getName() override;

};

class Bishop : public ChessPiece {
public:

  /* Purpose: Constructs a Bishop object, which inherits from ChessPiece.
   *
   * @param c: Takes a Color data type (Color enumeration) that represents
   * the color (white or black) of the Bishop chess piece.
   */
  Bishop(Color c);


  /* Purpose: Destroys a Bishop object. */
  ~Bishop() override;
  

  /* Purpose: Determines the validity of a proposed move of a Bishop object on 
   * a chess board. A Bishop's move is valid if it is moves any number of squares
   * diagonally, but does not leap over other pieces.
   *
   * See parameter details in parent class method.
   */
  bool isValidMove(ChessBoard&, int, int, int, int) override;


  /* Purpose: Gets name "Bishop" for a Bishop object. */
  const char* getName() override;

};


class Rook : public ChessPiece {
public:

  /* Purpose: Constructs a Rook object, which inherits from ChessPiece.
   *
   * @param c: Takes a Color data type (Color enumeration) that represents
   * the color (white or black) of the Rook chess piece.
   */
  Rook(Color c);


  /* Purpose: Destroys a Rook object. */
  ~Rook() override;
  

  /* Purpose: Determines the validity of a proposed move of a Rook object on 
   * a chess board. A Rook's move is valid if it is moves any number of squares
   * vertically or horizontally, but does not leap over other pieces.
   *
   * See parameter details in parent class method.
   */
  bool isValidMove(ChessBoard&, int, int, int, int) override; 


  /* Purpose: Gets name "Rook" for a Rook object. */
  const char* getName() override;

};


class Queen : public ChessPiece {
public:

  /* Purpose: Constructs a Queen object, which inherits from ChessPiece.
   *
   * @param c: Takes a Color data type (Color enumeration) that represents
   * the color (white or black) of the Queen chess piece.
   */
  Queen(Color c);


  /* Purpose: Destroys a Queen object. */
  ~Queen() override;
  

  /* Purpose: Determines the validity of a proposed move of a Queen object on 
   * a chess board. A Queen's move is valid if it is moves any number of squares
   * diagonally, vertically, or horizontally, but does not leap over other pieces.
   *
   * See parameter details in parent class method.
   */
  bool isValidMove(ChessBoard&, int, int, int, int) override; 


  /* Purpose: Gets name "Queen" for a Queen object. */
  const char* getName() override;

};


class King : public ChessPiece {
public:

   /* Purpose: Constructs a King object, which inherits from ChessPiece.
   *
   * @param c: Takes a Color data type (Color enumeration) that represents
   * the color (white or black) of the King chess piece.
   */
  King(Color c);

  /* Purpose: Destroys a King object. */
  ~King() override;

  /* Purpose: Determines the validity of a proposed move of a King object on 
   * a chess board. A King's move is valid if it is moves 1 square in any
   * direction.
   *
   * See parameter details in parent class method.
   */
  bool isValidMove(ChessBoard&, int, int, int, int) override;


  /* Purpose: Gets name "King" for a King object. */
  const char* getName() override;

};

#endif

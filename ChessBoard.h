/* ChessBoard.h - header file for the class ChessBoard */

#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "ChessPiece.h"

using namespace std;


class ChessPiece;
class King;

/*********************** Class ChessBoard ***************************/
class ChessBoard {
private:
  ChessPiece* boardLayout[8][8];

  Color turnColor;

  King* whiteKingPtr;

  King* blackKingPtr;

public:
  ChessBoard(); //constructor

  ChessPiece* pieceIdentifier(char);

  void loadState(const char*);

  void submitMove(const char*, const char*);

  ChessPiece* getPiece(int, int) const;

  bool isDiagonalClear(int, int, int, int);

  bool isStraightClear(int, int, int, int);

  bool isKingInCheck(Color);

  void findKing(King*, int&, int&);

  // bool searchForValidMoves(Color c);

  bool willMovePutKingInCheck(Color, int, int, int, int);

  bool isKingInCheckMate(Color);

  Color getFenColor(char);

  void printChessBoard(const ChessBoard&);
};

#endif


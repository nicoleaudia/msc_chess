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

  /* Purpose: Stores ChessPiece* (pointers) in an 8x8 2D array,
  * representing the layout of a chess board. 
  */
  ChessPiece* boardLayout[8][8];


  /* Purpose: Stores the color of the turn of the game, e.g. in
   * chess, black or white. 
   */
  Color turnColor;


  /* Pointer to the white king piece on the chess board,
   * allowing the program to find its position.
   */
  King* whiteKingPtr;


  /* Pointer to the black king piece on the chess board,
   * allowing the program to find its position.
   */
  King* blackKingPtr;


public:

  /* Purpose: Constructs a ChessBoard object. */
  ChessBoard(); 


  /* Purpose: Evaluates a character from a chess FEN record string 
   * and creates the appropriate ChessPiece child object. Follows
   * standard FEN record character definitions. For example, 'n' 
   * is black knight, 'K' is white king.
   * 
   * @param fenChar: Takes an uppercase or lowercase char from
   * standard FEN record characters.
   */
  ChessPiece* pieceIdentifier(char fenChar);


  /* Purpose: Loads the state of a chess board into the 8x8 2D array
   * ChessBoard. Loops through the FEN record to identify blank spaces,
   * black and white chess pieces, and their positions.  Blank spaces
   * will be represented by nullptrs and pieces are represented with
   * board is loaded. Additionally assigns value white and black King pointers
   * to variables whiteKingPtr and blackKingPtr respectively for use in
   * finding the king on the board (see findKing method for details).
   * 
   * @param fenRecord: Takes a standard FEN record string representing
   * 64 total positions. Does not need to be playable chess configuration
   * or initial starting configuration.
   */
  void loadState(const char* fenRecord);


  /* Purpose: Determines legality and validity of a proposed move of a 
   * particular chess piece on a chess board, and updates the board if
   * the move is allowed. After the board is updated, the turnColor is 
   * updated to the opposite color and the method also determines if the 
   * opposite color is in check, checkmate, or stalemate.
   *
   * @param startingPosition: Takes a 2-character string with the first 
   * char being A-H and the second being 1-8 representing starting position
   * of a piece on a chess board.
   * 
   * @param startingPosition: Takes a 2-character string with the first 
   * char being A-H and the second being 1-8 representing position of a p
   * piece on a chess board after a successful move.
   */
  void submitMove(const char* startingPosition, const char* moveToPosition);


  /* Purpose: Returns the pointer or nullptr at a given position on a
   * 8x8 2D array representing a chess board.
   *
   * @param row: Takes an integer 0-7 representing a particular row.
   * 
   * @param col: Takes an integer 0-7 representing a particular column.
   */
  ChessPiece* getPiece(int row, int col) const;


  /* Purpose: Determines if diagonal path across a 8x8 2D array representing
   * a chess board is free of chess pieces (ie, path only contains nullptrs).
   * Does not evaluate starting and ending positions, only positions in
   * between. 
   * 
   * Should be called if piece can move diagonally but cannot leap over pieces.
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
  bool isDiagonalClear(int startingRow, int startingCol, int moveToRow, int moveToCol);


  /* Purpose: Determines if straight (vertical or horizontal) path across a 8x8 2D 
   * array representing a chess board is free of chess pieces (ie, path only 
   * contains nullptrs). Does not evaluate starting and ending positions, only 
   * positions in between. 
   * 
   * Should be called if piece can move straight but cannot leap over pieces.
   * 
   * @param startingRow: Takes an integer 0-7 representing a particular row 
   * where the chess piece is initially.
   * 
   * @param startingCol: Takes an integer 0-7 representing a particular column 
   * where the chess piece is initially.
   * 
   * @param moveToRow: Takes an integer 0-7 representing a particular row 
   * where the chess piece is proposed to move.
   * 
   * @param moveToRow: Takes an integer 0-7 representing a particular column 
   * where the chess piece is proposed to move.
   */
  bool isStraightClear(int startingRow, int startingCol, int moveToRow, int moveToCol);


  /* Purpose: Determines if there are currently any pieces of the opposite color that 
   * could attack the current color's king in a valid move.
   * 
   * Should be called after a move is made by the opposite color.
   * 
   * @param c: Takes a Color data type (defined in Color enumeration) representing the
   * current turn color. 
   */
  bool isKingInCheck(Color);

  /* Purpose: Searches ChessBoard object (8x8 2D array) for the position (row and column)
   * of the king pointer passed in.
   *
   * @param king: Takes a King* that represents a specific king piece on a chess board.
   * 
   * @param row: Takes an integer 0-7 representing a particular row; once the king is 
   * found, the value of row is updated to the king's row.
   * 
   * @param col: Takes an integer 0-7 representing a particular column; once the king is 
   * found, the value of col is updated to the king's column.
   */
  void findKing(King* king, int& row, int& col);

  /* Purpose: Determines if a particular move of a chess piece will put the piece's 
   * own (same color) king in check. King is represented by the value stored in 
   * whiteKingPtr or blackKingPtr based on current color (see pieceIdentifier
   * method for details). 
   * 
   * Should be called before a move is made by the current color. Can be used to 
   * determine validity of move, because a move may not put the piece's own king in check.
   *
   * @param c: Takes a Color data type (defined in Color enumeration) representing
   * the current turn color. 
   * 
   * @param startingRow: Takes an integer 0-7 representing a particular row 
   * where the chess piece is initially.
   * 
   *  @param startingCol: Takes an integer 0-7 representing a particular column 
   * where the chess piece is initially.
   * 
   *  @param moveToRow: Takes an integer 0-7 representing a particular row 
   * where the chess piece is proposed to move.
   * 
   * @param moveToRow: Takes an integer 0-7 representing a particular column 
   * where the chess piece is proposed to move.
   */
  bool willMovePutKingInCheck(Color c, int startingRow, int startingCol, int moveToRow, int moveToCol);


  /* Purpose: Determines if the current color's king is in checkmate, meaning
   * there are no valid moves the color's pieces could make to get the king
   * out of check and thus the game is over. 
   *
   * Should be called when the king is in check (see isKingInCheck for details).
   * 
   * @param c: Takes a Color data type (defined in Color enumeration) representing
   * the current turn color. 
   */
  bool isKingInCheckMate(Color c);


  /* Purpose: Determines if the chess game has reached a stalemate, meaning
   * the current color is not in check but has no legal and valid moves it can make
   * (without putting the king in check). If yes, the game ends.
   *
   * Should be called when the king is not in check (see isKingInCheck for details).
   * 
   * @param c: Takes a Color data type (defined in Color enumeration) representing
   * the current turn color. 
   */
  bool isStalemate(Color c);

  
  /* Purpose: Loops through chess board (8x8 2D array) looking for all possible
   * valid moves that do not result in the current color's king being in check.
   *
   * May be used for determining checkmate or stalemate.
   * 
   * @param c: Takes a Color data type (defined in Color enumeration) representing
   * the current turn color. 
  */
  bool searchForValidMoves(Color c);
  

  /* Purpose: Determines if a character from a chess FEN record string represents
   * a black or a white chess piece. A lowercase character represents a black piece,
   * and an uppercase character represents a white piece.
   * 
   * @param fenChar: Takes an uppercase or lowercase char from
   * standard FEN record characters.
   */
  Color getFenColor(char fenChar);


  /* Purpose: Prints visual representation of chess board with chess piece 
   * pointers (memory locations) in their positions on the board to aid in testing.
   */
  void printChessBoard();


 


};

#endif


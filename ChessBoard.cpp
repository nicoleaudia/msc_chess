/* Implementation file for ChessBoard class  */
#include <iostream>
#include <cassert>
#include <iomanip>
#include "ChessPiece.h"

using namespace std;

int sign(int x){
  if (x == 0){return 0;}
  else if (x > 0){return 1;}
  else {return -1;}
}

ChessBoard::ChessBoard(){}

void ChessBoard::loadState(const char* fenRecord){

  int index = 0, row = 0, col = 0;

  //loop through FEN string until space (denotes we've passed the last square on the board)
  while (fenRecord[index] != ' '){

    //if you hit an end-of-row marker (/), reset the col value to 0 and increment the row value to load next row
    if (fenRecord[index] == '/'){
      index++;
      row++;
      col = 0;
    }

    //if you hit 1-8, determine the number of continuous blank squares on the board
    if (fenRecord[index] >= '1' && fenRecord[index] <= '8'){

      //save number of blank squares into a variable
      int blankSquaresNeeded;
      blankSquaresNeeded = (fenRecord[index] - '0');

      //set index variable to use in while loop
      int blankSquaresIndex = 0;

      //insert a null pointer (representing an empty square) into 2D array (the board)
      while (blankSquaresIndex < blankSquaresNeeded){
        boardLayout[row][col] = nullptr;
        blankSquaresIndex++;
        col++;
      }
      
      //increment index (just once for the char in the FEN string)
      index++;
    }
    
    //call pieceIdentifier to figure out what type of chess piece should be loaded onto board
    else {
      char currentFenChar = fenRecord[index];
      ChessPiece* ptr = pieceIdentifier(currentFenChar);
      boardLayout[row][col] = ptr;
      index++;
      col++;
    }
  }
        
  //move the index by 1 to reach the w/b character
  index++;

  //set initial turn color
  if (fenRecord[index] == 'w'){
    turnColor = white;
  }
  if (fenRecord[index] == 'b'){
    turnColor = black;
  }
  
  //move the index by 2 to reach the castling characters 
  index+=2; //start of castling bit of FEN

  cout << "A new board state is loaded!\n";
}

//determine type and color of chess piece based on char in FEN string
ChessPiece* ChessBoard::pieceIdentifier(char fenChar){
  ChessPiece* ptr;

  Color pieceFenColor = getFenColor(fenChar);
  
  if (fenChar == 'p' || fenChar == 'P'){
    ptr = new Pawn(pieceFenColor);
   }
  else if (fenChar == 'n' || fenChar == 'N'){
    ptr = new Knight(pieceFenColor);
    }
  else if (fenChar == 'b' || fenChar == 'B'){
    ptr = new Bishop(pieceFenColor);
  }
  else if (fenChar == 'r' || fenChar == 'R'){
    ptr = new Rook(pieceFenColor);
  }
  else if (fenChar == 'q' || fenChar == 'Q'){
    ptr = new Queen(pieceFenColor);
  }
  else if (fenChar == 'k'){
    blackKingPtr = new King(pieceFenColor); //blackKingPtr for use in findKing method for determining check
    ptr = blackKingPtr;
  }
  else if (fenChar == 'K'){
    whiteKingPtr = new King(pieceFenColor); //whiteKingPtr for use in findKing method for determining check
    ptr = whiteKingPtr;
  }
  else {
    cerr << "Not a valid FEN record character.\n";
    ptr = nullptr;
  }  
  return ptr;
}



Color ChessBoard::getFenColor(char fenChar){
  if (fenChar >= 'B' && fenChar <= 'R'){
    return white;
  }
  else {
    return black;
  }
}



void ChessBoard::submitMove(const char* startingPosition, const char* moveToPosition){

  int startingRow, startingCol, moveToRow, moveToCol;

  //run a series of checks to determine legality and validity of move on board

  //determine starting position on board
  startingCol = startingPosition[0] - 'A';
  startingRow = 7 - (startingPosition[1] - '1');

  ChessPiece* pieceToMove = boardLayout[startingRow][startingCol];

  //determine goal position for piece to move to on board
  moveToCol = moveToPosition[0] - 'A';
  moveToRow = 7 - (moveToPosition[1] - '1');

  //check that goal position is on the board
  if ((moveToRow < 0) || (moveToRow > 7) || (moveToCol < 0) || (moveToCol > 7)){
    cout << "Destination square is not within board's range." << endl;
    return;
  }

  //check that the destination square is not the starting square
  if ((moveToRow == startingRow) && (moveToCol == startingCol)){
    return;
  }
  
  //check if starting spot on board has a nullptr (ie, no piece in square)
  if (pieceToMove == nullptr){
    cout << "There is no piece at position " << startingPosition << "!" << endl;
    return;
  }

   //determine if it's this color's turn to move
  if (pieceToMove->getColor() != turnColor){
    cout << "It is not " << pieceToMove->getColor() << "'s turn to move!" << endl;
    return;
  }
  
  //override virtual method to determine if move is valid for that type of piece
  if (!pieceToMove->isValidMove(*this, startingRow, startingCol, moveToRow, moveToCol)){ 
    cout << pieceToMove->getColor() << "'s " << pieceToMove->getName() << " cannot move to " << moveToPosition << "!" << endl;
    return;
  } 

  //check that the move does not put color's own king in check
  //note that if current color's king is in check already (due to opposite color's move), it is not in checkmate (or else the game would've ended)
  //so if the color's king is in check, a legal move exists that color can make to get out of check
  if (willMovePutKingInCheck(turnColor, startingRow, startingCol, moveToRow, moveToCol)){
    cout << "Cannot make this move, as it will put own King in check" << endl;
    return;
  }

  ChessPiece* pieceToTake = boardLayout[moveToRow][moveToCol];

  //check if there is a piece of the opposite to be taken at that spot
  if (pieceToTake != nullptr && pieceToTake->getColor() == pieceToMove->getColor()){
    cout << "Cannot make this move, as the " << pieceToTake->getName() << "in this spot is own color" << endl;
    return;
  }

  //at this point, checks have determined move is legal and valid, so board can be updated
  
  //update board to store nullptr where piece used to be, and store piece data at new location
  boardLayout[startingRow][startingCol] = nullptr;
  boardLayout[moveToRow][moveToCol] = pieceToMove;
  cout << pieceToMove->getColor() << "'s " << pieceToMove->getName() << " moves from " << startingPosition << " to " << moveToPosition;

  
  if (pieceToTake != nullptr){
    cout << " taking " << pieceToTake->getColor() << "'s " << pieceToTake->getName();
    delete pieceToTake;
  } 
  
  cout << endl;

  //set currentTurnColor flag to indicate it's opposite color's turn to make a move
  turnColor = (turnColor == white) ? black : white;

  //check if move put opposite color in check; if yes, additionally check for checkmate, which ends game
  if (isKingInCheck(turnColor)){
    if (isKingInCheckMate(turnColor)){
      cout << turnColor << " is in checkmate" << endl;
      cout << '\n';
      exit(0); //end program
    }
    cout << turnColor << " is in check" << endl;
  }
  //check if move prevents opposite color from making any valid move; if so, end game in stalemate
  else {
    if (isStalemate(turnColor)){
      cout << turnColor << " has no valid moves, and thus the game ends in a stalemate" << endl;
      cout << '\n';
      exit(0); //end program
    }
  }
return;
} 



bool ChessBoard::isDiagonalClear(int startingRow, int startingCol, int moveToRow, int moveToCol){
  int rowDiff = moveToRow - startingRow;
  int colDiff = moveToCol - startingCol;

  assert(abs(rowDiff) == abs(colDiff)); //if this condition isn't met, throw an error

  int rowDir = sign(rowDiff); //function assigns 1, 0, or -1 to rowDir to represent its sign
  int colDir = sign(colDiff); //function assigns 1, 0, or -1 to colDir to represent its sign

  int r = startingRow + rowDir;
  int c = startingCol + colDir;

  while(r != moveToRow && c != moveToCol){
    if (boardLayout[r][c] != nullptr){
      return false;
    }
    r += rowDir;
    c += colDir;
  }
  return true;
}



bool ChessBoard::isStraightClear(int startingRow, int startingCol, int moveToRow, int moveToCol){
  int rowDiff = moveToRow - startingRow;
  int colDiff = moveToCol - startingCol;

  assert(rowDiff == 0 || colDiff == 0); //if this condition isn't met, throw an error

  int rowDir = sign(rowDiff); //function assigns 1, 0, or -1 to rowDir to represent its sign
  int colDir = sign(colDiff); //function assigns 1, 0, or -1 to colDir to represent its sign

  int r = startingRow + rowDir;
  int c = startingCol + colDir;

  while(r != moveToRow || c != moveToCol){
    if (boardLayout[r][c] != nullptr){
      return false;
    }
    r += rowDir;
    c += colDir;
  }
  return true;
}



ChessPiece* ChessBoard::getPiece(int row, int col) const{
  return boardLayout[row][col];
}



void ChessBoard::findKing(King* king, int &row, int &col){
  for (row = 0; row < 8; row++){
    for (col = 0; col < 8; col++){
      if (this->getPiece(row, col) == king){
        return;
      }
    }
  }
}



bool ChessBoard::isKingInCheck(Color c){

  King* king = (c == white) ? whiteKingPtr : blackKingPtr; //if color is white, assign whiteKingPtr to king; otherwise, assign blackKingPtr
  Color attackingColor = (c == white) ? black : white; //if color is white, assign black (opposite color) to attackingColor; otherwise, assign white

  int kingRow, kingCol;
  findKing(king, kingRow, kingCol);

  //loop through board; if there are any pieces of the opposite color that could move to the king's spot, return true (indicating in check)
  for (int pieceRow = 0; pieceRow < 8; pieceRow++){
    for (int pieceCol = 0; pieceCol < 8; pieceCol++){
      ChessPiece* piece = getPiece(pieceRow, pieceCol);
      if (piece != nullptr && piece->getColor() == attackingColor){ 
        if (piece->isValidMove(*this, pieceRow, pieceCol, kingRow, kingCol)){
          return true; //exit function as soon as any valid move that could attack the king is found
        }
      }
    }
  }
  return false; //if there are no pieces of the opposite color that could attack the king, the king is not in check and thus function returns false
}



bool ChessBoard::willMovePutKingInCheck(Color c, int startingRow, int startingCol, int moveToRow, int moveToCol){
    
  ChessPiece* pieceToMove = boardLayout[startingRow][startingCol];
  ChessPiece* pieceToTake = boardLayout[moveToRow][moveToCol];

  //temporarily update board state
  boardLayout[startingRow][startingCol] = nullptr;
  boardLayout[moveToRow][moveToCol] = pieceToMove;
    
  bool checkResult = isKingInCheck(c);  


  //restore original board state
  boardLayout[startingRow][startingCol] = pieceToMove;
  boardLayout[moveToRow][moveToCol] = pieceToTake;

  return checkResult;
}



bool ChessBoard::isKingInCheckMate(Color c){
 
  if (!isKingInCheck(c)){ //cannot be in checkmate unless king is already in check
    return false;
  } 
  if(!searchForValidMoves(c)){
    return true; //if no valid moves can be found to get king out of check, color is in checkmate
  }
  return false;
}



bool ChessBoard::searchForValidMoves(Color c){

  for (int pieceRow = 0; pieceRow < 8; pieceRow++){
    for (int pieceCol = 0; pieceCol < 8; pieceCol++){ //loop through board
      ChessPiece* piece = getPiece(pieceRow, pieceCol); //grab piece
      if (piece != nullptr && piece->getColor() == c){ //if piece is of current color, loop through possible moves from current position and see if any are valid
        for (int pieceMoveToRow = 0; pieceMoveToRow < 8; pieceMoveToRow++){
          for (int pieceMoveToCol = 0; pieceMoveToCol < 8; pieceMoveToCol++){

            ChessPiece* targetPiece = getPiece(pieceMoveToRow, pieceMoveToCol);

            if (pieceRow == pieceMoveToRow && pieceCol == pieceMoveToCol) { //skip (continue) if move is to starting square
              continue;
            }
            if (targetPiece != nullptr && targetPiece->getColor() == c) { //if a piece will be taken as part of the move, skip (continue) if piece is same color
              continue;
            }
            if (piece->isValidMove(*this, pieceRow, pieceCol, pieceMoveToRow, pieceMoveToCol)){ //if there are valid moves for the piece of the current color, see if move puts/keeps king in check
              if (!willMovePutKingInCheck(c, pieceRow, pieceCol, pieceMoveToRow, pieceMoveToCol)){
                return true; //if move is allowed and king is not in check after the move, a valid move exists
              }
            }
          }
        }
      }
    }
  }
  return false; 
}



bool ChessBoard::isStalemate(Color c){

  if (isKingInCheck(c)){ //cannot be in stalemate if king is currently in check
    return false;
  } 
  if(!searchForValidMoves(c)){
    return true; //if no valid moves can be found and king is not in check, game is in stalemate
  }
  return false;
}



void ChessBoard::printChessBoard() {
    const int colWidth = 18;

    //print top line
    cout << "   ";
    for (int col = 0; col < 8; ++col) {
        cout << setw(colWidth) << " +";
    }
    cout << endl;

    //loop through board and print memory locations of pieces
    for (int row = 0; row < 8; ++row) {
        cout << 8 - row << "|";
        for (int col = 0; col < 8; ++col) {
            const ChessPiece* piece = this->getPiece(row, col);
            cout << setw(colWidth) << piece;
        }
        cout << "|" << endl;

        //print separator line
        cout << "   ";
        for (int col = 0; col < 8; ++col) {
            cout << setw(colWidth) << " +";
        }
        cout << endl;
    }

    //print column labels
    cout << "    A                B                C                D                E                F                G                H" << endl;
}

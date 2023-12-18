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

  // loop through fen string until space (denotes we've passed the last square on the board)
  while (fenRecord[index] != ' '){

    // if you hit an end of row marker (/), reset the col value to 0 and increment the row value
    if (fenRecord[index] == '/'){
      index++;
      row++;
      col = 0;
    }

    // if you hit 1-8, determine the number of blank spaces to insert
    if (fenRecord[index] >= '1' && fenRecord[index] <= '8'){

      // save number of blank spaces to insert into a variable
      int blankSpaceNeeded;
      blankSpaceNeeded = (fenRecord[index] - '0');

      // index to use in while loop
      int blankSpaceIndex = 0;

      // insert a null pointer (representing an empty space) into pointer array (the board)
      while (blankSpaceIndex < blankSpaceNeeded){
        boardLayout[row][col] = nullptr;
        blankSpaceIndex++;
        col++;
      }
      
      //index (just once for the char)
      index++;
    }
    

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
  index+=2; //start of castling bit of fen

  cout << "A new board state is loaded!\n";
}

//determine type of piece based on char in fen string
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
    blackKingPtr = new King(pieceFenColor);
    ptr = blackKingPtr;
  }
  else if (fenChar == 'K'){
    whiteKingPtr = new King(pieceFenColor);
    ptr = whiteKingPtr;
  }
  else {
    cerr << "Not a valid fen record character.\n";
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


//submitMove function ----------------------------------------------------------------------------------------------------

void ChessBoard::submitMove(const char* startingPosition, const char* moveToPosition){

  int startingRow, startingCol, moveToRow, moveToCol;

  //RUN CHECKS TO DETERMINE VALIDITY OF PIECE AND MOVE

  //determine starting position on board
  startingCol = startingPosition[0] - 'A';
  startingRow = 7 - (startingPosition[1] - '1');

  ChessPiece* pieceToMove = boardLayout[startingRow][startingCol];
  //cout << pieceToMove << endl;


  //determine goal position to move piece to on board
  moveToCol = moveToPosition[0] - 'A';
  moveToRow = 7 - (moveToPosition[1] - '1');

  //check goal position is on the board
  if ((moveToRow < 0) || (moveToRow > 7) || (moveToCol < 0) || (moveToCol > 7)){
    cout << "Destination square is not within board's range." << endl;
    return;
  }

  //check that the destination square is not the starting square
  if ((moveToRow == startingRow) && (moveToCol == startingCol)){
    return;
  }
  
  //check if starting spot on board has a nullptr (ie, no piece)
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
  if (!pieceToMove->isValidMove(*this, startingRow, startingCol, moveToRow, moveToCol)){ //notation means "if false"
    cout << pieceToMove->getColor() << "'s " << pieceToMove->getName() << " cannot move to " << moveToPosition << "!" << endl;
    return;
  } 

  //at this point, doesn't matter if color is in check or not. just want to make sure willMovePutInCheck returns false.
  //if color is in check already (due to opposite color), it is not in checkmate (or else the game would've ended). so, there is a legal move that can be made here that gets out of check
  if (willMovePutKingInCheck(turnColor, startingRow, startingCol, moveToRow, moveToCol)){
    cout << "move will put king in check" << endl;
    return;
  }

  ChessPiece* pieceToTake = boardLayout[moveToRow][moveToCol];

  //check if there is a piece OF THE OPPOSITE COLOR to be taken at that spot
  if (pieceToTake != nullptr && pieceToTake->getColor() == pieceToMove->getColor()){
    cout << "TESTING SUBMITMOVE - " << pieceToTake->getName() << " piece in spot is same color" << endl;
    return;
  }

  //now we've done the checks. time to update the board
  //update board to store nullptr where piece used to be, and store piece data at new location
  boardLayout[startingRow][startingCol] = nullptr;
  boardLayout[moveToRow][moveToCol] = pieceToMove;
  cout << pieceToMove->getColor() << "'s " << pieceToMove->getName() << " moves from " << startingPosition << " to " << moveToPosition;

  
  if (pieceToTake != nullptr){
    cout << " taking " << pieceToTake->getColor() << "'s " << pieceToTake->getName();
    delete pieceToTake;
  } 
  
  cout << endl;

  //set currentTurnColor flag
  turnColor = (turnColor == white) ? black : white;

  //check if move put opposite color in check. if yes, additionally check for checkmate or stalemate
  if (isKingInCheck(turnColor)){
    if (isKingInCheckMate(turnColor)){
      cout << turnColor << " is in checkmate" << endl;
      cout << '\n';
      exit(0); //end program
    }
    cout << turnColor << " is in check" << endl;
  }
return;
} 




//isDiagonalClear- --------------------------------------------------------------------
bool ChessBoard::isDiagonalClear(int startingRow, int startingCol, int moveToRow, int moveToCol){
  int rowDiff = moveToRow - startingRow;
  int colDiff = moveToCol - startingCol;

  assert(abs(rowDiff) == abs(colDiff)); //if this condition isn't met, throw an error

  int rowDir = sign(rowDiff); //function assigns 1 or -1 to rowDir
  int colDir = sign(colDiff); //function assigns 1 or -1 to rowCol

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

//isStraightClear -------------------------------------------------------------------
bool ChessBoard::isStraightClear(int startingRow, int startingCol, int moveToRow, int moveToCol){
  int rowDiff = moveToRow - startingRow;
  int colDiff = moveToCol - startingCol;

  assert(rowDiff == 0 || colDiff == 0); //if this condition isn't met, throw an error

  int rowDir = sign(rowDiff); //function assigns 1 or -1 to rowDir
  int colDir = sign(colDiff); //function assigns 1 or -1 to rowCol

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


//getPiece ---------------------------------------------------------------------------
ChessPiece* ChessBoard::getPiece(int row, int col) const{
  return boardLayout[row][col];
}

//findKing ------------------------------------------------------------------------
void ChessBoard::findKing(King* king, int &row, int &col){
  for (row = 0; row < 8; row++){
    for (col = 0; col < 8; col++){
      if (this->getPiece(row, col) == king){
        return;
      }
    }
  }
}


//check functions -----------------------------------------------------------------
bool ChessBoard::isKingInCheck(Color c){
  //this function looks for move by the attacking color

  King* king = (c == white) ? whiteKingPtr : blackKingPtr; //if color is white, assign whiteKingPtr to king; otherwise, assign blackKingPtr
  Color attackingColor = (c == white) ? black : white; //if color is white, assign black (opposite color) to attackingColor; otherwise, assign white

  int kingRow, kingCol;
  findKing(king, kingRow, kingCol);

  //loop through board; if there are any pieces of the opposite color that could move to the king's spot, return true (indicating in check)
  for (int pieceRow = 0; pieceRow < 8; pieceRow++){
    for (int pieceCol = 0; pieceCol < 8; pieceCol++){
      ChessPiece* piece = getPiece(pieceRow, pieceCol);
      if (piece != nullptr && piece->getColor() == attackingColor){ //need to check that it isn't nullptr to prevent segfault
        if (piece->isValidMove(*this, pieceRow, pieceCol, kingRow, kingCol)){
          return true; //exit function as soon as any valid move that could attack the king is found
        }
      }
    }
  }
  return false; //if there are no pieces of the opposite color that could attack the king, the king is not in check and thus function returns false
}

//willMovePutInCheck ----------------------------------------------------------------------------------------- 
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

//isInCheckMate ----------------------------------------------------------------------------------------- 
bool ChessBoard::isKingInCheckMate(Color c){
 
  bool isKingInCheckFlag = isKingInCheck(c);

  //safeguard to ensure king is actually in check and thus could be in checkmate
  if (!isKingInCheckFlag){
    return false;
  }

  for (int pieceRow = 0; pieceRow < 8; pieceRow++){
    for (int pieceCol = 0; pieceCol < 8; pieceCol++){ //loop through board
      ChessPiece* piece = getPiece(pieceRow, pieceCol); //grab piece
      if (piece != nullptr && piece->getColor() == c){ //if piece is of current color, loop through possible moves from current position and see if any are valid.
        for (int pieceMoveToRow = 0; pieceMoveToRow < 8; pieceMoveToRow++){
          for (int pieceMoveToCol = 0; pieceMoveToCol < 8; pieceMoveToCol++){

            ChessPiece* targetPiece = getPiece(pieceMoveToRow, pieceMoveToCol);
            if (targetPiece != nullptr && targetPiece->getColor() == c) { //if a piece will be taken as part of the move, ensure it is of the opposite color; if not, skip (continue)
              continue;
            }
            if (piece->isValidMove(*this, pieceRow, pieceCol, pieceMoveToRow, pieceMoveToCol)){ //if there are valid moves for the piece of the current color, see if check goes away with this move
              if (!willMovePutKingInCheck(c, pieceRow, pieceCol, pieceMoveToRow, pieceMoveToCol)){
                return false; //if move takes color out of check, cannot be in checkmate, so return false
              }
            }
          }
        }
      }
    }
  }
  return true;
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

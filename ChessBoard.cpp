/* Implementation file for ChessBoard class  */
#include <iostream> //is this necessary?
#include <cassert>
#include <iomanip>

#include "ChessPiece.h"

// using std::cout;
// using std::endl;

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

      // cout << fenRecord[index] << "  " << blankSpaceNeeded << endl;

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

  std::cout << "A new board state is loaded!\n";
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
    //cout << "black king is: " << blackKingPtr << endl;
  }
  else if (fenChar == 'K'){
    whiteKingPtr = new King(pieceFenColor);
    ptr = whiteKingPtr;
    //cout << "white king is: " << whiteKingPtr << endl;

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

  //check if path is clear, if necessary (all pieces except knight)
  // int rowDiff = moveToRow - startingRow;
  // int colDiff = moveToCol - startingCol;

  //at this point, it's been determined that the piece and the move are valid

  //check if move will put playing color in check. if yes, not a valid move



  
  //at this point, doesn't matter if color is in check or not. just want to make sure willMovePutInCheck returns false.
  //if color is in check already (due to opposite color), it is not in checkmate (or else the game would've ended). so, there is a legal move that can be made here that gets out of check
  if (willMovePutKingInCheck(turnColor, startingRow, startingCol, moveToRow, moveToCol)){
    cout << "move will put king in check" << endl;
    return;
  }
  //if false, continue with move
  //if true, return




  
  /*if (!isInCheck(turnColor)){
    if (willCurrentColorBeInCheck(turnColor, startingRow, startingCol, moveToRow, moveToCol)){
      cout << pieceToMove->getColor() << "'s " << pieceToMove->getName() << " cannot move from " << startingPosition << " to " << moveToPosition << " because it would put " 
           << pieceToMove->getColor() << " in check! " << endl;
      return;
    }
  }
  else {
    cout << turnColor << " is already in check. lol! let's see if we can get out of it..." << endl;
    if (moveGetsOutOfCheck()){
    }
    if (!isInCheckMate(turnColor, startingRow, startingCol, moveToRow, moveToCol)){
      cout << "that move worked, hooray" << endl;
      //return;
    }
    //else if (){
     // cout << 
      //stalemate
      //end game
    //}
    else {
      cout << turnColor << " is in checkmate" << endl;
      return;
      //END GAME?????

    }
    //run a function to see if there are any moves (current move?) to get out of check

  } */
  
  
  // cout << "just came out of willcurrentcolorbeincheck. current info: moveToRow - " << moveToRow << ", moveToCol - " << moveToCol << ", board layout at that spot - "
  // << boardLayout[4][2] << endl;
 

  //PLACEHOLDER FOR OTHER CHECKS, LIKE CHECK ---------

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
  //cout << "it is " << turnColor << "'s move" << endl;

  //check if move put OPPOSITE color in check
  if (isKingInCheck(turnColor)){
    if (isKingInCheckMate(turnColor)){
      cout << turnColor << " is in checkmate" << endl;
      //end program
      exit(0);
    }
    cout << turnColor << " is in check" << endl;
  }
return;
} 




//isDiagonalClear- --------------------------------------------------------------------
//tested
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
      //cout << "noooooo" << endl;
      return false;
    }
    //cout << "row: " << r << "  col: " << c << endl;
    r += rowDir;
    c += colDir;
  }
  //cout << "piece can move diagonally " << rowDir << " : " << colDir << endl;
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

  //cout << "r:" << r << "   c: " << c << endl;

  while(r != moveToRow || c != moveToCol){
    if (boardLayout[r][c] != nullptr){
      return false;
    }
    //cout << "row: " << r << "  col: " << c << endl;
    r += rowDir;
    c += colDir;
  }
  //cout << "piece can move straight. row direction: " << rowDir << ", col direction: " << colDir << endl;
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
        // cout << "found " << king->getColor() << "'s king at row: " << row << ", col: " << col << endl;
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
          //cout << "A piece that could put the king in check is " << piece->getColor() << "'s " << piece->getName() << " moving from row: " << pieceRow << ", col: " << pieceCol << ", to kingRow: "
               //<< kingRow << ", kingCol: " << kingCol << endl;
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
  //cout << "is in check?? " << checkResult << endl;
  //cout << "the turn color that isInCheck is using is: " << c << endl;

  //restore original board state
  boardLayout[startingRow][startingCol] = pieceToMove;
  boardLayout[moveToRow][moveToCol] = pieceToTake;

  return checkResult;
}

//isInCheckMate ----------------------------------------------------------------------------------------- 
bool ChessBoard::isKingInCheckMate(Color c){
  // King* king = (c == white) ? whiteKingPtr : blackKingPtr; //if color is white, assign whiteKingPtr to king; otherwise, assign blackKingPtr
  // Color attackingColor = (c == white) ? black : white; //if color is white, assign black (opposite color) to attackingColor; otherwise, assign white

  // int kingRow, kingCol;
  // ChessPiece* piece;
  // findKing(king, kingRow, kingCol);

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


/*
bool ChessBoard::searchForValidMoves(Color c){
  //this function looks for moves by the color in check

  for (int pieceRow = 0; pieceRow < 8; pieceRow++){
    for (int pieceCol = 0; pieceCol < 8; pieceCol++){ //loop through board to find a piece
      ChessPiece* piece = getPiece(pieceRow, pieceCol); //grab piece; this position is now the starting position
      if (piece != nullptr && piece->getColor() == c){ //if piece is of king's color, loop through possible moves from starting position and see if any are valid
        for (int pieceMoveToRow = 0; pieceMoveToRow < 8; pieceMoveToRow++){
          for (int pieceMoveToCol = 0; pieceMoveToCol < 8; pieceMoveToCol++){
            if (piece->isValidMove(*this, pieceRow, pieceCol, pieceMoveToRow, pieceMoveToCol)){
              return true; //if there is a valid move
            }
          }
        }
      }
    }
  }
  return false;
}*/



  //see if proposed move gets color out of check -- if yes, flip isInCheck switch and proceed with move
    //if no, see if there are any moves turnColor can make to get out of check (!isInCheck)
      //if yes, return false
      //if no, return true, meaning turnColor is in checkmate
  


void ChessBoard::printChessBoard(const ChessBoard& cb) {
  // Set the width for each column
    const int colWidth = 18;

    // Print the top line
    cout << "   ";
    for (int col = 0; col < 8; ++col) {
        cout << setw(colWidth) << " +";
    }
    cout << endl;

    // Loop through the board and print memory locations
    for (int row = 0; row < 8; ++row) {
        cout << 8 - row << "|";
        for (int col = 0; col < 8; ++col) {
            const ChessPiece* piece = cb.getPiece(row, col);
            cout << setw(colWidth) << piece;
        }
        cout << "|" << endl;

        // Print the separator line
        cout << "   ";
        for (int col = 0; col < 8; ++col) {
            cout << setw(colWidth) << " +";
        }
        cout << endl;
    }

    // Print column labels
    cout << "    a                b                c                d                e                f                g                h" << endl;
}

#include "ChessBoard.h"
#include<iostream>

using std::cout;

int main() {

	cout << "========================\n";
	cout << "Testing the Chess Engine\n";
	cout << "========================\n\n";

	ChessBoard cb; 
	cb.loadState("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq");
	cout << '\n';

	cb.submitMove("D7", "D6");
	cout << '\n';

	cb.submitMove("D4", "H6");
	cout << '\n';

	cb.submitMove("D2", "D4");
	cout << '\n';

	cb.submitMove("F8", "B4");
	cout << '\n'; 

	//tests I added
	/*
	
	cout << "===================================\n";
	cout << "Nicole's tests for the Chess Engine\n";
	cout << "===================================\n\n";

	cb.loadState("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq"); //starting color = black
	cout << '\n';
	
	//invalid moves tests
	cb.submitMove("E1", "E0"); //destination square isn't within range
	cout << '\n';
	//-----test moving off board


	//pawn tests

	//test moving forward 2 on first move
	cb.submitMove("B7", "B5"); //success -- black pawn moves 2 spaces forward on first move
	cout << '\n';

	//setup step
	cb.submitMove("B2", "B4"); //success -- white pawn moves 2 spaces forward on first move
	cout << '\n';

	//test not moving forward 1 bc piece in destination
	cb.submitMove("B5", "B4"); //failure -- black pawn cannot move 1 space forward because white pawn is there
	cout << '\n';

	//test moving diagonally when destination is unoccupied
	cb.submitMove("B5", "A4"); //failure -- black pawn cannot move 1 space forward bc destination is unoccupied
	cout << '\n';

	//setup step
	cb.submitMove("A7", "A5"); //success -- black pawn moves 2 spaces forward on first move
	cout << '\n';

	//test moving forward 1 on first move
	cb.submitMove("C2", "C3"); //success -- white pawn moves 1 space forward on first move
	cout << '\n';

	//test moving diagonally when destination is occupied by opposite color
	cb.submitMove("A5", "B4"); //success -- black pawn moves 1 space diagonally, taking white's pawn
	cout << '\n';

	//test moving diagonally on first move
	cb.submitMove("D2", "E3"); //failure -- white pawn cannot move diagonally on first move
	cout << '\n';

	//setup step
	cb.submitMove("D2", "D4"); //success -- white pawn moves 2 spaces forward on first move
	cout << '\n';

	//test moving forward 2 on non-first move
	cb.submitMove("B4", "B2"); //failure -- black pawn cannot move forward 2 when it isn't it's first move
	cout << '\n';

	//test moving diagonally backward
	cb.submitMove("B4", "B5"); //failure -- black pawn cannot move diagonally backward a row
	cout << '\n';

	//test moving diagonally 2 spaces
	cb.submitMove("B5", "C3"); //failure -- black pawn cannot move diagonally more than 1 space
	cout << '\n';

	//setup
	cb.submitMove("B4", "B3"); //success - black pawn moves 1 space forward
	cout << '\n';

	//test moving diagonally when destination is occupied by SAME color
	cb.submitMove("C3", "D4"); //failure -- white pawn cannot move diagonally when piece of same color is in destination
	cout << '\n';

	//setup
	cb.submitMove("F2", "F3"); //success -- white pawn moves 1 space forward on first move
	cout << '\n';

	//test moving horizontally
	cb.submitMove("B5", "A5"); //failure -- black pawn can't move horizontally
	cout << '\n';

	//setup
	cb.submitMove("E7", "E5"); //success -- black pawn moves 2 spaces forward on first move
	cout << '\n';	
	cb.submitMove("F3", "F4"); //success -- white pawn moves 1 space forward
	cout << '\n';
	cb.submitMove("E5", "E4"); //success -- black pawn moves 1 space forward
	cout << '\n';	

	//test moving forward 2 on first move when destination is occupied
	cb.submitMove("E2", "E4"); //failure -- white pawn cannot move 2 spaces forward when destination is occupied
	cout << '\n';

	//setup
	cb.submitMove("F4", "F5"); //success -- white pawn moves 1 space forward
	cout << '\n';
	cb.submitMove("E4", "E3"); //success -- black pawn moves 1 space forward
	cout << '\n';

	//test moving forward 2 on first move when middle space is occupied
	cb.submitMove("E2", "E4"); //failure -- white pawn cannot move 2 spaces forward on first move bc path is not clear
	cout << '\n';

	

	//rook tests
	cb.submitMove("A8", "A5"); //black rook successfully moves 3 spaces forward
	cout << '\n';
	cb.submitMove("A1", "A3"); //white rook cannot move forward because path is blocked
	cout << '\n';
	cb.submitMove("A5", "B5"); //black rook cannot move 1 space sideways because black pawn (its own color) is there
	cout << '\n';
	cb.submitMove("H1", "H7"); //white rook successfully moves forward 6 spaces and takes black's pawn
	cout << '\n';
	cb.submitMove("H7", "H6"); //white rook successfully moves forward 6 spaces and takes black's pawn
	cout << '\n';
	cb.submitMove("A5", "A6"); //black rook successfully moves 1 space backward
	cout << '\n';
	//cb.submitMove("A6", "A6"); //WANT TO TEST DIAGONAL
	//cout << '\n';

      

	//putting self in check tests
	//note, not necessarily a realistic board setup; just designed for test purposes
	cb.loadState("rnbqkbn1/pppppppp/8/8/8/4RB2/PPPPPPPP/RNBQK1Nr w KQkq");
	//test moving white knight -- doing so will put white in check
	cb.submitMove("G1", "H3"); //failure -- white knight cannot make a move that puts its king in check
	cout << "Nicole's test failed, as expected" << endl;
	cout << '\n';

	//queen tests
	//note, not necessarily a realistic board setup; just designed for test purposes
	cb.loadState("r1bqk1nr/pppk1pp1/4p2p/3p4/3PP3/B1PB4/P1P1QPPP/R3K1NR b KQkq"); //fenstring up to D1E2 move that puts black in check incorrectly
	cb.printChessBoard(cb);
	cb.submitMove("D5", "E4");
	cb.printChessBoard(cb);
	cout << '\n';
	

	cb.loadState("r1bqk1nr/pppk1pp1/4p2p/3p4/3PP3/B1PB4/P1P2PPP/R2QK1NR w KQkq"); //fenstring up to D1E2 move that puts black in check incorrectly
	cb.printChessBoard(cb);
	cb.submitMove("D1", "E2");
	cout << '\n';
	cb.printChessBoard(cb);
	cb.submitMove("D5", "E4");	
	cb.printChessBoard(cb);
	cout << '\n'; 
	
	//checkmate tests
	//note, not necessarily a realistic board setup; just designed for test purposes
	
	cb.loadState("7k/5Q2/8/8/8/8/8/4K3 w KQkq");
	cb.submitMove("E1", "E2");
	cout << '\n';

	cb.loadState("r4rk1/2p2ppp/p7/1p6/2P2n2/1B3b2/PP1P2q1/RNB4K w KQkq");
	cb.submitMove("D2", "D3");
	cout << '\n';

	cb.loadState("r1bqk2r/p1pn2p1/1p2pn1P/8/3P4/B1PB4/P1P2PPP/R3K1NR w KQkq"); //this is after F7E6, so black will be in checkmate after this move
	cb.submitMove("D3", "G6");
	cout << '\n';
	
	//stalemate test
	cout << "stalemate test\n";
	cb.loadState("pK6/8/8/8/8/8/5Q2/7k w KQkq");
	cb.submitMove("B8", "A8"); //white's move removes all valid moves for blackm thus stalemate
	
	*/
	
	cout << "=========================\n";
	cout << "Alekhine vs. Vasic (1931)\n";
	cout << "=========================\n\n";

	cb.loadState("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq");
	cout << '\n';

	cb.submitMove("E2", "E4");
	cb.submitMove("E7", "E6");
	cout << '\n';

	cb.submitMove("D2", "D4");
	cb.submitMove("D7", "D5");
	cout << '\n';

	cb.submitMove("B1", "C3");
	cb.submitMove("F8", "B4");
	cout << '\n';

	cb.submitMove("F1", "D3");
	cb.submitMove("B4", "C3");
	cout << '\n';

	cb.submitMove("B2", "C3");
	cb.submitMove("H7", "H6");
	cout << '\n';

	cb.submitMove("C1", "A3");
	cb.submitMove("B8", "D7");
	cout << '\n';

	cb.submitMove("D1", "E2");
	cb.submitMove("D5", "E4");
	cout << '\n';

	cb.submitMove("D3", "E4");
	cb.submitMove("G8", "F6");
	cout << '\n';

	cb.submitMove("E4", "D3");
	cb.submitMove("B7", "B6");
	cout << '\n';

	cb.submitMove("E2", "E6");
	cb.submitMove("F7", "E6");
	cout << '\n';

	cb.submitMove("D3", "G6");
	cout << '\n';

	return 0;
}

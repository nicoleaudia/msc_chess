chess: ChessBoard.o ChessPiece.o ChessMain.o
	g++ -g -Wall ChessBoard.o ChessPiece.o ChessMain.o -o chess

ChessBoard.o: ChessBoard.cpp ChessBoard.h ChessPiece.h
	g++ -g -Wall -c ChessBoard.cpp -o ChessBoard.o

ChessPiece.o: ChessPiece.cpp ChessPiece.h ChessBoard.h
	g++ -g -Wall -c ChessPiece.cpp -o ChessPiece.o

ChessMain.o: ChessMain.cpp ChessBoard.h ChessPiece.h
	g++ -g -Wall -c ChessMain.cpp -o ChessMain.o

clean:
	rm -f chess *.o

#include <iostream>

#include "piece.h"
#include "chessboard.h"
#include "chessai.h"
#include "printfunctions.h"

using namespace chess;

void test() {
	Chessboard b;
	std::cout << "\n" << b << "\n";
	b.generateMoves();
}

void test2() {
	AlphaBeta algorithm(3);
	IterativeDeepening iterative(3);
	ChessAi ai(&iterative);
	
	std::cout << "Turn 0" << "\n" << ai.chessboard() << "\n";

	for (int i = 1; i <= 50; ++i) {		
		std::cout << "\nTurn " << i;
		if (ai.isWhiteToMove()) {
			std::cout << "\nWhite ";
		} else {
			std::cout << "\nBlack ";
		}
		std::cout << "\nMoves " << ai.makeMove();
		std::cout << "\n" << ai.chessboard() << "\n";
	}
}

int main() {
	//test();
	test2();

	char a[10];
	std::cin >> a;
	return 0;
}

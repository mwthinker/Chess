#include <iostream>

#include "piece.h"
#include "chessboard.h"
#include "chessai.h"
#include "printfunctions.h"

using namespace std;
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
	
	cout << "Turn 0" << "\n" << ai.chessboard() << "\n";

	for (int i = 1; i <= 50; ++i) {		
		cout << "\nTurn " << i;
		if (ai.isWhiteToMove()) {
			cout << "\nWhite ";
		} else {
			cout << "\nBlack ";
		}
		cout << "\nMoves " << ai.makeMove();
		cout << "\n" << ai.chessboard() << "\n";
	}
}

int main() {
	//test();
	test2();

	char a[10];
	cin >> a;
	return 0;
}
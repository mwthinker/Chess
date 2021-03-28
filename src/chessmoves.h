#ifndef CHESSMOVES_H
#define CHESSMOVES_H

#include <vector>
#include "position.h"

namespace chess {

	std::vector<Position> getPawnMovesCapture() {
		std::vector<Position> moves;
		moves.push_back(Position{1,1});
		moves.push_back(Position{1,-1});
		return moves;
	}

	std::vector<Position> getPawnMoves() {
		std::vector<Position> moves;
		moves.push_back(Position{1,0});
		return moves;
	}

	std::vector<Position> getPawnSpecialMoves() {
		std::vector<Position> moves;
		moves.push_back(Position{2,0});
		return moves;
	}

	/*std::vector<Position> getKnightMovesCapture() {	
	return getKnightMoves();
	}*/

	std::vector<Position> getKnightMoves() {
		std::vector<Position> moves;
		moves.push_back(Position{2,1});
		moves.push_back(Position{2,-1});
		moves.push_back(Position{1,2});
		moves.push_back(Position{-1,2});
		moves.push_back(Position{1,-2});
		moves.push_back(Position{-1,-2});
		moves.push_back(Position{-2,1});
		moves.push_back(Position{-2,-1});
		return moves;
	}

	std::vector<Position> getKingMoves() {
		std::vector<Position> moves;
		moves.push_back(Position{1,0});
		moves.push_back(Position{1,-1});
		moves.push_back(Position{0,-1});
		moves.push_back(Position{-1,-1});
		moves.push_back(Position{-1,0});
		moves.push_back(Position{-1,1});
		moves.push_back(Position{0,1});
		moves.push_back(Position{1,1});
		return moves;
	}


	/*void generatePawnCaptureMoves() {
	std::vector<Position> pawnMoves = getPawnMovesCapture();
	int pawnSize = pawnMoves.size();

	std::vector<Position>& team = blackTeam_;
	int sign = -1;
	if (white_) {
	team = whiteTeam_;
	sign = 1;
	}
	int teamSize = team.size();

	for (int i = 0; i < teamSize; ++i) {
	for (int j = 0; j < pawnSize; ++j) {
	Position dest = team[i] + pawnMoves[j]*sign;
	Piece piece = board_[dest.row][dest.column];
	if (insideBoard(dest.row,dest.column) && piece.getType() != NONE && piece.isWhite() != white_) {
	moves_.push_back(Move(team[i] ,dest));
	std::cout << Move(team[i] ,dest) << "\n";
	}
	}
	//std::cout << dest << "\n";
	}
	//moves_
	}*/

}

#endif

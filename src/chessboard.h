#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "piece.h"
#include "position.h"
#include "move.h"

#include <vector>
#include <string>
#include <algorithm>

namespace chess {

	class Chessboard {
	public:
		Chessboard();
		Chessboard(const Chessboard& chessboard, Move move);
		Chessboard(const Chessboard& chessboard);

		inline bool isWhiteToMove() const {
			return white_;
		}

		Piece pieceAt(int row, int column) const;

		int value() const;
		
		void move(Move move);

		inline int nbrOfMoves() const {
			return static_cast<int>(moves_.size());
		}

		inline Move operator[](int nbr) const {
			return moves_[nbr];
		}
		
		inline static bool insideBoard(int row, int column) {
			return row > 0 && row < 9 && column > 0 && column < 9;
		}

		void generateMoves();

		inline std::vector<Position> whiteTeam() const {
			return whiteTeam_;
		}

		inline std::vector<Position> blackTeam() const {
			return blackTeam_;
		}

		void testBoard();

	private:
		void generatePawnMoves(const Position& position, bool white, std::vector<Move>& moves);
		void generateKnightMoves(const Position& position, bool white, std::vector<Move>& moves);
		void generateBishopMoves(const Position& position, bool white, std::vector<Move>& moves);
		void generateRookMoves(const Position& position, bool white, std::vector<Move>& moves);	
		void generateQueenMoves(const Position& position, bool white, std::vector<Move>& moves);
		void generateKingMoves(const Position& position, bool white, std::vector<Move>& moves);

		int pieceValue(Type type) const;
		void initBoard();
		void removeFromTeam(int row, int column, bool fromWhite);
		void updateTeam(Move move, bool whiteUpdate);

		Piece board_[9][9];
		bool white_;

		std::vector<Position> whiteTeam_;
		std::vector<Position> blackTeam_;

		std::vector<Move> moves_;
	};

}

#endif

#ifndef CHESSAI_H
#define CHESSAI_H

#include "chessboard.h"
#include "piece.h"
#include "move.h"
#include "minimax.h"
#include "alphabeta.h"

#include <vector>
#include <memory>

namespace chess {

	class ChessAi {
	public:
		ChessAi(BestMoveAlgorithm* bestMoveAlgorithm) {
			bestMoveAlgorithm_ = bestMoveAlgorithm;
		}		

		Move makeMove() {
			Move bestMove = bestMoveAlgorithm_->bestMove(chessboard_);
			chessboard_.move(bestMove);
			return bestMove;
		}

		void makeMove(Move move) {
			chessboard_.move(move);
		}

		Chessboard chessboard() const {
			return chessboard_;
		}

		BestMoveAlgorithm* getBestMoveAlgorithm() const {
			return bestMoveAlgorithm_;
		}

		bool isWhiteToMove() const {
			return chessboard_.isWhiteToMove();
		}

	private:
		Chessboard chessboard_;
		BestMoveAlgorithm* bestMoveAlgorithm_;
	};

} // Namespace chess.

#endif // CHESSAI_H

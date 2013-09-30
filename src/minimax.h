#ifndef MINIMAX_H
#define MINIMAX_H

#include "chessboard.h"
#include "move.h"
#include "value.h"
#include "bestmovealgorithm.h"

namespace chess {

	/*
	function integer minimax(node, depth)
	if node is a terminal node or depth == 0:
	return the heuristic value of node
	a = -inf
	for child in node:                       // evaluation is identical for both players 
	a = max(a, -minimax(child, depth-1))
	return a
	*/
	class MiniMax : public BestMoveAlgorithm {
	public:
		MiniMax(int depth) {
			depth_ = depth;
			nbr_ = 0;
			//std::cout << "\n" << bestMove;
		}

		Move bestMove(const Chessboard& chessboardCONST) {
			nbr_ = 0;
			Value alpha = -INF;
			Chessboard chessboard = chessboardCONST;
			chessboard.generateMoves();
			int size = chessboard.nbrOfMoves();		
			for (int i = 0; i < size; ++i) {
				Chessboard tmp(chessboard,chessboard[i]);			
				++nbr_;
				alpha = max(alpha, -miniMax(tmp,depth_ - 1,chessboard[i]));
			}
			std::cout << " :" << nbr_ << ": ";
			return alpha.bestMove();
		}

		Value miniMax(Chessboard chessboard, int depth, Move bestMove) {
			++nbr_;
			if (depth == 0 || terminal(chessboard)) {
				return Value(chessboard.value(),bestMove);
			}

			Value alpha = -INF;

			int size = chessboard.nbrOfMoves();
			for (int i = 0; i < size; ++i) {
				Chessboard tmp(chessboard,chessboard[i]);
				alpha = max(alpha, -miniMax(tmp,depth - 1, bestMove));
			}

			return alpha;
		}
	private:
		int nbr_;

		bool terminal(Chessboard& chessboard) {
			chessboard.generateMoves();
			return chessboard.nbrOfMoves() == 0;
		}
		int depth_;
	};

} // Namespace chess.

#endif // MINIMAX_H

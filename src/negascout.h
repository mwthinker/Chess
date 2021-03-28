#ifndef NEGASCOUT_H
#define NEGASCOUT_H

#include "chessboard.h"
#include "move.h"
#include "bestmovealgorithm.h"
#include "chessmoves.h"
#include "value.h"

#include <iostream>

namespace chess {

	/*
	function negascout(node, depth, alpha, beta)
	if node is a terminal node or depth = 0
	return the heuristic value of node
	b := beta                                             (* initial window is (-beta, -alpha) *)
	foreach child of node
	a := -negascout (child, depth - 1, -b, -alpha)
	if alpha < a < beta                                   (* check if null-window failed high*)
	a := -negascout(child, depth - 1, -beta, -alpha)  (* full re-search *)
	alpha := max(alpha, a)
	if alpha >= beta
	return alpha                                   (* Beta cut-off *)
	b := alpha + 1                                     (* set new null window *)
	return alpha
	*/
	class Negascout : public BestMoveAlgorithm {
	public:
		explicit Negascout(int depth)
			: depth_{depth} {
		}

		Move bestMove(const Chessboard& chessboardCONST) {
			nbr_ = 0;
			Value alpha = -INF;
			Chessboard chessboard = chessboardCONST;
			chessboard.generateMoves();
			int size = chessboard.nbrOfMoves();
			for (int i = 0; i < size; ++i) {
				Chessboard tmp = chessboard;
				tmp.move(chessboard[i]);
				++nbr_;
				alpha = max(alpha, -alphabeta(tmp,depth_ - 1,-INF,INF,chessboard[i]));
			}
			std::cout << " :" << nbr_ << ": ";
			return alpha.bestMove();
		}

		Value alphabeta(Chessboard chessboard, int depth, Value alpha,Value beta,Move bestMove) {
			++nbr_;
			if (depth == 0 || terminal(chessboard)) {
				return Value(chessboard.value(),bestMove);
			}		

			int size = chessboard.nbrOfMoves();
			for (int i = 0; i < size; ++i) {
				Chessboard tmp = chessboard;
				tmp.move(chessboard[i]);
				alpha = std::max(alpha, -alphabeta(tmp,depth - 1,-beta, -alpha, bestMove));

				if (alpha > beta) {
					break;
				}
			}

			return alpha;
		}
	
	private:
		bool terminal(Chessboard& chessboard) {
			chessboard.generateMoves();
			return chessboard.nbrOfMoves() == 0;
		}

		int nbr_ = 0;
		int depth_ = 0;
	};

}

#endif

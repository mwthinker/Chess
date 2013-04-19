#ifndef ALPHABETA_H
#define ALPHABETA_H

#include "bestmovealgorithm.h"
#include "chessboard.h"
#include "move.h"

#include <ctime>
#include <iostream>

namespace chess {

	/*
	function alphabeta(node, depth, alpha, beta)
	(* beta represents previous player best choice - doesn't want it if alpha would worsen it *)
	if  depth = 0 or node is a terminal node
	return the heuristic value of node
	for each child of node
	alpha := max(alpha, -alphabeta(child, depth-1, -beta, -alpha))     
	(* use symmetry, -beta becomes subsequently pruned alpha *)
	if beta<=alpha
	break	(* Beta cut-off *)
	return alpha

	(* Initial call *)
	alphabeta(origin, depth, -infinity, +infinity)
	*/
	class AlphaBeta : public BestMoveAlgorithm {
	public:
		AlphaBeta(int depth) : depth_(depth) {
		}

		Move bestMove(const Chessboard& chessboardCONST) override {
			Chessboard chessboard = chessboardCONST;
			Value value = alphabeta(chessboard,depth_,-INF,INF,Move(),true);
			return value.bestMove();
		}

		Value alphabeta(Chessboard& chessboard, int depth, Value alpha, 
			Value beta,Move bestMove, bool firstTime) {
				if (depth == 0 || terminal(chessboard)) {
					return Value(chessboard.value(),bestMove);
				}

				int size = chessboard.nbrOfMoves();
				for (int i = 0; i < size; ++i) {
					Chessboard tmp(chessboard,chessboard[i]);
					if (firstTime) {
						bestMove = chessboard[i];
					}
					alpha = max(alpha, -alphabeta(tmp, depth - 1, -beta, -alpha, bestMove, false));
					if (alpha >= beta) {
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

		const int depth_;
	};	

	class IterativeDeepening : public BestMoveAlgorithm {
	public:
		IterativeDeepening(int timeLength) {
			timeLength_ = timeLength;
		}		

		Move bestMove(const Chessboard& chessboardCONST) override {
			whiteToMove_ = chessboardCONST.isWhiteToMove();
			Chessboard chessboard = chessboardCONST;
			int depth = 1;
			Value value = alphabeta(chessboard,depth,-INF,INF,Move(),true);

			int startTime_ = (int) ::time(0);
			while (startTime_ + timeLength_ > ::time(0)) {
				Chessboard chessboard = chessboardCONST;
				value = alphabeta(chessboard,++depth,-INF,INF,Move(),true);
				std::cout << "|" << depth;
			}
			std::cout << "|";

			return value.bestMove();
		}	

		Value alphabeta(Chessboard& chessboard, int depth, Value alpha, 
			Value beta,Move bestMove, bool firstTime) {
				if (depth == 0 || terminal(chessboard)) {
					return Value(chessboard.value(),bestMove);
				}

				int size = chessboard.nbrOfMoves();
				for (int i = 0; i < size; ++i) {
					Chessboard tmp(chessboard,chessboard[i]);
					if (firstTime) {
						bestMove = chessboard[i];
					}
					alpha = max(alpha, -alphabeta(tmp, depth - 1, -beta, -alpha, bestMove, false));
					if (firstTime) {
						moveOrders_.push_back(i);
					}
					if (alpha >= beta) {
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

		int timeLength_, startTime_;
		bool whiteToMove_;		

		std::vector<int> moveOrders_;
	};

} // Namespace chess.

#endif // ALPHABETA_H

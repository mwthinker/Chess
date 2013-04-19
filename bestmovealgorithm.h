#ifndef BESTMOVEALGORITHM_H
#define BESTMOVEALGORITHM_H

namespace chess {

	class Chessboard;

	class BestMoveAlgorithm {
	public:
		virtual Move bestMove(const Chessboard& chessboard) = 0;
		virtual ~BestMoveAlgorithm() {};
	};

} // Namespace chess.

#endif // BESTMOVEALGORITHM_H

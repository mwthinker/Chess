#ifndef BESTMOVEALGORITHM_H
#define BESTMOVEALGORITHM_H

namespace chess {

	class Chessboard;

	class BestMoveAlgorithm {
	public:
		virtual ~BestMoveAlgorithm() = default;

		virtual Move bestMove(const Chessboard& chessboard) = 0;
	};

}

#endif

#ifndef PIECE_H
#define PIECE_H

namespace chess {

	enum Type {KING, QUEEN, ROOK, BISHOP, KNIGHT, PAWN, NONE};

	class Piece {
	public:
		Piece() : type_(NONE) {}

		Piece(Type type, bool white) : type_(type), white_(white) {}

		inline bool isWhite() const {
			return white_;
		}

		inline Type getType() const {
			return type_;
		}

	private:
		Type type_;
		bool white_;
	};

} // Namespace chess.

#endif // PIECE_H

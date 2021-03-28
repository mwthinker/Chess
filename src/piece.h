#ifndef PIECE_H
#define PIECE_H

namespace chess {

	enum class Type : char {
		King = 'K',
		Queen = 'D',
		Rook = 'T',
		Bishop = 'L',
		Knight = 'S',
		Pawn = 'B',
		None = '-'
	};

	class Piece {
	public:
		Piece() = default;

		Piece(Type type, bool white)
			: type_{type}
			, white_{white} {
		}

		inline bool isWhite() const {
			return white_;
		}

		inline Type getType() const {
			return type_;
		}

	private:
		Type type_ = Type::None;
		bool white_ = true;
	};

}

#endif

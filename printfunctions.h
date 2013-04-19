#ifndef PRINTFUNCTIONS_H
#define PRINTFUNCTIONS_H

#include "chessboard.h"
#include "move.h"
#include "position.h"

namespace chess {

	char printChessType(Type type) {
		char chr = 'x'; // In case of error
		switch (type) {
		case KING:
			chr = 'K';
			break;
		case QUEEN:
			chr = 'D';
			break;
		case ROOK:
			chr = 'T';
			break;
		case BISHOP:
			chr = 'L';
			break;
		case KNIGHT:
			chr = 'S';
			break;
		case PAWN:
			chr = 'B';
			break;
		case NONE:
			chr = '-';
			break;
		}
		return chr;
	}

	std::ostream& operator<<(std::ostream& stream , const Chessboard& chessboard) {
		std::string str;
		char nbr[] = {'0','1','2','3','4','5','6','7','8','9'};
		for (int i = 8; i > 0; --i) {
			str += nbr[i];
			str += "  ";
			for (int j = 1; j < 9; ++j) {
				Piece piece = chessboard.pieceAt(i,j);
				if (piece.getType() != NONE) {
					str += printChessType(piece.getType());				
					if (piece.isWhite()) {
						str += "v ";
					} else {
						str += "s ";
					}					
				} else {
					str += "-- ";
				}				
			}
			str += "\n";
		}	
		str += "\n   ";
		for (int j = 1; j < 9; ++j) {		
			str += nbr[j];
			str += "  ";
		}
		stream << str;
		return stream;
	}

	inline std::ostream& operator<<(std::ostream& stream , const Position& position) {
		stream << "(" << position.row << "," << position.column << ")";
		return stream;
	}

	inline std::ostream& operator<<(std::ostream& stream , const Move& move) {
		stream << move.start << " -> " << move.end;
		return stream;
	}

} // Namespace chess.

#endif // PRINTFUNCTIONS_H

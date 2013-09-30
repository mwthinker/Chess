#ifndef MOVE_H
#define MOVE_H

#include "position.h"

namespace chess {

	class Move {
	public:
		Move() {}

		Move(int sourceRow,int sourceColon, int destRow, int destColon) {
			start = Position(sourceRow,sourceColon);
			end = Position(destRow, destColon);
		}

		Move(Position myStart, Position myEnd) {
			start = myStart;
			end = myEnd;
		}

		Position start;
		Position end;
	};

} // Namespace chess.

#endif // MOVE_H

#ifndef MOVE_H
#define MOVE_H

#include "position.h"

namespace chess {

	class Move {
	public:
		Move() {}

		Move(int sourceRow, int sourceColon, int destRow, int destColon)
			: start{sourceRow, sourceColon}
			, end{destRow, destColon} {
		}

		Move(Position start, Position end)
			: start{start}
			, end{end} {
		}

		Position start{};
		Position end{};
	};

}

#endif

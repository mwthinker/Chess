#ifndef POSITION_H
#define POSITION_H

namespace chess {

	struct Position {
		Position() = default;

		Position(int row, int column)
			: row{row}
			, column{column} {
		}

		Position operator+(const Position& p) {
			return {row + p.row, column + p.column};
		}

		Position operator*(int nbr) {
			return {row * nbr, column * nbr};
		}

		int row = 0;
		int column = 0;
	};

}

#endif

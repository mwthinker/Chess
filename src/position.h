#ifndef POSITION_H
#define POSITION_H

namespace chess {

	struct Position {
		Position() {
			row = 0;
			column = 0;
		}

		Position(int myRow, int myColon) {
			row = myRow;
			column = myColon;
		}

		Position operator+(const Position& p) {
			return Position(row+p.row,column+p.column);
		}

		Position operator*(int nbr) {
			return Position(row*nbr,column*nbr);
		}

		int row;
		int column;
	};

} // Namespace chess.

#endif // POSITION_H

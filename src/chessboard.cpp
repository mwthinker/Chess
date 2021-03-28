#include "chessboard.h"
#include "random.h"

namespace chess {

	Chessboard::Chessboard()
		: white_{true} {
		
		initBoard();
	}

	Chessboard::Chessboard(const Chessboard& chessboard, Move move)
		: whiteTeam_{chessboard.whiteTeam_}
		, blackTeam_{chessboard.blackTeam_}
		, white_{chessboard.white_} {
			
		for (int i = 1; i <= 8; ++i) {
			for (int j = 1; j <= 8; ++j) {
				board_[i][j] = chessboard.board_[i][j];
			}
		}	
		Chessboard::move(move);
	}

	Chessboard::Chessboard(const Chessboard& chessboard)
		: whiteTeam_{chessboard.whiteTeam_}
		, blackTeam_{chessboard.blackTeam_}
		, white_{chessboard.white_} {
		
		for (int i = 1; i <= 8; ++i) {
			for (int j = 1; j <= 8; ++j) {
				board_[i][j] = chessboard.board_[i][j];
			}
		}
	}

	Piece Chessboard::pieceAt(int row, int column) const {
		if (!insideBoard(row,column)) {
			return Piece();
		}
		return board_[row][column];
	}

	int Chessboard::value() const {
		int sign = -1;
		if (white_) {
			sign = 1;
		}
		int val = 0;

		int size = static_cast<int>(whiteTeam_.size());
		for (int i = 0; i < size; ++i) {
			Position p = whiteTeam_[i];
			val += sign*pieceValue(board_[p.row][p.column].getType());
		}

		sign *= -1;
		size = static_cast<int>(blackTeam_.size());
		for (int i = 0; i < size; ++i) {
			Position p = blackTeam_[i];
			val += sign*pieceValue(board_[p.row][p.column].getType());
		}
		return val;
	}

	void Chessboard::move(Move move) {
		Position start = move.start;
		Position end = move.end;

		// Update teams
		if (board_[end.row][end.column].getType() != Type::None) { // Assumes that the current palyer captures the opponent's piece.
			removeFromTeam(end.row,end.column,!white_);
		}
		updateTeam(move,white_);

		// Updates board
		board_[end.row][end.column] = board_[start.row][start.column];
		board_[start.row][start.column] = {};

		// Pawn promotion
		if ((end.row == 1 || end.row == 8) && board_[end.row][end.column].getType() == Type::Pawn) {
			board_[end.row][end.column] = Piece{Type::Queen, white_};
		}

		// Change player's turn
		white_ = !white_;

		// Removes all moves, i.e. the moves from the earlier chess state.
		moves_.clear();
	}

	void Chessboard::generateMoves() {
		moves_.clear();
		std::vector<Position> pawns;

		std::vector<Position>* team = &blackTeam_;
		if (white_) {
			team = &whiteTeam_;
		}
		auto teamSize = static_cast<int>(team->size());
		for (int i = 0; i < teamSize; ++i) {
			Position position = team->at(i);
			Piece piece = board_[position.row][position.column];
			switch (piece.getType()) {
			case Type::Pawn:
				generatePawnMoves(position, white_, moves_);
				break;
			case Type::Knight:
				generateKnightMoves(position, white_, moves_);
				break;
			case Type::Bishop:
				generateBishopMoves(position, white_, moves_);
				break;
			case Type::Rook:
				generateRookMoves(position, white_, moves_);
				break;
			case Type::Queen:
				generateQueenMoves(position, white_, moves_);
				break;
			case Type::King:
				generateKingMoves(position, white_, moves_);
				break;
			}
		}
	}

	void Chessboard::testBoard() {
		for (int i = 1; i <= 8; ++i) {
			for (int j = 1; j <= 8; ++j) {
				board_[i][j] = {};
			}
		}
		whiteTeam_.clear();
		blackTeam_.clear();

		//board_[8][4] = Piece(PAWN,true);
		board_[8][8] = Piece(Type::Rook, true);

		for (int i = 1; i <= 8; ++i) {
			for (int j = 1; j <= 8; ++j) {
				if (board_[i][j].getType() != Type::None) {
					if (board_[i][j].isWhite()) {
						whiteTeam_.push_back(Position{i,j});
					} else {
						blackTeam_.push_back(Position{i,j});
					}
				}
			}
		}
	}

	void Chessboard::generatePawnMoves(const Position& position, bool white, std::vector<Move>& moves) {
		int step = -1;
		int startRow = 7;
		if (white) {
			step = 1;
			startRow = 2;
		}

		int row = position.row;
		int column = position.column;

		// Ordinary step
		if (insideBoard(row+step, column)) {
			Piece other = board_[row+step][column];
			if (other.getType() == Type::None) {
				moves.push_back(Move{row,column, row + step,column});
			}
		}

		// Step in order to take an opponent
		if (insideBoard(row+step, column-1)) {
			Piece other = board_[row+step][column-1];
			if (other.getType() != Type::None && white != other.isWhite()) {
				moves.push_back(Move{row, column, row + step,column - 1});
			}
		}

		if (insideBoard(row+step, column+1)) {
			Piece other = board_[row+step][column+1];
			if (other.getType() != Type::None && white != other.isWhite()) {
				moves.push_back(Move{row, column, row + step, column + 1});
			}
		}

		// Beginning step
		if (startRow == row && insideBoard(row, column)) {
			Piece other = board_[row + step * 2][column];
			if (other.getType() == Type::None && board_[row+step][column].getType() == Type::None) {
				moves.push_back(Move{row, column, row + step * 2, column});
			}
		}
	}

	void Chessboard::generateKnightMoves(const Position& position, bool white, std::vector<Move>& moves) {
		std::vector<Position> movesRel;// = ::getKnightMoves();
		movesRel.push_back(Position{2, 1});
		movesRel.push_back(Position{2, -1});
		movesRel.push_back(Position{1, 2});
		movesRel.push_back(Position{-1, 2});
		movesRel.push_back(Position{1, -2});
		movesRel.push_back(Position{-1,-2});
		movesRel.push_back(Position{-2, 1});
		movesRel.push_back(Position{-2,-1});

		auto size = static_cast<int>(movesRel.size());
		for (int i = 0; i < size; ++i) {
			int row = movesRel[i].row + position.row;
			int column = movesRel[i].column + position.column;
			if (insideBoard(row, column) && (board_[row][column].getType() == Type::None || white != board_[row][column].isWhite())) {
				moves.push_back(Move{position, Position{row, column}});
			}
		}
	}

	void Chessboard::generateBishopMoves(const Position& position, bool white, std::vector<Move>& moves) {		
		// Move up-right
		int row = position.row;
		int column = position.column;
		while (row <= 8 && column <= 8) {
			++row;
			++column;
			Piece piece = board_[row][column];
			if (insideBoard(row, column)) {
				if (piece.getType() == Type::None) {
					moves.push_back(Move{position, Position{row, column}});
				} else if (piece.isWhite() != white) {
					moves.push_back(Move{position, Position{row, column}});
					break;
				} else {
					break;
				}
			}
		}

		// Move down-left
		row = position.row;
		column = position.column;
		while (row >= 1 && column >= 1) {
			--row;
			--column;
			Piece piece = board_[row][column];
			if (insideBoard(row, column)) {
				if (piece.getType() == Type::None) {
					moves.push_back(Move{position, Position{row, column}});
				} else if (piece.isWhite() != white) {
					moves.push_back(Move{position, Position{row, column}});
					break;
				} else {
					break;
				}
			}
		}

		// Move up-left
		row = position.row;
		column = position.column;
		while (row <= 8 && column >= 1) {
			++row;
			--column;
			Piece piece = board_[row][column];
			if (insideBoard(row, column)) {
				if (piece.getType() == Type::None) {
					moves.push_back(Move{position, Position{row, column}});
				} else if (piece.isWhite() != white) {
					moves.push_back(Move{position, Position{row, column}});
					break;
				} else {
					break;
				}
			}
		}

		// Move down-right
		row = position.row;
		column = position.column;
		while (row >= 1 && column <= 8) {
			--row;
			++column;
			Piece piece = board_[row][column];
			if (insideBoard(row, column)) {
				if (piece.getType() == Type::None) {
					moves.push_back(Move{position, Position{row, column}});
				} else if (piece.isWhite() != white) {
					moves.push_back(Move{position, Position{row, column}});
					break;
				} else {
					break;
				}
			}
		}
	}

	void Chessboard::generateRookMoves(const Position& position, bool white, std::vector<Move>& moves) {	
		for (int row = position.row+1; row <= 8; ++row) {
			int column = position.column;
			Piece piece = board_[row][column];
			if (insideBoard(row, column)) {
				if (piece.getType() == Type::None) {
					moves.push_back(Move{position, Position{row, column}});
				} else if (piece.isWhite() != white) {
					moves.push_back(Move{position, Position{row, column}});
					break;
				} else {
					break;
				}
			}
		}

		// Move downwards
		for (int row = position.row-1; row >= 1; --row) {
			int column = position.column;
			Piece piece = board_[row][column];
			if (insideBoard(row, column)) {
				if (piece.getType() == Type::None) {
					moves.push_back(Move{position, Position{row, column}});
				} else if (piece.isWhite() != white) {
					moves.push_back(Move{position, Position{row, column}});
					break;
				} else {
					break;
				}
			}
		}

		// Move rightwards
		for (int column = position.column+1; column <= 8; ++column) {
			int row = position.row;		
			Piece piece = board_[row][column];
			if (insideBoard(row, column)) {
				if (piece.getType() == Type::None) {
					moves.push_back(Move{position, Position{row, column}});
				} else if (piece.isWhite() != white) {
					moves.push_back(Move{position, Position{row, column}});
					break;
				} else {
					break;
				}
			}
		}

		// Move leftwards
		for (int column = position.column-1; column >= 1; --column) {
			int row = position.row;
			Piece piece = board_[row][column];
			if (insideBoard(row, column)) {
				if (piece.getType() == Type::None) {
					moves.push_back(Move{position, Position{row, column}});
				} else if (piece.isWhite() != white) {
					moves.push_back(Move{position, Position{row, column}});
					break;
				} else {
					break;
				}
			}
		}
	}

	void Chessboard::generateQueenMoves(const Position& position, bool white, std::vector<Move>& moves) {
		generateRookMoves(position,white,moves);
		generateBishopMoves(position,white,moves);
	}

	void Chessboard::generateKingMoves(const Position& position, bool white, std::vector<Move>& moves) {
		std::vector<Position> movesRel;
		movesRel.push_back(Position{1,0});
		movesRel.push_back(Position{1,-1});
		movesRel.push_back(Position{0,-1});
		movesRel.push_back(Position{-1,-1});
		movesRel.push_back(Position{-1,0});
		movesRel.push_back(Position{-1,1});
		movesRel.push_back(Position{0,1});
		movesRel.push_back(Position{1,1});

		auto size = static_cast<int>(movesRel.size());
		for (int i = 0; i < size; ++i) {
			int row = movesRel[i].row + position.row;
			int column = movesRel[i].column + position.column;
			if (insideBoard(row, column) && (board_[row][column].getType() == Type::None || white != board_[row][column].isWhite())) {
				moves.push_back(Move{position, Position{row, column}});
			}
		}
	}

	int Chessboard::pieceValue(Type type) const {
		switch (type) {
		case Type::King:
			return 99999;
		case Type::Pawn:
			return 100 + static_cast<int>((random() - 0.5) * 20);
		case Type::Knight:
			return 300 + static_cast<int>((random() - 0.5) * 20);
		case Type::Bishop:
			return 300 + static_cast<int>((random() - 0.5) * 20);
		case Type::Rook:
			return 500 + static_cast<int>((random() - 0.5) * 20);
		case Type::Queen:
			return 900 + static_cast<int>((random() - 0.5) * 20);
		default:
			return 0;
		}
	}

	void Chessboard::initBoard() {
		// Pawns
		for (int j = 1; j <= 8; ++j) {
			board_[2][j] = Piece{Type::Pawn, true};
			board_[7][j] = Piece{Type::Pawn, false};
		}

		board_[1][1] = Piece{Type::Rook, true};
		board_[1][8] = Piece{Type::Rook, true};
		board_[8][1] = Piece{Type::Rook, false};
		board_[8][8] = Piece{Type::Rook, false};

		board_[8][2] = Piece{Type::Knight, false};
		board_[8][7] = Piece{Type::Knight, false};

		board_[1][2] = Piece{Type::Knight, true};
		board_[1][7] = Piece{Type::Knight, true};

		board_[1][3] = Piece{Type::Bishop, true};
		board_[1][6] = Piece{Type::Bishop, true};
		board_[8][3] = Piece{Type::Bishop, false};
		board_[8][6] = Piece{Type::Bishop, false};

		board_[8][4] = Piece{Type::Queen, false};
		board_[1][4] = Piece{Type::Queen, true};

		board_[8][5] = Piece{Type::King, false};
		board_[1][5] = Piece{Type::King, true};

		for (int i = 1; i <= 8; ++i) {
			for (int j = 1; j <= 8; ++j) {
				if (board_[i][j].getType() != Type::None) {
					if (board_[i][j].isWhite()) {
						whiteTeam_.push_back(Position{i, j});
					} else {
						blackTeam_.push_back(Position{i,j});
					}
				}
			}
		}
	}

	void Chessboard::removeFromTeam(int row, int column, bool fromWhite) {
		std::vector<Position>* team = &blackTeam_;

		if (fromWhite) {
			team = &whiteTeam_;
		}

		auto size = static_cast<int>(team->size());
		int remove = -1;
		for (int i = 0; i < size; ++i) {
			Position p = team->at(i);
			if (row == p.row && column == p.column) {
				remove = i;
				break;
			}
		}

		std::swap(team->at(remove),team->at(size - 1));
		team->pop_back();
	}

	void Chessboard::updateTeam(Move move, bool whiteUpdate) {
		std::vector<Position>* team = &blackTeam_;

		if (whiteUpdate) {
			team = &whiteTeam_;
		}
		auto size = static_cast<int>(team->size());
		for (int i = 0; i < size; ++i) {
			Position& p = team->at(i);
			if (move.start.row == p.row && move.start.column == p.column) {
				p = Position{move.end};
				break;
			}
		}
	}

}

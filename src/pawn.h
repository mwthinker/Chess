#ifndef PAWN_H
#define PAWN_H

#include "move.h"
#include "piece.h"

#include <vector>

namespace chess {

	class Pawn : public Piece {
	public:
		Pawn(bool white, int row, int column, ChessboardInterface* chessboard)
			: Piece(PAWN, white, row, column, chessboard) {
			
			moves_ = generatePossibleMoves();
		}

		Piece* copy(ChessboardInterface* chessboard) {
			return new Pawn(white(),row(),column(),chessboard);
		}

		Piece* copy(int row, int column, ChessboardInterface* chessboard) {
			return new Pawn(white(),row,column,chessboard);
		}

		move_iterator begin() {
			return moves_.begin();
		}

		move_iterator end() {
			return moves_.end();
		}
	private:
		std::vector<Move> generatePossibleMoves() {		
			int step = -1; // Black
			int startRow = 7;
			if (white()) {
				step = 1;
				startRow = 2;
			}

			int row = this->row();
			int column = this->column();

			ChessboardInterface* board = chessboard();

			// ordinary step
			if (board->insideBoard(row+step, column)) {
				Piece* other = board->pieceAt(row+step, column);
				if (other == 0) {
					moves_.push_back(Move(this->row(),this->column(),row+step,column));
				}
			}

			// step in order to take an opponent
			if (board->insideBoard(row+step, column-1)) {
				Piece* other = board->pieceAt(row+step, column-1);
				if (other != 0 && white() != other->white()) {
					moves_.push_back(Move(this->row(),this->column(),row+step,column-1));
				}
			}
			if (board->insideBoard(row+step, column+1)) {
				Piece* other = board->pieceAt(row+step, column+1);		
				if (other != 0 && white() != other->white()) {
					moves_.push_back(Move(this->row(),this->column(),row+step,column+1));
				}
			}

			// beginning step
			if (board->insideBoard(row+step*2, column)) {
				Piece* other = board->pieceAt(row+step*2, column);		
				if (this->row() == startRow && other == 0 && board->pieceAt(row+step, column) == 0) {
					moves_.push_back(Move(this->row(),this->column(),row+step*2,column));
				}
			}

			return moves_;
		}

		std::vector<Move> moves_;
	};

	class Knight : public Piece {
	public:
		Knight(bool white, int row, int column, ChessboardInterface* chessboard) : Piece(KNIGHT, white, row, column, chessboard) {
			moves_ = generatePossibleMoves();
		}


		Piece* copy(ChessboardInterface* chessboard) {
			return new Knight(white(),row(),column(),chessboard);
		}


		Piece* copy(int row, int column, ChessboardInterface* chessboard) {
			return new Knight(white(),row,column,chessboard);
		}

		move_iterator begin() {
			return moves_.begin();
		}

		move_iterator end() {
			return moves_.end();
		}
	private:
		std::vector<Move> generatePossibleMoves() {
			Move* move = generateMove(this->row() + 2, this->column() + 1);
			if (move != 0) {
				moves_.push_back(*move);
				delete move;
			}

			move = generateMove(this->row() + 2, this->column() - 1);
			if (move != 0) {
				moves_.push_back(*move);
				delete move;
			}

			move = generateMove(this->row() + 1, this->column() + 2);
			if (move != 0) {
				moves_.push_back(*move);
				delete move;
			}

			move = generateMove(this->row() - 1, this->column() + 2);
			if (move != 0) {
				moves_.push_back(*move);
				delete move;
			}

			move = generateMove(this->row() + 1, this->column() - 2);
			if (move != 0) {
				moves_.push_back(*move);
				delete move;
			}

			move = generateMove(this->row() - 1, this->column() - 2);
			if (move != 0) {
				moves_.push_back(*move);
				delete move;
			}

			move = generateMove(this->row() - 2, this->column() + 1);
			if (move!=0) {
				moves_.push_back(*move);
				delete move;
			}

			move = generateMove(this->row() - 2, this->column() - 1);
			if (move != 0) {
				moves_.push_back(*move);
				delete move;
			}

			return moves_;
		}

		Move* generateMove(int row,int column) {
			if (chessboard()->insideBoard(row, column)) {
				Piece* other = chessboard()->pieceAt(row, column);
				if (other == 0 || this->white() != other->white()) {
					return new Move(this->row(),this->column(),row,column);
				}
			}
			return 0;
		}

		std::vector<Move> moves_;
	};

	class Bishop : public Piece {
	public:
		Bishop(bool white, int row, int column, ChessboardInterface* chessboard) : Piece(BISHOP, white, row, column, chessboard) {
			moves_ = generatePossibleMoves();
		}

		Piece* copy(ChessboardInterface* chessboard) {
			return new Bishop(white(),row(),column(),chessboard);
		}

		Piece* copy(int row, int column, ChessboardInterface* chessboard) {
			return new Bishop(white(),row,column,chessboard);
		}
		friend class Queen;
	private:
		move_iterator begin() {
			return moves_.begin();
		}

		move_iterator end() {
			return moves_.end();
		}

		std::vector<Move> generatePossibleMoves() {
			// Move up-right
			int row = this->row();
			int column = this->column();
			while (row <= 8 && column <= 8) {
				++row;
				++column;			
				Piece* piece = chessboard()->pieceAt(row, column);
				if (chessboard()->insideBoard(row, column)) {
					if (piece == 0) {
						moves_.push_back(Move(this->row(),this->column(),row,column));
					} else if (piece->white() != white()) {
						moves_.push_back(Move(this->row(),this->column(),row,column));
						break;
					} else {
						break;
					}
				}			
			}

			// Move down-left
			row = this->row();
			column = this->column();
			while (row >= 1 && column >= 1) {
				--row;
				--column;			
				Piece* piece = chessboard()->pieceAt(row, column);
				if (chessboard()->insideBoard(row, column)) {
					if (piece == 0) {
						moves_.push_back(Move(this->row(),this->column(),row,column));
					} else if (piece->white() != white()) {
						moves_.push_back(Move(this->row(),this->column(),row,column));
						break;
					} else {
						break;
					}
				}			
			}

			// Move up-left
			row = this->row();
			column = this->column();
			while (row <= 8 && column >= 1) {
				++row;
				--column;			
				Piece* piece = chessboard()->pieceAt(row, column);
				if (chessboard()->insideBoard(row, column)) {
					if (piece == 0) {
						moves_.push_back(Move(this->row(),this->column(),row,column));
					} else if (piece->white() != white()) {
						moves_.push_back(Move(this->row(),this->column(),row,column));
						break;
					} else {
						break;
					}
				}			
			}

			// Move down-right
			row = this->row();
			column = this->column();
			while (row >= 1 && column <= 8) {
				--row;
				++column;			
				Piece* piece = chessboard()->pieceAt(row, column);
				if (chessboard()->insideBoard(row, column)) {
					if (piece == 0) {
						moves_.push_back(Move(this->row(),this->column(),row,column));
					} else if (piece->white() != white()) {
						moves_.push_back(Move(this->row(),this->column(),row,column));
						break;
					} else {
						break;
					}
				}			
			}

			return moves_;
		}

		std::vector<Move> moves_;
	};

	class Rook : public Piece {
	public:	
		Rook(bool white, int row, int column, ChessboardInterface* chessboard) : Piece(ROOK, white, row, column, chessboard) {
			moves_ = generatePossibleMoves();
		}	

		Piece* copy(ChessboardInterface* chessboard) {
			return new Rook(white(),row(),column(),chessboard);
		}

		Piece* copy(int row, int column, ChessboardInterface* chessboard) {
			return new Rook(white(),row,column,chessboard);
		}

		move_iterator begin() {
			return moves_.begin();
		}

		move_iterator end() {
			return moves_.end();
		}
		friend class Queen;
	private:
		std::vector<Move> generatePossibleMoves() {		
			// Move upwards
			for (int row = this->row()+1; row <= 8; ++row) {
				int column = this->column();
				Piece* piece = chessboard()->pieceAt(row, column);
				if (chessboard()->insideBoard(row, column)) {
					if (piece == 0) {
						moves_.push_back(Move(this->row(),this->column(),row,column));
					} else if (piece->white() != white()) {
						moves_.push_back(Move(this->row(),this->column(),row,column));
						break;
					} else {
						break;
					}
				}
			}

			// Move downwards
			for (int row = this->row()-1; row >= 1; --row) {
				int column = this->column();
				Piece* piece = chessboard()->pieceAt(row, column);
				if (chessboard()->insideBoard(row, column)) {
					if (piece == 0) {
						moves_.push_back(Move(this->row(),this->column(),row,column));
					} else if (piece->white() != white()) {
						moves_.push_back(Move(this->row(),this->column(),row,column));
						break;
					} else {
						break;
					}
				}
			}

			// Move rightwards
			for (int column = this->column()+1; column <= 8; ++column) {
				int row = this->row();
				Piece* piece = chessboard()->pieceAt(row, column);
				if (chessboard()->insideBoard(row, column)) {
					if (piece == 0) {
						moves_.push_back(Move(this->row(),this->column(),row,column));
					} else if (piece->white() != white()) {
						moves_.push_back(Move(this->row(),this->column(),row,column));
						break;
					} else {
						break;
					}
				}
			}

			// Move leftwards
			for (int column = this->column()-1; column >= 1; --column) {
				int row = this->row();
				Piece* piece = chessboard()->pieceAt(row, column);
				if (chessboard()->insideBoard(row, column)) {
					if (piece == 0) {
						moves_.push_back(Move(this->row(),this->column(),row,column));
					} else if (piece->white() != white()) {
						moves_.push_back(Move(this->row(),this->column(),row,column));
						break;
					} else {
						break;
					}
				}
			}

			return moves_;
		}	

		std::vector<Move> moves_;
	};

	class Queen : public Piece {
	public:
		Queen(bool white, int row, int column, ChessboardInterface* chessboard) : Piece(QUEEN, white, row, column, chessboard) {		
			moves_ = generatePossibleMoves();
		}

		Piece* copy(ChessboardInterface* chessboard) {
			return new Queen(white(),row(),column(),chessboard);
		}

		Piece* copy(int row, int column, ChessboardInterface* chessboard) {
			return new Queen(white(),row,column,chessboard);
		}

		move_iterator begin() {
			return moves_.begin();
		}

		move_iterator end() {
			return moves_.end();
		}	
	private:
		std::vector<Move> generatePossibleMoves() {
			Rook rook(this->white(),row(),column(),chessboard());
			Bishop bishop(this->white(),row(),column(),chessboard());
			std::vector<Move> tmp1 = rook.generatePossibleMoves();
			std::vector<Move> tmp2 = bishop.generatePossibleMoves();
			tmp1.assign(tmp2.begin(),tmp2.end());
			return tmp1;
		}	

		std::vector<Move> moves_;
	};



	class King : public Piece {
	public:
		King(bool white, int row, int column, ChessboardInterface* chessboard) : Piece(KING, white, row, column, chessboard) {
			moves_ = generatePossibleMoves();
		}

		Piece* copy(ChessboardInterface* chessboard) {
			return new King(white(),row(),column(),chessboard);
		}

		Piece* copy(int row, int column, ChessboardInterface* chessboard) {
			return new King(white(),row,column,chessboard);
		}

		move_iterator begin() {
			return moves_.begin();
		}

		move_iterator end() {
			return moves_.end();
		}
	private:	
		std::vector<Move> generatePossibleMoves() {		
			Move* move = generateMove(row()+1, column());
			if (move != 0) {
				moves_.push_back(*move);
				delete move;
			}

			move = generateMove(row()+1, column()-1);
			if (move != 0) {
				moves_.push_back(*move);
				delete move;
			}

			move = generateMove(row(), column()-1);
			if (move != 0) {
				moves_.push_back(*move);
				delete move;
			}

			move = generateMove(row()-1, column()-1);
			if (move != 0) {
				moves_.push_back(*move);
				delete move;
			}

			move = generateMove(row()-1, column());
			if (move != 0) {
				moves_.push_back(*move);
				delete move;
			}

			move = generateMove(row()-1, column()+1);
			if (move != 0) {
				moves_.push_back(*move);
				delete move;
			}

			move = generateMove(row(), column()+1);
			if (move != 0) {
				moves_.push_back(*move);
				delete move;
			}

			move = generateMove(row()+1, column()+1);
			if (move != 0) {
				moves_.push_back(*move);
				delete move;
			}
			return moves_;
		}

		Move* generateMove(int row,int column) {
			if (chessboard()->insideBoard(row, column)) {
				Piece* piece = chessboard()->pieceAt(row, column);
				if (piece == 0 || white() != piece->white()) {
					return new Move(this->row(),this->column(),row,column);
				}
			}
			return 0;
		}
		std::vector<Move> moves_;
	};

}

#endif

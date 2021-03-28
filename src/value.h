#ifndef VALUE_H
#define VALUE_H

#include "move.h"

#include <limits>

namespace chess {

	class Move;

	class Value {
	public:
		Value(int value, Move bestMove)
			: value_{value}
			, bestMove_{bestMove} {
		}

		explicit Value(int value)
			: value_{value} {
		}

		bool operator>(Value valueObj) const {
			return value_ > valueObj.value_;
		}

		bool operator>=(Value valueObj) const {
			return value_ >= valueObj.value_;
		}

		int value() const {
			return value_;
		}

		Move bestMove() const {
			return bestMove_;
		}

		Value operator-() const {
			return {value_*-1, bestMove_};
		}
		
	private:
		int value_;
		Move bestMove_;
	};

	inline Value max(Value value1, Value value2) {
		if (value1 > value2) {
			return value1;
		} else {
			return value2;
		}
	}

	const Value Inf(std::numeric_limits<int>::max());

}

#endif

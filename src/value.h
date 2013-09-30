#ifndef VALUE_H
#define VALUE_H

#include <limits>

namespace chess {

	class Move;

	class Value {
	public:
		Value(int value, Move bestMove) : value_(value), bestMove_(bestMove) {
		}

		Value(int value) : value_(value) {
		}

		inline bool operator>(Value valueObj) const {
			return value_ > valueObj.value_;
		}

		inline bool operator>=(Value valueObj) const {
			return value_ >= valueObj.value_;
		}

		inline int	value() const {
			return value_;
		}

		inline Move bestMove() const {
			return bestMove_;
		}

		inline Value operator-() const {
			return  Value(value_*-1, bestMove_);
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

	const Value INF(std::numeric_limits<int>::max());

}

#endif // VALUE_H
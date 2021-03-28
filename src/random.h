#ifndef RANDOM_H
#define RANDOM_H

#include <random>

namespace chess {

	// Returns a random number. The output is uniformly distributed on the interval [min, max).
	inline float random(float min, float max) {
		static std::random_device rd;
		static std::default_random_engine generator(rd());
		return std::uniform_real_distribution<float>{min, max}(generator);
	}
	
	// Returns a random number. The output is uniformly distributed on the interval [0, 1).
	inline float random() {
		return random(0, 1);
	}

}

#endif

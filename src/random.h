#ifndef RANDOM_H
#define RANDOM_H

#include <random>

namespace chess {

	// Returns a random number. The output is uniformly distributed on the interval [a, b).
	float random() {
		static std::random_device rd;
		static std::default_random_engine generator(rd());
		static std::uniform_real_distribution<float> distribution(0.0,1.0);
		return distribution(generator);
	}
}

#endif // RANDOM_H

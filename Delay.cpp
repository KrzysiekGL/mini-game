#include "Delay.h"

void Delay::delay(float time) {
	sf::Clock clock;
	sf::Time elapsedTime;

	while (true) {
		elapsedTime = clock.getElapsedTime();
		if (elapsedTime.asMilliseconds() >= time) {
			break;
		}
	}
}